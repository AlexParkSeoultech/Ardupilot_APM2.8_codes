#ifndef COMMON_H
#define COMMON_H
#include <Arduino.h>
#define RadToDeg (180/PI)
#define DEG100 (18000/PI)
#define BARO_CS_PIN 40
enum {OUT1, OUT2, OUT3, OUT4, OUT5};
enum {ROLL_IN,PITCH_IN, THROTTLE_IN, YAW_IN, AUX_IN};
struct Vectorf{float x;float y; float z;};
float wrap_PI(float angle_in_radians);


#endif
