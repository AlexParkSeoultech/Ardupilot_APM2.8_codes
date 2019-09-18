#ifndef AHRS_H
#define AHRS_H
#include "MPU6k.h"
#include "HMC5883L.h"
#include "common.h"
#define ALPHA 0.92

class AHRS{
public:
  void IMU_comp(float dt);
  void MARG_comp(float dt);
  void init();
  float   roll, pitch,  yaw;  
  float  alt_acc;
  int32_t   roll_sensor, pitch_sensor, yaw_sensor;
  int32_t   roll_rate, pitch_rate, yaw_rate;
};


#endif
