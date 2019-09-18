void setup() {
  Serial.begin(9600);
  pinMode(25, OUTPUT); pinMode(26, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(2,HIGH);  // Internal Pull-up
  attachInterrupt(digitalPinToInterrupt(2), flip, FALLING);
}
void loop() {
  digitalWrite(26,LOW);  delay(1000);
  digitalWrite(26,HIGH);  delay(1000);
}
void flip(){     // interrupt service routine
  digitalWrite(25,!digitalRead(25));
}
