#ifndef __RCINOUT_H__
#define __RCINOUT_H__
#define NUM_CHANNELS 8
#define MIN_PULSEWIDTH 900
#define MAX_PULSEWIDTH 2100
#include <Arduino.h>
class RCINOUT{
   volatile uint16_t _PWM_RAW[NUM_CHANNELS] 
          = {2400,2400,2400,2400,2400,2400,2400,2400};
    volatile uint8_t _radio_status=0;    
  public:
    void outputCh(unsigned char ch, uint16_t pwm);
    void enableOut(uint8_t ch);
    void disableOut(uint8_t ch);
    void init();
    unsigned char getState(void);
    uint16_t inputCh(unsigned char ch);
    void _timer5_capt(void);
};
#endif

