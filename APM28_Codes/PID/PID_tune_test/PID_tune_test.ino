//#include "AC_PID.h"
#include "AHRS.h"
#include "rcInOut.h"
#define eps 100
#define TEST_P 0.5
#define TEST_I 0.5
#define TEST_D 0.2
#define TEST_IMAX 200
extern RCINOUT radio;
AHRS ahrs;
//AC_PID pitchRatePID(TEST_P, TEST_I, TEST_D, TEST_IMAX), pitchAngPID(TEST_P, TEST_I, TEST_D, TEST_IMAX);
uint32_t prevTime;
int16_t roll_target, pitch_target, yaw_target,throttle_target=1000;
int16_t U1, U2, U3, U4;
void setup() {
  Serial.begin(115200);  
  ahrs.init();
  radio.init();
  radio.enableOut(OUT1);radio.enableOut(OUT2); radio.enableOut(OUT3); radio.enableOut(OUT4);
   U1=1000;
  applyPWM(); delay(3000);
  prevTime = micros();
}
void loop() {
 //calcDT();
  makeDt(5000);
// ahrs.MARG_comp(0.01);
 ahrs.IMU_comp(0.005);
 if (radio.getState())  {
  int16_t p=map(radio.inputCh(PITCH_IN),1000,2000,-4500,4500);
  pitch_target=(( p< -eps)||( p > eps))? p:0;
  int16_t t=radio.inputCh(THROTTLE_IN);
  throttle_target=( t> 1100)? t:1000;  
 }
 U1=throttle_target;
 applyPWM();
 //Serial.print(ahrs.roll*RadToDeg); Serial.print(",");
// Serial.print(ahrs.pitch*RadToDeg); Serial.print(",");
 //float y=wrap_PI(ahrs.yaw);
// Serial.print(ahrs.yaw*RadToDeg); //Serial.print(",");
  Serial.print( pitch_target); Serial.print(",");  
  Serial.print( throttle_target); //Serial.print(",");   
  Serial.print("\n");   
 // digitalWrite(12,!digitalRead(12)); 
//delay(0);

}
void makeDt(uint32_t p){
  uint32_t newTime;
  do {newTime = micros();}while (newTime - prevTime<p);
  prevTime = newTime;
}
void applyPWM(){
  radio.outputCh(OUT1, U1);
  radio.outputCh(OUT2, U1);
  radio.outputCh(OUT3, U1);
  radio.outputCh(OUT4, U1);
}

