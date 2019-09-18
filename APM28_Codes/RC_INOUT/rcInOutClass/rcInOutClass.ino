#include "rcInOut.h"
extern RCINOUT radio;
enum {OUT1, OUT2, OUT3, OUT4, OUT5};
void setup() {
  Serial.begin(115200);
  radio.init();
  radio.enableOut(OUT1); radio.enableOut(OUT2);
  radio.enableOut(OUT3); radio.enableOut(OUT4);
}
void loop() {
    if (radio.getState()){
      Serial.print(radio.inputCh(OUT1));Serial.print(",");
      Serial.print(radio.inputCh(OUT2));Serial.print(",");
      Serial.print(radio.inputCh(OUT3));Serial.print(",");
      Serial.print(radio.inputCh(OUT4));Serial.print(",");
      Serial.print(radio.inputCh(OUT5));Serial.print("\n");
      radio.outputCh(OUT1, radio.inputCh(OUT1)); radio.outputCh(OUT2, radio.inputCh(OUT2));
      radio.outputCh(OUT3, radio.inputCh(OUT3)); radio.outputCh(OUT4, radio.inputCh(OUT4));
    }
    delay(10);
}
