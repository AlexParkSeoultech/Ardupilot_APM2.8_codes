#include <SPI.h>
#include "MPU6k.h"
#define INTRRUPT_PLOT  
#define BARO_CS_PIN 40
#define RadToDeg (180/PI)
#define ALPHA 0.96
extern MPU6000 mpu;
float roll=0, pitch=0, yaw=0,dt;
float gyAngleX=0, gyAngleY=0, gyAngleZ=0;
float kalmanFilter(float u, float y);
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
  calcDT();
  mpu.updateData( ); 
  float accAngleX=-atan2(mpu._accel.y,-mpu._accel.z);//*RadToDeg;
  float srtAccXY=sqrt(mpu._accel.y*mpu._accel.y+mpu._accel.z*mpu._accel.z);
  float accAngleY=atan2(mpu._accel.x,srtAccXY);//*RadToDeg;
  roll=ALPHA* (roll+mpu._gyro.x*dt)+(1-ALPHA)*accAngleX;
  float roll_kalman=kalmanFilter(mpu._gyro.x, accAngleX);
  pitch=ALPHA* (pitch+mpu._gyro.y*dt)+(1-ALPHA)*accAngleY;
  gyAngleX=gyAngleX+mpu._gyro.x*dt;
  Serial.print(roll*RAD_TO_DEG); Serial.print(",");
  Serial.print(accAngleX*RAD_TO_DEG);  Serial.print(",");
  Serial.print(gyAngleX*RAD_TO_DEG); Serial.print(",");   
  Serial.print(roll_kalman*RAD_TO_DEG);//Serial.print(",");
  Serial.print("\n");    
  delay(0);
}
void calcDT() {
  uint32_t newTime = micros();
  dt = (newTime - prevTime)/1000000.0;
  prevTime = newTime;  
}
float q1=0.001,q2=0.003, r1=0.03;
float kalmanFilter(float u, float y){
    static float x1=0, x2=0,p11=0,p12=0,p21=0, p22=0;
    //= Time Update State, error covariance
    x1+=(u-x2)*dt;
    p12+=-p22*dt;   p11-=(p21+p12)*dt+q1*dt;
    p21+=-p22*dt;   p22+=q2*dt;
    //= Measurement Update Gain, State, error covariance
    float s=p11+r1,k1=p11/s, k2=p21/s, e=y-x1;
    x1+=k1*e;       x2+=k2*e;
    p11*=(1-k1);    p12*=(1-k1);
    p21+=-k2*p11;   p22+=-k2*p12;
    return x1;
}

