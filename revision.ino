const int btn = 2;
volatile bool flip = false;

void setup() {
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(btn), motionISR, FALLING); //1 to 0
}

void loop() {
  if(flip == true) {
    Serial.println("Door Opened.");
  }
  flip = false;
}

void motionISR() {
  flip = true;
}