#include <NeoHWSerial.h>
String inString = "";
float x,y;
bool getFrame=false;
void setup() {
  pinMode(27,OUTPUT);
  NeoSerial.begin( 9600 );
  NeoSerial.attachInterrupt( recvData );
  inString.reserve(50);
}
void loop() {
  digitalWrite(27,HIGH); delay(2000); digitalWrite(27,LOW); delay(2000);
}
void recvData( uint8_t c) {
    if (c=='\n'){
       y= inString.toFloat();
        NeoSerial.println(sqrt(x*x+y*y),5);
       inString="";
    }
    else if (c==','){
      x= inString.toFloat();
      inString="";
    }
    else
     inString+=(char)c;   // char로 변환이 중요
}
