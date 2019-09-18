void setup() {
  Serial.begin(9600);
  pinMode(27,OUTPUT);
}
void loop() {
 digitalWrite(27,HIGH);delay(2000);
 digitalWrite(27,LOW);delay(2000);
}
void serialEvent(){
  while (Serial.available()){
    uint8_t val=Serial.read();
    Serial.write(val);
  }
}

