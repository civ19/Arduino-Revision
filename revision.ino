const int led = 9;
int ledState = 0;
long int lastToggle = 0;
int toggleDelay = 500;

const int btn = 4;
int btnState = 1;
long int lastPress = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int curr_state = digitalRead(btn); 
  
  //first check led state. then, if led state isnt the same as the current state, update last toggle. this happens every 500ms
  if(millis()-lastToggle >= toggleDelay) { //if its been 500ms since the last time it turned on, or off, change state
    ledState=!ledState; //changing state
    lastToggle = millis();
  }
  digitalWrite(led, ledState);

  if(curr_state!=btnState) {lastPress = millis();}

  if(millis() - lastPress >= 50) {
    if(curr_state == LOW) {toggleDelay = 100; Serial.println("Debounced?");}
    else toggleDelay = 500;
  }

  btnState = curr_state; //update curr state
  
  //first we put toggle delay, then checked if its pressed. if its HIGH(btn), we write 500ms. if it gets low we write



}
