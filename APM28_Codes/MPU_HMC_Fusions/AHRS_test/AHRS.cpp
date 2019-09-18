#include "AHRS.h"
extern MPU6000 mpu;
HMC5883L hmc;
void AHRS::init(){
  pinMode(BARO_CS_PIN, OUTPUT);  pinMode(12, OUTPUT);
  pinMode(MPU6K_CS_PIN, OUTPUT); digitalWrite(MPU6K_CS_PIN, HIGH);
  digitalWrite(BARO_CS_PIN, HIGH);   //Deselect Barometer
  mpu.configureMPU6000();  // configure chip
  while (!hmc.begin()) delay(500);
  hmc.init();
}
void AHRS::IMU_comp(float dt){
  mpu.updateData( );   
  Vectorf m = hmc.readNormalize();
  float accAngleX=-atan2(mpu._accel.y,-mpu._accel.z);
  float srtAccXY=sqrt(mpu._accel.y*mpu._accel.y+mpu._accel.z*mpu._accel.z);
  float accAngleY=atan2(mpu._accel.x,srtAccXY);
    // complementary filter roll, pitch
  roll=ALPHA* (roll+mpu._gyro.x*dt)+(1-ALPHA)*accAngleX;
  pitch=ALPHA* (pitch+mpu._gyro.y*dt)+(1-ALPHA)*accAngleY; 
  roll_sensor=roll*DEG100;
  pitch_sensor=pitch*DEG100;
  roll_rate=mpu._gyro.x*DEG100;
  pitch_rate=mpu._gyro.y*DEG100;
  yaw_rate=mpu._gyro.z*DEG100;
  alt_acc=-mpu._accel.z-9.1;
}
 void AHRS::MARG_comp(float dt){
   mpu.updateData( );   
  Vectorf m = hmc.readNormalize();
  float accAngleX=-atan2(mpu._accel.y,-mpu._accel.z);
  float srtAccXY=sqrt(mpu._accel.y*mpu._accel.y+mpu._accel.z*mpu._accel.z);
  float accAngleY=atan2(mpu._accel.x,srtAccXY);
    // complementary filter roll, pitch
  roll=ALPHA* (roll+mpu._gyro.x*dt)+(1-ALPHA)*accAngleX;
  pitch=ALPHA* (pitch+mpu._gyro.y*dt)+(1-ALPHA)*accAngleY;
  // magnetometer --> heading angle
  float xd=-m.y, yd=m.x, zd=-m.z;// internal HMC 
  //compensate heading angle to remove roll, pitch effects  
  float s_r=sin(roll), c_r=cos(roll),s_p=sin(pitch),c_p=cos(pitch);
  float xh=xd*c_p+yd*s_r*s_p+zd*c_r*s_p;
  float yh=yd*c_r+zd*s_r;
  float heading = atan2(yh, xh);
  // complementary filter yaw
  yaw=ALPHA*(yaw+mpu._gyro.z*dt)+(1-ALPHA)*heading; 
  roll_sensor=roll*DEG100;
  pitch_sensor=pitch*DEG100; 
  yaw_sensor=yaw*DEG100; 
  roll_rate=mpu._gyro.x*DEG100;
  pitch_rate=mpu._gyro.y*DEG100;
  yaw_rate=mpu._gyro.z*DEG100;  
  alt_acc=-mpu._accel.z-9.1;
}


