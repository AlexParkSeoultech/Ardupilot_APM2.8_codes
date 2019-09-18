#include "timerSetup.h"
void setup() {
  Serial.begin(115200);
  initTimers();
  enableOut(0); enableOut(1); enableOut(2); 
  enableOut(3); enableOut(4);
}
void loop() {
    if (getState()){
      Serial.print(inputCh(0));Serial.print(",");
      Serial.print(inputCh(1));Serial.print(",");
      Serial.print(inputCh(2));Serial.print(",");
      Serial.print(inputCh(3));Serial.print(",");
      Serial.print(inputCh(4));Serial.print("\n");
      outputCh(0, inputCh(0));outputCh(1, inputCh(1));
      outputCh(2, inputCh(2));outputCh(3, inputCh(3));
    }
    delay(10);
}

