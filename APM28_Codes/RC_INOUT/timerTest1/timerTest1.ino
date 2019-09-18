#include "timerSetup.h"
void setup() {
  Serial.begin(115200);
  initTimers();
  enableOut(0); enableOut(1);
  outputCh(0, 1000);
  outputCh(1, 2000);
}
void loop() {
}
