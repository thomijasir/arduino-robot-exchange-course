#define swLeftUp digitalRead(PinSwLeftUp)
#define swLeftDown digitalRead(PinSwLeftDown)
#define swRightUp digitalRead(PinSwRightUp)
#define swRightDown digitalRead(PinSwRightDown)

int leftForward = 6; // Left Motor - Forward
int leftRevese = 5; // Left Motor - Revers
int rightForward = 9; // Right Motor - forward
int rightRevers = 10; // Right Motor - Reverse

int PinSwLeftUp = 3;
int PinSwLeftDown = 2;
int PinSwRightUp = 11;
int PinSwRightDown = 12;

int leftLed = 7;
int ledMid = 13;
int ledRight = 9;
int maxpwm = 250;
int jeda;

void setup() {
  // OUTPUT
  pinMode(leftForward, OUTPUT);
  pinMode(leftRevese, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightRevers, OUTPUT);
  // Input
  pinMode(PinSwLeftUp, INPUT_PULLUP);
  pinMode(PinSwLeftDown, INPUT_PULLUP);
  pinMode(PinSwRightUp, INPUT_PULLUP);
  pinMode(PinSwRightDown, INPUT_PULLUP);
}

void setMotor(int pwmLeft, int pwmRight){
    if(pwmLeft > maxpwm){
        pwmLeft = maxpwm;
      }else if(pwmLeft < -maxpwm){
        pwmLeft = -maxpwm;  
      }
    if(pwmLeft < 0){
      pwmLeft *= -1;
      analogWrite(leftRevese, pwmLeft);
      analogWrite(leftForward, 0);
     }else{
      analogWrite(leftRevese, 0);  
      analogWrite(leftForward, pwmLeft);
     }

     if(pwmRight > maxpwm){
       pwmRight = maxpwm;
      }else if(pwmRight < -maxpwm){
        pwmRight = -maxpwm;
       }

       if(pwmRight < 0){
          pwmRight *= -1;
          analogWrite(rightRevers, pwmRight);
          analogWrite(rightForward, 0);
        }else{
          analogWrite(rightRevers, 0);
          analogWrite(rightForward, pwmRight);   
        }
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!swLeftUp){
      analogWrite(leftForward, 200);
    }else{
        analogWrite(leftForward,0);
      }

  if(!swLeftDown){
      analogWrite(leftRevese, 150);
    }else{
        analogWrite(leftRevese,0);
      }

  if(!swRightUp){
      analogWrite(rightForward, 200);
    }else{
      analogWrite(rightForward, 0);
      }

  
  if(!swRightDown){
      analogWrite(rightForward, 150);
    }else{
      analogWrite(rightForward, 0);
      }

}
