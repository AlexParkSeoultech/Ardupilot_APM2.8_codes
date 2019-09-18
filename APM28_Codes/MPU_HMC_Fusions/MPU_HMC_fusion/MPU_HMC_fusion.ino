#include <SPI.h>
#include "MPU6k.h"
#include <Wire.h>
#include "HMC5883L.h"
#define BARO_CS_PIN 40
#define RadToDeg (180/PI)
#define ALPHA 0.96
extern MPU6000 mpu;
HMC5883L hmc;
float roll=0, pitch=0, yaw=0,dt=0.01;
float gyAngleX=0, gyAngleY=0, gyAngleZ=0;
uint32_t prevTime=micros();
void setup() {
  Serial.begin(115200);  
  pinMode(BARO_CS_PIN, OUTPUT);  pinMode(12, OUTPUT);
  pinMode(MPU6K_CS_PIN, OUTPUT); digitalWrite(MPU6K_CS_PIN, HIGH);
  digitalWrite(BARO_CS_PIN, HIGH);   //Diselect Barometer
  SPI.begin();  
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));delay(100);
  mpu.configureMPU6000();  // configure chip
  while (!hmc.begin()) delay(500);
  hmc.init();
}
void loop() {
 //calcDT();
  makeDt(10000);
  AHRS(roll, pitch, yaw, dt);
  Serial.print(roll*RadToDeg); Serial.print(",");
  Serial.print(pitch*RadToDeg); Serial.print(",");
  yaw=wrap_PI(yaw);
  Serial.print(yaw*RadToDeg); //Serial.print(",");   
  Serial.print("\n");   
 // digitalWrite(12,!digitalRead(12)); 
//delay(0);
}
float wrap_PI(float angle_in_radians){
    if (angle_in_radians > 10*PI || angle_in_radians < -10*PI) {
        // for very large numbers use modulus
        angle_in_radians = fmodf(angle_in_radians, 2*PI);
    }
    while (angle_in_radians > PI) angle_in_radians -= 2*PI;
    while (angle_in_radians < -PI) angle_in_radians += 2*PI;
    return angle_in_radians;
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
void AHRS(float &roll, float &pitch, float &yaw,float dt){
  mpu.updateData( );   
  Vector norm = hmc.readNormalize();
  // acceleration --> angle
  digitalWrite(12,HIGH); 
  float accAngleX=-atan2(mpu._accel.y,-mpu._accel.z);
  float srtAccXY=sqrt(mpu._accel.y*mpu._accel.y+mpu._accel.z*mpu._accel.z);
  float accAngleY=atan2(mpu._accel.x,srtAccXY);
  // complementary filter roll, pitch
  roll=ALPHA* (roll+mpu._gyro.x*dt)+(1-ALPHA)*accAngleX;
  pitch=ALPHA* (pitch+mpu._gyro.y*dt)+(1-ALPHA)*accAngleY;
  // magnetometer --> heading angle
  float xd=-norm.YAxis, yd=norm.XAxis, zd=-norm.ZAxis;// internal HMC 
  //compensate heading angle to remove roll, pitch effects  
  float s_r=sin(roll), c_r=cos(roll),s_p=sin(pitch),c_p=cos(pitch);
  float xh=xd*c_p+yd*s_r*s_p+zd*c_r*s_p;
  float yh=yd*c_r+zd*s_r;
  float heading = atan2(yh, xh);
  // complementary filter yaw
  yaw=ALPHA*(yaw+mpu._gyro.z*dt)+(1-ALPHA)*heading; 
  digitalWrite(12,LOW);
}
