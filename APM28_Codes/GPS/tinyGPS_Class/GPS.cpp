#include "GPS.h"
TinyGPSPlus g;
void GPS::init(){
  NeoSerial1.begin(GPSBaud);
  NeoSerial1.attachInterrupt( recvData );
  delay(1000);
}
bool GPS::available(){
  bool a=g.altitude.isValid()&& g.altitude.isUpdated();
  bool b=g.location.isValid()&&g.location.isUpdated();
  return (a||b)? 1:0;
}
void GPS::update(){
  loca.alt=g.altitude.meters();
  loca.lat=g.location.lat();
  loca.lng=g.location.lng();
  time.hour=(g.time.hour()+9)%24; // UMT +9 hour
  time.min=g.time.minute();
  time.sec=g.time.second();
}
float GPS::distanceBetween(float lat1,float long1,float lat2, float long2){
  return g.distanceBetween(lat1, long1, lat2, long2);
}
float GPS::courseTo(float lat1,float long1, float lat2,float long2){
  float ang = g.courseTo(lat1, long1, lat2, long2); 
  return (ang>180)? ang-360:ang;  //+- 180 dgree
}
void  recvData(uint8_t c){
    g.encode((char)c);
}
