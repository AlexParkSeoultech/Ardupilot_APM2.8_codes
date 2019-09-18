#include "timerSetup.h"
void outputCh(unsigned char ch, uint16_t pwm){
  pwm=constrain(pwm,MIN_PULSEWIDTH,MAX_PULSEWIDTH);
  pwm<<=1;   // pwm*2; Regiter 2000 ~ 4000
 switch(ch)   {
    case 0:  OCR1B=pwm; break;  // out1
    case 1:  OCR1A=pwm; break;  // out2
    case 2:  OCR4C=pwm; break;  // out3
    case 3:  OCR4B=pwm; break;  // out4
    case 4:  OCR4A=pwm; break;  // out5
    case 5:  OCR3C=pwm; break;  // out6
    case 6:  OCR3B=pwm; break;  // out7
    case 7:  OCR3A=pwm; break;  // out8
    case 9:  OCR5B=pwm; break;  // out10 x
    case 10: OCR5C=pwm; break;  // out11 x
  }
}
void enableOut(uint8_t ch){
  switch(ch) {
    case 0: TCCR1A |= (1<<COM1B1); break; // CH_1 : OC1B
    case 1: TCCR1A |= (1<<COM1A1); break; // CH_2 : OC1A
    case 2: TCCR4A |= (1<<COM4C1); break; // CH_3 : OC4C
    case 3: TCCR4A |= (1<<COM4B1); break; // CH_4 : OC4B
    case 4: TCCR4A |= (1<<COM4A1); break; // CH_5 : OC4A
    case 5: TCCR3A |= (1<<COM3C1); break; // CH_6 : OC3C
    case 6: TCCR3A |= (1<<COM3B1); break; // CH_7 : OC3B
    case 7: TCCR3A |= (1<<COM3A1); break; // CH_8 : OC3A
    case 9: TCCR5A |= (1<<COM5B1); break; // CH_10 : OC5B
    case 10: TCCR5A |= (1<<COM5C1); break; // CH_11 : OC5C
  }
}
void disableOut(uint8_t ch) {
  switch(ch) {
    case 0: TCCR1A &= ~(1<<COM1B1); break; // CH_1 : OC1B
    case 1: TCCR1A &= ~(1<<COM1A1); break; // CH_2 : OC1A
    case 2: TCCR4A &= ~(1<<COM4C1); break; // CH_3 : OC4C
    case 3: TCCR4A &= ~(1<<COM4B1); break; // CH_4 : OC4B
    case 4: TCCR4A &= ~(1<<COM4A1); break; // CH_5 : OC4A
    case 5: TCCR3A &= ~(1<<COM3C1); break; // CH_6 : OC3C
    case 6: TCCR3A &= ~(1<<COM3B1); break; // CH_7 : OC3B
    case 7: TCCR3A &= ~(1<<COM3A1); break; // CH_8 : OC3A
    case 9: TCCR5A &= ~(1<<COM5B1); break; // CH_10 : OC5B
    case 10: TCCR5A &= ~(1<<COM5C1); break; // CH_11 : OC5C
  }
}
void initTimers(){
  //TIMER1: WGM 1110, TOP=ICR1, CS=2, OUT1,OUT2
  pinMode(12,OUTPUT); // OUT1 (PB6/OC1B)
  pinMode(11,OUTPUT); // OUT2 (PB5/OC1A)
  TCCR1A =((1<<WGM11));
  TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);
  ICR1 = 40000; // 0.5us tick => 50hz freq
  OCR1A = 0xFFFF; OCR1B = 0xFFFF;//disable 
 //TIMER4: WGM 1110, TOP=ICR4, CS=2, OUT3,OUT4,OUT5
  pinMode(8,OUTPUT); // OUT3 (PH5/OC4C)
  pinMode(7,OUTPUT); // OUT4 (PH4/OC4B)
  pinMode(6,OUTPUT); // OUT5 (PH3/OC4A)
  TCCR4A =((1<<WGM41));
  TCCR4B = (1<<WGM43)|(1<<WGM42)|(1<<CS41);
  OCR4A = 0xFFFF; OCR4B = 0xFFFF; OCR4C = 0xFFFF;
  ICR4 = 40000; // 0.5us tick => 50hz freq
  //TIMER3: WGM 1110, TOP=ICR3, CS=2, OUT6,OUT7,OUT8
  pinMode(3,OUTPUT); // OUT6 (PE5/OC3C)
  pinMode(2,OUTPUT); // OUT7 (PE4/OC3B)
  pinMode(5,OUTPUT); // OUT8 (PE3/OC3A)
  TCCR3A =((1<<WGM31));
  TCCR3B = (1<<WGM33)|(1<<WGM32)|(1<<CS31);
  OCR3A = 0xFFFF; OCR3B = 0xFFFF; OCR3C = 0xFFFF;
  ICR3 = 40000; // 0.5us tick => 50hz freq
  //TIMER5: WGM 1111, TOP=OCR5A, CS=2, PPM,OUT10,OUT11
  pinMode(48, INPUT);  // PPM Input(PL1/ICP5)
  pinMode(45, OUTPUT); // OUT10 (PL4/OC5B)
  pinMode(44, OUTPUT); // OUT11 (PL5/OC5C)
  TCCR5A =((1<<WGM50)|(1<<WGM51));
  TCCR5B = ((1<<WGM53)|(1<<WGM52)|(1<<CS51)|(1<<ICES5)); //Rising
  OCR5A = 40000; // 0.5us tick => 50hz freq. 
//  isr_reg->register_signal( ISR_REGISTRY_TIMER5_CAPT, _timer5_capt_cb );
 // TIMSK5 |= (1<<ICIE5); // Enable Input Capture interrupt
}
