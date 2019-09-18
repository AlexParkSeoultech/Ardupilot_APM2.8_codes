#ifndef COMMON_H
#define COMMON_H
#include <Arduino.h>
#define RadToDeg (180/PI)
#define DEG100 (18000/PI)
struct Vectorf{float x;float y; float z;};
float wrap_PI(float angle_in_radians);
#define BARO_CS_PIN 40
#endif
