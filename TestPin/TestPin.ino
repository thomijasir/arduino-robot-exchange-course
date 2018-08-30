// Indicator LED
int ledR = D0;
int ledG = D1;
int ledB = D2;
int ledRB = D5;

int pirSensor = D3;

int buzzer = D6;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledRB, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pirSensor, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(ledR, HIGH);
//  digitalWrite(ledG, HIGH);
//  digitalWrite(ledB, HIGH);
//  digitalWrite(ledRB, HIGH);
  int sensorVal = digitalRead(pirSensor);
  Serial.println(sensorVal);
  delay(300);
 
}
