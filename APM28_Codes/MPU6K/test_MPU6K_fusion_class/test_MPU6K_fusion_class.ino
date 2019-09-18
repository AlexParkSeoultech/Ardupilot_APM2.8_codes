#include <SPI.h>
#include "MPU6k.h"
#define INTRRUPT_PLOT  
#define BARO_CS_PIN 40
//#define RadToDeg (180/PI)
#define ALPHA 0.89
extern MPU6000 mpu;
float roll=0, pitch=0, yaw=0,dt=0.01;
float gyAngleX=0, gyAngleY=0, gyAngleZ=0;
uint32_t prevTime=0;
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
  //calcDT();
  makeDt(10000);
  mpu.updateData( ); 
  float accAngleX=-atan2(mpu._accel.y,-mpu._accel.z);
  float srtAccXY=sqrt(mpu._accel.y*mpu._accel.y+mpu._accel.z*mpu._accel.z);
  float accAngleY=atan2(mpu._accel.x,srtAccXY);
  roll=ALPHA* (roll+mpu._gyro.x*dt)+(1-ALPHA)*accAngleX;
  pitch=ALPHA* (pitch+mpu._gyro.y*dt)+(1-ALPHA)*accAngleY;
  gyAngleX=gyAngleX+mpu._gyro.x*dt;
  gyAngleY=gyAngleY+mpu._gyro.y*dt;
  gyAngleZ=gyAngleZ+mpu._gyro.z*dt; 
  Serial.print(roll*RAD_TO_DEG); Serial.print(",");
  Serial.print(pitch*RAD_TO_DEG);// Serial.print(",");
  //Serial.print(_accel.z); Serial.print(",");   
// Serial.print(_gyro.x);Serial.print(",");
 // Serial.print(_gyro.y);  Serial.print(",");
 //Serial.print(dt,5);  
  Serial.print("\n");    
delay(0);
}
void calcDT() {
  uint32_t newTime = micros();
  dt = (newTime - prevTime)/1000000.0;
  prevTime = newTime;  
}
void makeDt(uint32_t p){
  uint32_t newTime;
  do {newTime = micros();}while (newTime - prevTime<p);
  prevTime = newTime;
}
