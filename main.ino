#include <SoftwareSerial.h>

SoftwareSerial BT (0,1); //RX, TX

void setup() {
    Serial.begin(9600); //usb serial comms, pc to arduiono. the normal one
    BT.begin(38400); //serialcomms: hc-05 to arduino 
    Serial.println("AT Mode Ready"); //ready for AT configs!

}

void loop() {
    if(Serial.available()) { //if we have available bytes to use
        BT.write(Serial.read()); //if you type something on pc, send it/write it to hc05
    }

    if(Serial.available()) Serial.write(BT.read()); //if hc05 responds, send it back to pc
}


/*
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  BT.begin(38400); // AT mode default baud rate
  Serial.println("AT Mode Ready");
}

void loop() {
  if (Serial.available()) {
    BT.write(Serial.read());
  }

  if (BT.available()) {
    Serial.write(BT.read());
  }
}*/