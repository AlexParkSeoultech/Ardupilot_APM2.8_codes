#ifndef LEDBASIC_H    // Include guard
#define LEDBASIC_H
#include <Arduino.h>  // for C++ file
class LEDbasic {
        int LED_pin;
public:
        LEDbasic(int);
        ~LEDbasic();
        void on();
        void off();
        void blink(int);
        void flip();
};
#endif

