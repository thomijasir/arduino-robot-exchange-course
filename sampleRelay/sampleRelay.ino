#define RELAY  D4
#define RELAY_ON 0
#define RELAY_OFF 1

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, RELAY_OFF);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RELAY, RELAY_ON);
  delay(2000);
  digitalWrite(RELAY, RELAY_OFF);
  delay(5000);
}
