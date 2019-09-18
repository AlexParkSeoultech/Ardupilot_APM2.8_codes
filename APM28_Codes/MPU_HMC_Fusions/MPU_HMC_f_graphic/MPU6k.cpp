#include "MPU6k.h"
#include <SPI.h>
#include <Arduino.h>
static volatile uint8_t MPU6000::_new_data=0;
static volatile uint16_t MPU6000::_count=0;
static volatile int32_t MPU6000::_sum[7]={0};
MPU6000 mpu;
//================= Configuration of MPU6k
void MPU6000::configureMPU6000() {
  SPIwrite(MPUREG_PWR_MGMT_1,BIT_H_RESET);            delay(100);// eset device
  SPIwrite(MPUREG_PWR_MGMT_1,MPU_CLK_SEL_PLLGYROZ);   delay(1); //select GyroZ clock 
  SPIwrite(MPUREG_USER_CTRL,BIT_I2C_IF_DIS);          delay(1); //disable I2C interface
  SPIwrite(MPUREG_SMPLRT_DIV,0x04);                   delay(1); //Fsample=1Khz/(4+1)=200Hz
  SPIwrite(MPUREG_CONFIG,BITS_DLPF_CFG_98HZ);         delay(1); //DLPF = 98Hz (Gyro)
  SPIwrite(MPUREG_GYRO_CONFIG,BITS_FS_2000DPS);       delay(1); //Gyro scale 2000deg/s
  SPIwrite(MPUREG_ACCEL_CONFIG,BITS_AFS_4G);          delay(1); //accel scale at 4g(4096LSB/g)
  SPIwrite(MPUREG_INT_ENABLE,BIT_RAW_RDY_EN);         delay(1); //INT: Raw data ready
  SPIwrite(MPUREG_INT_PIN_CFG,BIT_INT_ANYRD_2CLEAR);  delay(1); //INT: Clear on any read
  attachInterrupt(EI_INT_6,dataReady,RISING);  // External Interrupt pin PE6 INT6
  initTimer(); 
}
void MPU6000::readData( ){
    if (_new_data == 0) return; // no new data then exit
    _new_data = 0;
    digitalWrite(MPU6K_CS_PIN, LOW);
    byte addr = MPUREG_ACCEL_XOUT_H | 0x80;// R/W bit
    SPI.transfer(addr);
    for (uint8_t i=0; i<7; i++) {
        _sum[i] += spi_transfer_16();
    }
   _count++;
    digitalWrite(MPU6K_CS_PIN, HIGH);
}
bool MPU6000::updateData( ) {
  int32_t sum[7];
  uint16_t count;
  float count_scale;
  while (_count == 0);   // wait for at least one sample
  cli();   // disable interrupts
  for (int i=0; i<7; i++) {
    sum[i] = _sum[i];
    _sum[i] = 0;
  }
  count = _count; 
  _count = 0;
  sei();   //enable interrupts
  count_scale = 1.0 / count;
  _gyro.x = _gyro_scale * _gyro_data_sign[0] * sum[_gyro_data_index[0]] * count_scale;
  _gyro.y = _gyro_scale * _gyro_data_sign[1] * sum[_gyro_data_index[1]] * count_scale;
  _gyro.z = _gyro_scale * _gyro_data_sign[2] * sum[_gyro_data_index[2]] * count_scale;
  _accel.x = _accel_scale * _accel_data_sign[0] * sum[_accel_data_index[0]] * count_scale;
  _accel.y = _accel_scale * _accel_data_sign[1] * sum[_accel_data_index[1]] * count_scale;
  _accel.z = _accel_scale * _accel_data_sign[2] * sum[_accel_data_index[2]] * count_scale;
  return true;
}
//=================== SPI Read/Write ==================
void MPU6000::SPIwrite(byte reg, byte data) {
  uint8_t dump;
  digitalWrite(MPU6K_CS_PIN,LOW);
  dump=SPI.transfer(reg);
  dump=SPI.transfer(data);
  digitalWrite(MPU6K_CS_PIN,HIGH);
}
uint8_t MPU6000::SPIread(byte reg) {
  uint8_t dump, return_value, addr=reg|0x80; // R/W bit
  digitalWrite(MPU6K_CS_PIN,LOW);
  dump=SPI.transfer(addr);
  return_value=SPI.transfer(0x00);
  digitalWrite(MPU6K_CS_PIN,HIGH);
  return return_value;
}
static int16_t MPU6000::spi_transfer_16(void) {
  uint8_t byte_H, byte_L;
  byte_H = SPI.transfer(0);
  byte_L = SPI.transfer(0);
  return (((int16_t)byte_H)<<8) | byte_L;
}
//================= Interrupts ==================
void MPU6000::dataReady(void) { 
    _new_data = 1;  // new data arrived for read
}
void MPU6000::initTimer(){
  TIMSK2 = 0;                     // Disable interrupts
  TCCR2A = 0;                     // normal counting mode
  TCCR2B = _BV(CS21) | _BV(CS22); // Set prescaler of clk/256 16usec
  TCNT2  = 100;                     // Set count=0
  TIFR2  = _BV(TOV2);             // clear previous interrupts;
  TIMSK2 = _BV(TOIE2);            // enable overflow interrupt
}
ISR(TIMER2_OVF_vect) {   
    mpu.readData();
    TCNT2  = 100;
}

