#include <NeoHWSerial.h>
uint8_t c;
void setup() {
  pinMode(27,OUTPUT);
  NeoSerial.begin( 9600 );
  NeoSerial.attachInterrupt( recvData );
}
void loop() {
  digitalWrite(27,HIGH); delay(2000); digitalWrite(27,LOW); delay(2000);
}
void recvData( uint8_t c) {
  NeoSerial.write( c );
}
