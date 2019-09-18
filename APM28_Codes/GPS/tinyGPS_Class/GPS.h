#ifndef __GPS_h
#define __GPS_h
#define GPSBaud 9600
#include <NeoHWSerial.h>
#include <TinyGPS++.h>
#include <Arduino.h>
void  recvData(uint8_t c);
class GPS{
   struct TIME{uint8_t hour,min,sec;};
   struct DATE{uint8_t year,month,day;};
   struct LOCA{float lat,lng,alt;};
  public:
    void init();
    bool available();
    void  update();
    float distanceBetween(float lat1,float long1,float lat2, float long2);
    float courseTo(float lat1,float long1, float lat2,float long2);
    TIME time;
    DATE date;
    LOCA loca;
};
#endif 
