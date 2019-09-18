#include "MS5611.h"
#include <SPI.h>
uint32_t curtime=0, prevtime=0,count=0;
float alt=0;
MS5611 baro;
void setup() {
  pinMode(12,OUTPUT); pinMode(11,OUTPUT);
  Serial.begin(115200);
  SPI.begin();
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));
  baro._init();
  prevtime=micros();
  digitalWrite(27,HIGH);
}
void loop() {
  do {curtime=micros();}  while (curtime-prevtime<1000);
    prevtime=curtime;     
    if (count% 10==0)
        digitalWrite(11,HIGH);
        baro._update(curtime); 
        digitalWrite(11,LOW);
     if (count% 20==0) {
        digitalWrite(12,!digitalRead(12));
        baro._read();
        alt=0.98*alt+0.02*(baro.get_altitude()-5501.); // simple filtering
        Serial.println(alt);//Serial.print(",");// x100
        //Serial.println(get_temperature());// x10
     }  
  count ++;
}
