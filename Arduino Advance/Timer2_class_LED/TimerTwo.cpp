#include "TimerTwo.h"
#include "avr/interrupt.h"
_procedure  Timer2::_proc;
void Timer2::init(_procedure proc){
  TIMSK2 = 0;                 
  TCCR2A = 0;                 
  TCCR2B = _BV(CS21) | _BV(CS22); //Set prescaler (110) -> clk/256 -> 16usec
  TCNT2  = 194;               
  TIFR2  = _BV(TOV2);         
  TIMSK2 = _BV(TOIE2);        
  _proc=proc;
}
ISR(TIMER2_OVF_vect) {   
   Timer2::_proc ();  //excute _proc() function
   TCNT2  = 194;  
}
