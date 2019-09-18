#include <SPI.h>
#include "MS5611.h"

uint32_t MS5611::_spi_read_adc() {
  uint8_t dump,byteH,byteM,byteL;
  uint32_t return_value;
  uint8_t addr = 0x00;
  digitalWrite(MS5611_CS, LOW);
  dump = SPI.transfer(addr);
  byteH = SPI.transfer(0);
  byteM = SPI.transfer(0);
  byteL = SPI.transfer(0);
  digitalWrite(MS5611_CS, HIGH);
  return_value = (((uint32_t)byteH)<<16) | (((uint32_t)byteM)<<8) | (byteL);
  return return_value;
}
void MS5611::_spi_write(uint8_t reg){
  uint8_t dump;
  digitalWrite(MS5611_CS, LOW);
  dump = SPI.transfer(reg);
  digitalWrite(MS5611_CS, HIGH);
}
uint16_t MS5611::_spi_read_16bits(uint8_t reg){
  uint8_t dump, byteH, byteL;
  uint16_t return_value;
  uint8_t addr = reg; // | 0x80; // Set MSB
  digitalWrite(MS5611_CS, LOW);
  dump = SPI.transfer(addr);
  byteH = SPI.transfer(0);
  byteL = SPI.transfer(0);
  digitalWrite(MS5611_CS, HIGH);
  return_value = ((uint16_t)byteH<<8) | (byteL);
  return return_value;
}
bool MS5611::_init(){
  pinMode(MS5611_CS, OUTPUT);  // Chip select Pin
  digitalWrite(MS5611_CS, HIGH);  delay(1);
  _spi_write(CMD_MS5611_RESET);   delay(4);
  // Read 6 calibration data
  C1 = _spi_read_16bits(CMD_MS5611_PROM_C1);
  C2 = _spi_read_16bits(CMD_MS5611_PROM_C2);
  C3 = _spi_read_16bits(CMD_MS5611_PROM_C3);
  C4 = _spi_read_16bits(CMD_MS5611_PROM_C4);
  C5 = _spi_read_16bits(CMD_MS5611_PROM_C5);
  C6 = _spi_read_16bits(CMD_MS5611_PROM_C6);
  //Send a command to read Temp first
  _spi_write(CMD_CONVERT_D2_OSR4096);
  _timer = micros();
  _state = 1;  Temp=0;   Press=0;
 // scheduler->register_process(   _update );
    return true;
}
void MS5611::_update(uint32_t tnow) {
   if (_sync_access) return;
   if (tnow - _timer < 9500) {return; } //
   _timer = tnow;
    if (_state == 1) {
      _s_D2 = _spi_read_adc();           // On state 1 we read temp
      _state++;
      _spi_write(CMD_CONVERT_D1_OSR4096);  // Command to read pressure
    } else if (_state == 5) {
      _s_D1 = _spi_read_adc();
      _state = 1;                     // Start again from state = 1
      _spi_write(CMD_CONVERT_D2_OSR4096); // Command to read temperature
      _updated = true;                          // New pressure reading
    } else {
      _s_D1 = _spi_read_adc();
      _state++;
      _spi_write(CMD_CONVERT_D1_OSR4096);  // Command to read pressure
      _updated = true;                         // New pressure reading
    }
}
uint8_t MS5611:: _read(){
   _sync_access = true;
    bool updated = _updated;
    _updated = 0;
    if (updated > 0) {
        D1 = _s_D1;
        D2 = _s_D2;
        _raw_press = D1;
        _raw_temp = D2;
    }
    _sync_access = false;
    _calculate();
    return updated ? 1 : 0;
}
void  MS5611::_calculate(){// Calculate Temp & compensated P in (Celsius degrees*100, mbar*100).
  int32_t dT;
  int64_t TEMP, OFF, SENS, P;
  // Formulas from datasheet
  dT = D2-((long)C5*256);
  TEMP = 2000 + ((int64_t)dT * C6)/8388608;
  OFF = (int64_t)C2 * 65536 + ((int64_t)C4 * dT ) / 128;
  SENS = (int64_t)C1 * 32768 + ((int64_t)C3 * dT) / 256;
  if (TEMP < 2000){   // second order temperature compensation
    int64_t T2 = (((int64_t)dT)*dT) >> 31;
    int64_t Aux_64 = (TEMP-2000)*(TEMP-2000);
    int64_t OFF2 = (5*Aux_64)>>1;
    int64_t SENS2 = (5*Aux_64)>>2;
    TEMP = TEMP - T2;
    OFF = OFF - OFF2;
    SENS = SENS - SENS2;
  }
  P = (D1*SENS/2097152 - OFF)/32768;
  Temp = TEMP;
  Press = P;
}
float MS5611::get_altitude() {
  float tmp_float;
  float Altitude;
  tmp_float = (Press / 101325.0);
  tmp_float = pow(tmp_float, 0.190295);
  Altitude = 44330.0 * (1.0 - tmp_float);
  return Altitude;
}
int32_t MS5611::get_pressure() {
  return Press;
}
int16_t MS5611::get_temperature() {
  return Temp/10; // callers want the temperature in 0.1C units
}
