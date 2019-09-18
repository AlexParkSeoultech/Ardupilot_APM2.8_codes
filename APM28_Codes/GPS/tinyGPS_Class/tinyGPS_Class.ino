#include <NeoHWSerial.h>
#include "GPS.h"
#define PCBaud 115200
GPS gps;
void setup() {
  NeoSerial.begin(PCBaud);
  gps.init();
}
void loop(){
  if(gps.available()) gps.update();
  NeoSerial.print("Time= ");NeoSerial.print(gps.time.hour);
  NeoSerial.print(":");NeoSerial.print(gps.time.min);
  NeoSerial.print(":");NeoSerial.print(gps.time.sec);
  NeoSerial.print(", Alt= "); NeoSerial.print(gps.loca.alt);
  NeoSerial.print(", Lat= "); NeoSerial.print(gps.loca.lat);
  NeoSerial.print(", Lng=");NeoSerial.print(gps.loca.lng);
  NeoSerial.print(", Crs=");NeoSerial.println(gps.courseTo(37.63,127.08,37.63,126.99));
  delay(100);
}

//  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
//  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
//  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
//  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
//  printInt(gps.location.age(), gps.location.isValid(), 5);
//  printDateTime(gps.date, gps.time);
//  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
//  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
//  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
//  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);
//
//  unsigned long distanceKmToLondon =
//    (unsigned long)TinyGPSPlus::distanceBetween(
//      gps.location.lat(),
//      gps.location.lng(),
//      LONDON_LAT, 
//      LONDON_LON) / 1000;
//  printInt(distanceKmToLondon, gps.location.isValid(), 9);
//
//  double courseToLondon =
//    TinyGPSPlus::courseTo(
//      gps.location.lat(),
//      gps.location.lng(),
//      LONDON_LAT, 
//      LONDON_LON);
//
//  printFloat(courseToLondon, gps.location.isValid(), 7, 2);
//
//  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);
//
//  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);
//
//  printInt(gps.charsProcessed(), true, 6);
//  printInt(gps.sentencesWithFix(), true, 10);
//  printInt(gps.failedChecksum(), true, 9);
//  Serial.println();
  
 

 // if (millis() > 5000 && gps.charsProcessed() < 10)
 //  NeoSerial.println(F("No GPS data received: check wiring"));


// This custom version of delay() ensures that the gps object
// is being "fed".
//static void smartDelay(unsigned long ms)
//{
//  unsigned long start = millis();
//  do 
//  {
//    while (ss.available())
//      gps.encode(ss.read());
//  } while (millis() - start < ms);
//}

//static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
//{
//  if (!d.isValid())
//  {
//    NeoSerial.print(F("********** "));
//  }
//  else
//  {
//    char sz[32];
//    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
//    NeoSerial.print(sz);
//  }
//  
//  if (!t.isValid())
//  {
//    NeoSerial.print(F("******** "));
//  }
//  else
//  {
//    char sz[32];
//    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
//    Serial.print(sz);
//  }
// // smartDelay(0);
//}

