#define swLeftUp digitalRead(pinSwLeftUp)
#define swLeftDown digitalRead(pinSwLeftDown)
#define swRightUp digitalRead(pinSwRightUp)
#define swRightDown digitalRead(pinSwRightDown)

int leftForward = 6; // Left Motor - Forward
int leftReverse = 5; // Left Motor - Revers
int rightForward = 9; // Right Motor - forward
int rightReverse = 10; // Right Motor - Reverse

int pinSwLeftUp = 3;
int pinSwLeftDown = 2;
int pinSwRightUp = 11;
int pinSwRightDown = 12;

int ledLeft = 7;
int ledMid = 13;
int ledRight = 8;

char buff[100];
// Black line 980
// White Line 880
// peka (Sensitivity) = white line value + ((black line valuie - white line value)/2)
int peka = 980;

int adc_sensor[8],
sendat[8],
robotSpeedRight,
robotSpeedLeft,
robotSpeed = 190, // Speed Range 0 - 255
kp = 20,
kd = 10,
lastError = 0,
error = 0,
x,
rate,
sensorBit,
maxpwm = 250,
t;
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9000);
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

void loop() {
  // put your main code here, to run repeatedly:
  follow_line();
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
//  delay(10);
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
 //Serial.print(buff);

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

 //Serial.println(buff);
 
}

void pv(){
    switch(sensorBit){
      case 0b10000000: error = -6; break;
      case 0b11000000: error = -5; break;
      case 0b01000000: error = -4; break;
      case 0b01100000: error = -4; break;
      case 0b00100000: error = -2; break;
      case 0b00110000: error = -1; break;
      case 0b00010000: error = 0; break;
      //
      case 0b00011000: error = 0; break;
      //
      case 0b00001000: error = 0; break;
      case 0b00001100: error = 1; break;
      case 0b00000100: error = 2; break;
      case 0b00000110: error = 3; break;
      case 0b00000010: error = 4; break;
      case 0b00000011: error = 5; break;
      case 0b00000001: error = 6; break;
      default: error = lastError; break;
    }
  }

void follow_line(){
    readSensor();
    pv();
    if(error < -2){
      digitalWrite(ledLeft, 1);
      digitalWrite(ledMid,0);
      digitalWrite(ledRight,0);
    }else if(error > 2){
      digitalWrite(ledLeft, 0);
      digitalWrite(ledMid,0);
      digitalWrite(ledRight,1);
    }else{
        digitalWrite(ledLeft, 0);
        digitalWrite(ledMid,1);
        digitalWrite(ledRight,0);
      }
      rate = error - lastError;
      lastError = error;
      int moveControl = (kp * error) + (rate * kd);
      robotSpeedRight = robotSpeed - moveControl;
      robotSpeedLeft = robotSpeed + moveControl;
      setMotor(robotSpeedLeft, robotSpeedRight);
      //Serial.println(robotSpeedLeft);
      //Serial.println(robotSpeedRight);  
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

