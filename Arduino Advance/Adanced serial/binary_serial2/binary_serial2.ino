#define omega 0.3
int j=0;
union {float intval; byte bytes[2];} sx;
char sync[2]={0xAA,0xBB};
void setup() {
  Serial.begin(115200);
}
void loop() {
    float t=omega*DEG_TO_RAD*j;
    float fdata=2000.*sin(t);
    sendPacket(fdata);
    delay(1);
    j++;
}
void sendPacket(float f) {
  byte* b = (byte *) &f;
  Serial.write(sync,2);
  Serial.write(b,4);
}

