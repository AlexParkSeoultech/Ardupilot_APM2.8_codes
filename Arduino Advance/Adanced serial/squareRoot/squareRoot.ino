#include <NeoHWSerial.h>
String inString = "";
void setup() {
  pinMode(27,OUTPUT);
  NeoSerial.begin(9600);
  NeoSerial.attachInterrupt( recvData );
  inString.reserve(50);
}
void loop() {
  digitalWrite(27,HIGH); delay(1000); digitalWrite(27,LOW); delay(1000);
}
void recvData( uint8_t c) {
    if (c=='\n'){
       float f= inString.toFloat();
        NeoSerial.println(sqrt(f),5);
       inString="";
    }
    else
     inString+=(char)c;   // char로 변환이 중요
}
