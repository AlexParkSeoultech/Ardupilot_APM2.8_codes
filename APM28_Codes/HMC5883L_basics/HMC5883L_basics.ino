#include <Wire.h>
#include "HMC5883L.h"
HMC5883L hmc;
void setup() {
  Serial.begin(115200);
   while (!hmc.begin()) delay(500);
   hmc.init();
}
void loop() {
//  Tilt compensation
//  float Xh = mag.XAxis * cosPitch + mag.ZAxis * sinPitch;
//  float Yh = mag.XAxis * sinRoll * sinPitch + mag.YAxis * cosRoll - mag.ZAxis * sinRoll * cosPitch;
//  float heading = atan2(Yh, Xh);
  Vector norm = hmc.readNormalize();
  //float xd=-norm.YAxis, yd=norm.XAxis, zd=-norm.ZAxis;// internal HMC
  float xd=norm.XAxis, yd=-norm.YAxis, zd=norm.ZAxis;  //external HMC [외부 지자기 센서
  float heading = atan2(yd, xd);  //external HMC -atan2
  float declinationAngle =-(8.0+ (29.0/60.0))*DEG_TO_RAD;  // seoul -8o29' NEGTIVE(WEST)
  heading += declinationAngle;
  float headingDegrees = heading * RAD_TO_DEG; 
  // Output
  //Serial.print(norm.XAxis);Serial.print(":");
 // Serial.print(norm.YAxis);Serial.print(":"); 
 // Serial.print(norm.ZAxis); Serial.print(":");
  Serial.print(headingDegrees);  Serial.println();

  delay(1);
}
