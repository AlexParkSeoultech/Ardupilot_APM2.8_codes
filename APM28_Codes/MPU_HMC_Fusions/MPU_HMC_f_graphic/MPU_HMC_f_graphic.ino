#include <SPI.h>
#include "MPU6k.h"
#include <Wire.h>
#include "HMC5883L.h"
#define BARO_CS_PIN 40
#define RadToDeg (180/PI)
#define ALPHA 0.96
extern MPU6000 mpu;
HMC5883L hmc;
union{ float s;  uint8_t data[4];} rpy;
unsigned char sync[2]={0xaa,0xaa};
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
  while (!hmc.begin()) delay(500);
  hmc.init();
}
void loop() {
  //calcDT();
  makeDt(10000);
  AHRS(roll, pitch, yaw,dt);

 digitalWrite(12,!digitalRead(12));  

}
void AHRS(float &roll, float &pitch, float &yaw, float dt){
  Vector norm = hmc.readNormalize();
  mpu.updateData( ); 
  float accAngleX=-atan2(mpu._accel.y,-mpu._accel.z);//*RadToDeg;
  float srtAccXY=sqrt(mpu._accel.y*mpu._accel.y+mpu._accel.z*mpu._accel.z);
  float accAngleY=atan2(mpu._accel.x,srtAccXY);//*RadToDeg;
  float xd=-norm.YAxis, yd=norm.XAxis, zd=-norm.ZAxis;// internal HMC 
  float s_r=sin(roll), c_r=cos(roll),s_p=sin(pitch),c_p=cos(pitch);
  float xh=xd*c_p+yd*s_r*s_p+zd*c_r*s_p;
  float yh=yd*c_r+zd*s_r;
  float heading = atan2(yh, xh);
  roll=ALPHA* (roll+mpu._gyro.x*dt)+(1-ALPHA)*accAngleX;
  pitch=ALPHA* (pitch+mpu._gyro.y*dt)+(1-ALPHA)*accAngleY;
  yaw=ALPHA*(yaw+mpu._gyro.z*dt)+(1-ALPHA)*heading; 
  yaw= wrap_PI(yaw);
    Serial.write(sync,2);
  rpy.s=roll;
  Serial.write(rpy.data,4);
  rpy.s=pitch;
  Serial.write(rpy.data,4);
  rpy.s=yaw;
  Serial.write(rpy.data,4);
  rpy.s=xd/200;
  Serial.write(rpy.data,4);
  rpy.s=yd/200;
  Serial.write(rpy.data,4);
  rpy.s=zd/200;
  Serial.write(rpy.data,4);
  rpy.s=xh/200;
  Serial.write(rpy.data,4);
  rpy.s=yh/200;
  Serial.write(rpy.data,4);
 Serial.print("\n");   
}
float wrap_PI(float a) {
  if (a > PI)  a -=2*PI;
  if (a < -PI) a += 2*PI;
  return a;
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
