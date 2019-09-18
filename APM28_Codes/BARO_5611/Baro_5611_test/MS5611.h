#ifndef __MS5611_H__
#define __MS5611_H__
#define MS5611_CS 40
#define CMD_MS5611_RESET 0x1E
#define CMD_MS5611_PROM_Setup 0xA0
#define CMD_MS5611_PROM_C1 0xA2
#define CMD_MS5611_PROM_C2 0xA4
#define CMD_MS5611_PROM_C3 0xA6
#define CMD_MS5611_PROM_C4 0xA8
#define CMD_MS5611_PROM_C5 0xAA
#define CMD_MS5611_PROM_C6 0xAC
#define CMD_MS5611_PROM_CRC 0xAE
#define CMD_CONVERT_D1_OSR4096 0x48   // Maximum resolution (oversampling)
#define CMD_CONVERT_D2_OSR4096 0x58   // Maximum resolution (oversampling)

uint32_t   _spi_read_adc();
void _spi_write(uint8_t reg);
uint16_t _spi_read_16bits(uint8_t reg);
bool _init(void );
void _update(uint32_t tnow);
uint8_t   _read();
void   _calculate();
float get_altitude();
int32_t get_pressure();
int16_t get_temperature() ;
#endif
