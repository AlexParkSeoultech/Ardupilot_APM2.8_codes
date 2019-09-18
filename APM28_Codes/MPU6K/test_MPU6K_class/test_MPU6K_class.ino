#include <SPI.h>
#include "MPU6k.h"
#define BARO_CS_PIN 40
extern MPU6000 mpu;
void setup() {
  Serial.begin(115200);  
  pinMode(BARO_CS_PIN, OUTPUT);  pinMode(12, OUTPUT);
  pinMode(MPU6K_CS_PIN, OUTPUT); digitalWrite(MPU6K_CS_PIN, HIGH);
  digitalWrite(BARO_CS_PIN, HIGH);   //Diselect Barometer
  SPI.begin();  
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  delay(100); 
  mpu.configureMPU6000();  // configure chip
}
void loop() {
   mpu.updateData( ); 
  Serial.print(mpu._accel.x); Serial.print(",");
  Serial.print(mpu._accel.y); Serial.print(",");
  Serial.print(mpu._accel.z);// Serial.print(",");   
//  Serial.print(mpu._gyro.x);Serial.print(",");
//  Serial.print(mpu._gyro.y);  Serial.print(",");
//  Serial.print(mpu._gyro.z);  
  Serial.print("\n");    
}
