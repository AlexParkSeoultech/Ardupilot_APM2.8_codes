class Flicker{
  int LED_pin, intval;
  uint32_t prevMillis;
  public: 
    Flicker(int pinN,long intv){
      LED_pin=pinN;intval=intv;
      pinMode(LED_pin, OUTPUT);  
      prevMillis=millis();
     }
    void update() {
      uint32_t curMillis = millis();
      if( curMillis-prevMillis> intval ) {
        prevMillis = curMillis; 
        digitalWrite(LED_pin,!digitalRead(LED_pin));
      }
    }
};
Flicker LEDblue(25,100),LEDred(27,1000);
void setup() { }
void loop() {
  LEDblue.update();
  LEDred.update();
}


