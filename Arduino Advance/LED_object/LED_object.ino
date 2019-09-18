#include "LEDBasic.h"
LEDbasic LEDred(27), LEDyellow(26), LEDblue(25);
void setup() {}
void loop() { 
  LEDblue.blink(100);
}
