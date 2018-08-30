
#include <ESP8266WiFi.h>
// Indicator LED
int ledR = D0;
int ledG = D1;
int ledB = D2;
int ledRB = D5;

// Buzz
int buzer = D6;

// PIR
// PIR SENSOR READ 0 and 1
int pirSensor = D3;

//Rellay
int rellay = D4;
#define RELAY_ON 0
#define RELAY_OFF 1


const char* ssid     = "Fast Fiber";
const char* password = "123456789";

const char* host = "onesystem.comeze.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

// Global Variable

int detected = 0;
int durationPrisent = 6000*1;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledRB, OUTPUT);
  pinMode(buzer, OUTPUT);
  pinMode(pirSensor, INPUT);
  pinMode(rellay, OUTPUT);
  digitalWrite(rellay, RELAY_OFF);
  wifiConnect();

}

void wifiConnect(){
  // We start by connecting to a WiFi network
  signWifiOff();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
}

void signWifiOn(){
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
  }
void signWifiOff(){
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
  }

void buz(){
  detected++;
  if(detected == 1){
      tone(buzer, 1000);
      delay(100);        
      noTone(buzer);
      delay(100);
      tone(buzer, 1000);
      delay(100);        
      noTone(buzer);
    }
     
  }

void loop() {
  // WIFI CHECK
  if(WiFi.status() != WL_CONNECTED){
      signWifiOff();
      wifiConnect();
   }else{
      signWifiOn();
      int sensorVal = digitalRead(pirSensor);
       if(sensorVal == 1){
          buz();
         digitalWrite(ledB, LOW);
         rellayON();
         passingData();
         delay(durationPrisent);
      }else{
         rellayOFF();
         digitalWrite(ledB, HIGH);
         detected =0;
       }
   }
   
}

void rellayON(){
    digitalWrite(ledRB, HIGH);
    digitalWrite(rellay, RELAY_ON);
  }

void rellayOFF(){
    digitalWrite(ledRB, LOW);
    digitalWrite(rellay, RELAY_OFF);
  }

void passingData(){

Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }else{
    Serial.println("Connecting  successfuly");

  // Database Push
  String url = "/oneelectric/public/detected/1";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  // Notification Push
  pushNotification();
  

   }
   
   // END VOID
  }

void pushNotification(){

Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }else{
    Serial.println("Connecting  successfuly");

  // Database Push
  String url = "/oneelectric/public/push/index.php";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
 
  
   }
   
   // END VOID
  }


