#define omega 0.3
int j=0;
union {int intval; byte bytes[2];} sx;
char sync[2]={0xAA,0xBB};
void setup() {
  Serial.begin(115200);
}
void loop() {
    float t=omega*DEG_TO_RAD*j;
    sx.intval=2000.*sin(t);
    Serial.write(sync,2);
    Serial.write(sx.bytes,2);
    delay(1);
    j++;
}

