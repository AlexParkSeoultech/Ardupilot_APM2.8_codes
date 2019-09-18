uint32_t period=50000,prevTime;
void setup() {
  Serial.begin(115200);
  pinMode(27,OUTPUT);
  pinMode(25,OUTPUT);
  prevTime=micros();
  initTimer();
}
void loop() {digitalWrite(25,LOW);delay(500);digitalWrite(25,HIGH);delay(500); }
void initTimer(){
  TIMSK2 = 0;                 // Disable interrupts
  TCCR2A = 0;                 // normal counting mode
  TCCR2B = _BV(CS21) | _BV(CS22); // Set prescaler of clk/256 16usec
  TCNT2  = 192;                 // Set count to zero, so it goes off right away.
  TIFR2  = _BV(TOV2);         // clear pending interrupts;
  TIMSK2 = _BV(TOIE2);        // enable the overflow interrupt
}
void periodic(){
  uint32_t curTime=micros(); TCNT2  = 192;
  if (curTime-prevTime<period) return;
    prevTime=curTime;
    Serial.println("1");   
    digitalWrite(27, !digitalRead(27));
}
ISR(TIMER2_OVF_vect) {  //extern "C" 
    periodic();
}
