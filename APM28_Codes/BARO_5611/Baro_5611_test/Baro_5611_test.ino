#include "MS5611.h"
#include <SPI.h>
uint32_t curtime=0, prevtime=0,count=0;
void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));
  _init();
  prevtime=micros();
  digitalWrite(27,HIGH);
}
void loop() {
  do {curtime=micros();}  while (curtime-prevtime<1000);
    prevtime=curtime;     
    if (count% 10==0)
           _update(curtime); 
     if (count% 50==0) {
         _read();
         Serial.println(get_altitude());//Serial.print(",");// x100
         //Serial.println(get_temperature());// x10
     }  
  count ++;
}
