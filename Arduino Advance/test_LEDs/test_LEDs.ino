int LED[3]={25,26,27};
int td[3]={100, 400, 800};
void setup() {
 for (int i=0;i<3;i++) pinMode(LED[i],1);

}

void loop() {
  for (int i=0;i<3;i++) {
    digitalWrite(LED[i],!digitalRead(LED[i]));
    delay(td[i]);
  }

}
