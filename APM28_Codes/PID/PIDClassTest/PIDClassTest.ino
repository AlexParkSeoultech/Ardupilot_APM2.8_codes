#include "AC_PID.h"
// default PID values
#define TEST_P 0.5
#define TEST_I 0.5
#define TEST_D 0.2
#define TEST_IMAX 20
AC_PID ratePID(TEST_P, TEST_I, TEST_D, TEST_IMAX), angPID(TEST_P, TEST_I, TEST_D, TEST_IMAX);
int count=0;
float dt=0.01;
uint32_t prevTime=micros();
void setup() {
    Serial.begin(115200);
    angPID(0.7,0.8,0.5,10);
}
void loop() {
  makeDt(10000);
  float t= 0.01*count;
  int error_r=100*sin(t), error_a=50*cos(t);
  int32_t pTerm_r=ratePID.get_p(error_r);
  int32_t iTerm_r=ratePID.get_i(error_r,dt);
  int32_t dTerm_r=ratePID.get_d(error_r,dt);
  int32_t control_r= pTerm_r+ iTerm_r+ dTerm_r;
  int32_t pTerm_a=angPID.get_p(error_a);
  int32_t iTerm_a=angPID.get_i(error_a,dt);
  int32_t dTerm_a=angPID.get_d(error_a,dt);
  int32_t control_a= pTerm_a+ iTerm_a+ dTerm_a; 
 // int32_t control=ratePID.get_pid(error,dt);
//  Serial.print(error_r);Serial.print(",");Serial.print(pTerm_r);Serial.print(",");Serial.print(iTerm_r);Serial.print(",");
//  Serial.print(dTerm_r);
  Serial.print(error_r);Serial.print(",");Serial.print(control_r);Serial.print(",");Serial.print(error_a);Serial.print(",");
  Serial.print(control_a);
//  Serial.print(error);Serial.print(",");Serial.print( control);Serial.print(",");Serial.print(ratePID.get_integrator());
  Serial.print("\n");
  count++;
}
void makeDt(uint32_t p){
  uint32_t newTime;
  do {newTime = micros();}while (newTime - prevTime<p);
  prevTime = newTime;
}

