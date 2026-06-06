#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.println("Ready for LED Control.");
}

void loop() {

  if (BT.available()) {
    char data = BT.read(); //user input 
    Serial.print("Received: ");
    Serial.println(data);

    if(data == '1') digitalWrite(13, HIGH);
    else if (data == '0') digitalWrite(13, LOW);
    
    //basically, just begin the serials, do pinmode, take in user input, and thats iut
  }
}