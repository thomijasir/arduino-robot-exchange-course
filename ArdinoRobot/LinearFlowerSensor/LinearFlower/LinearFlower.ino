#define swLeftUp digitalRead(pinSwLeftUp);
#define swLeftDown digitalRead(pinSwLeftDown);
#define swRightUp digitalRead(pinSwRightUp);
#define swRightDown digitalRead(pinSwRightDown);

int leftForward = 6;
int leftReverse = 5;
int rightForward = 9;
int rightReverse = 10;

int pinSwLeftUp = 3;
int pinSwLeftDown = 2;
int pinSwRightUp = 11;
int pinSwRightDown = 12;

 int ledLeft = 7;
 int ledMid = 13;
 int ledRight = 8;

char buff[100];
//Black Line 980
//White Line 880
//peka (sensitivity) = white line value + ((black line value - white line value)/2)

int peka = 900;

int adc_sensor[8],sendat[8], x, sensorBit, maxpwm = 250, t;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9000);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftReverse, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightReverse, OUTPUT);

  pinMode(pinSwLeftUp, INPUT_PULLUP);
  pinMode(pinSwLeftDown, INPUT_PULLUP);
  pinMode(pinSwRightUp, INPUT_PULLUP);
  pinMode(pinSwRightDown, INPUT_PULLUP);
  
  pinMode(ledLeft, OUTPUT);
  pinMode(ledMid, OUTPUT);
  pinMode(ledRight, OUTPUT);
}

void readSensor(){
  adc_sensor[0] = analogRead(A3);
  adc_sensor[1] = analogRead(A2);
  adc_sensor[2] = analogRead(A1);
  adc_sensor[3] = analogRead(A0);
  adc_sensor[4] = analogRead(A7);
  adc_sensor[5] = analogRead(A6);
  adc_sensor[6] = analogRead(A5);
  adc_sensor[7] = analogRead(A4); 
  delay(50);

 for(x = 7 ; x >= 0; x--){
  if(adc_sensor[x] > peka){
      sendat[x] = 1;
    } else{
      sendat[x] = 0;
      }
 }

 sensorBit = 0;
 for(x= 0; x<= 7; x++){
  sensorBit += sendat[x] * (1 << x); 
 }

 // Displaying The Data
 sprintf(buff, "%3d %3d %3d %3d %3d %3d %3d %3d",
 adc_sensor[7],
 adc_sensor[6],
 adc_sensor[5],
 adc_sensor[4],
 adc_sensor[3],
 adc_sensor[2],
 adc_sensor[1],
 adc_sensor[0]);
 Serial.print(buff);

 sprintf(buff, "%d%d%d%d%d%d%d%d %3d",
 sendat[7],
 sendat[6],
 sendat[5],
 sendat[4],
 sendat[3],
 sendat[2],
 sendat[1],
 sendat[0],
 peka);

 Serial.println(buff);
 
}

void setMotor(int pwmLeft, int pwmRight){
    if(pwmLeft > maxpwm){
        pwmLeft = maxpwm;
      }else if(pwmLeft < -maxpwm){
        pwmLeft = -maxpwm;  
      }
    if(pwmLeft < 0){
      pwmLeft *= -1;
      analogWrite(leftReverse, pwmLeft);
      analogWrite(leftForward, 0);
     }else{
      analogWrite(leftReverse, 0);  
      analogWrite(leftForward, pwmLeft);
     }

     if(pwmRight > maxpwm){
       pwmRight = maxpwm;
      }else if(pwmRight < -maxpwm){
        pwmRight = -maxpwm;
       }

       if(pwmRight < 0){
          pwmRight *= -1;
          analogWrite(rightReverse, pwmRight);
          analogWrite(rightForward, 0);
        }else{
          analogWrite(rightReverse, 0);
          analogWrite(rightForward, pwmRight);   
        }
  }


void loop() {
  // put your main code here, to run repeatedly:
  readSensor();
}
