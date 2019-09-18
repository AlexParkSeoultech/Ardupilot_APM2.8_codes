#include "LEDBasic.h" //include the declaration for this class
//const byte LED_PIN = 13; //use the LED @ Arduino pin 13
LEDbasic::LEDbasic(int pin){    //<<constructor>> 
   LED_pin=pin;
    pinMode(LED_pin, OUTPUT); 
}
LEDbasic::~LEDbasic(){/*nothing to destruct*/} //<<destructor>>
void LEDbasic::on(){
        digitalWrite(LED_pin,HIGH);
}
void LEDbasic::off(){//turn the LED off
        digitalWrite(LED_pin,LOW);
}
void LEDbasic::flip(){//turn the LED off
        digitalWrite(LED_pin,!digitalRead(LED_pin));
}
void LEDbasic::blink(int time){//blink the LED
        on();                  
        delay(time/2);  //wait half of period
        off();                  
        delay(time/2); 
}

