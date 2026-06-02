const int led = 9;
int lastPot = 0;
const int servo = 3;

#include <Servo.h>

Servo s;

const int btn = 4;
int btnState = 1;
long int lastPress = 0;
void setup() {
  // put your setup code here, to run once:
  s.attach(servo);
  Serial.begin(9600);
  lastPot = analogRead(A0); //initial reading
 

}

void loop() {
  // put your main code here, to run repeatedly:
  //last pot
  int raw = analogRead(A0);
  if(abs(raw - lastPot) >=5) {
    int angle = map(raw, 0, 1023, 0, 180);
    s.write(angle);
    Serial.print("Angle: "); Serial.println(angle);
    //upadte last pot 
    lastPot = raw;
  }
}
