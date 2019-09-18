#include "TimerTwo.h"
bool state=false;
uint32_t period=100000,prevTime;
Timer2 back;
void setup() {
  Serial.begin(115200);
  pinMode(26,OUTPUT);
  pinMode(25,OUTPUT);
  prevTime=micros();
  back.init(periodic);
}

void loop() {
  digitalWrite(25,1); delay(1000);
  digitalWrite(25,0); delay(1000);
}

void periodic(){
  uint32_t curTime=micros();
  if (curTime-prevTime < period) return;
    prevTime=curTime;
    //Serial.println(state); 
    digitalWrite(26, state);
    state=!state;
}

