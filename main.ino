void setup() {
  Serial.begin(9600);
  Serial.println("USB OK");
}

void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
}