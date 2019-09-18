#include <SPI.h>
#include "AHRS.h"
//#define RadToDeg (180/PI)
AHRS ahrs;
uint32_t prevTime;
void setup() {
  Serial.begin(115200);  
  SPI.begin();  
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));delay(100);
  ahrs.init();
  prevTime = micros();
}
void loop() {
 //calcDT();
  makeDt(5000);
 ahrs.MARG_comp(0.01);
 // ahrs.IMU_comp(0.005);
 Serial.print(ahrs.roll*RadToDeg); Serial.print(",");
 Serial.print(ahrs.pitch*RadToDeg); Serial.print(",");
 //float y=wrap_PI(ahrs.yaw);
 Serial.print(ahrs.yaw*RadToDeg); //Serial.print(",");
 //Serial.print(ahrs.alt_acc); //Serial.print(",");   
  Serial.print("\n");   
 // digitalWrite(12,!digitalRead(12)); 
//delay(0);
}
void makeDt(uint32_t p){
  uint32_t newTime;
  do {newTime = micros();}while (newTime - prevTime<p);
  prevTime = newTime;
}


