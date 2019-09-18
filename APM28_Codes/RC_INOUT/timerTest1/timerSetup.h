#ifndef __TIMERSETUP_H__
#define __TIMERSETUP_H__
#define NUM_CHANNELS 8
#define MIN_PULSEWIDTH 900
#define MAX_PULSEWIDTH 2100
#include <Arduino.h>
void outputCh(unsigned char ch, uint16_t pwm);
void enableOut(uint8_t ch);
void disableOut(uint8_t ch);
void initTimers();
#endif

