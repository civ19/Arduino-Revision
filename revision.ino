volatile int encoderPos = 0;
int lastPos = -1;

const int clk = 2;
const int dt = 3;

void setup() {
  pinMode(clk, INPUT_PULLUP);
  pinMode(dt, INPUT_PULLUP);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(clk), rotaryISR, FALLING); //if something drops then itll signify cw and ccw

}

void loop() { //the actual stuff we wanna print
  if(encoderPos != lastPos) {
    Serial.print("Position val: "); Serial.println(encoderPos);

    lastPos = encoderPos; //upodatng it
  }
}
void rotaryISR() { //bg logic
  int dtState = digitalRead(dt);

  if(dtState == HIGH && encoderPos < 100) {encoderPos++;} //cw
  else if(dtState == LOW && encoderPos > 0) {encoderPos--;} //ccw. dtState drops first
}