#include <Wire.h>
#include "HMC5883L.h"
void  HMC5883L::init(){
  setRange(HMC5883L_RANGE_1_3GA); //  1.3Ga/Lsb
  setMeasurementMode(HMC5883L_CONTINOUS);
  setDataRate(HMC5883L_DATARATE_30HZ);
  setSamples(HMC5883L_SAMPLES_8);
  setOffset(0, 0);  
}
bool HMC5883L::begin() {
    Wire.begin();
    if ((readRegister8(HMC5883L_REG_IDENT_A) != 0x48)
        || (readRegister8(HMC5883L_REG_IDENT_B) != 0x34)
        || (readRegister8(HMC5883L_REG_IDENT_C) != 0x33))
	      return false;
    setRange(HMC5883L_RANGE_1_3GA);
    setMeasurementMode(HMC5883L_CONTINOUS);
    setDataRate(HMC5883L_DATARATE_15HZ);
    setSamples(HMC5883L_SAMPLES_1);
    mgPerDigit = 0.92f;
    return true;
}
Vector HMC5883L::readRaw(void) {
    v.XAxis = readRegister16(HMC5883L_REG_OUT_X_M) - xOffset;
    v.YAxis = readRegister16(HMC5883L_REG_OUT_Y_M) - yOffset;
    v.ZAxis = readRegister16(HMC5883L_REG_OUT_Z_M);
    return v;
}
Vector HMC5883L::readNormalize(void) {
    v.XAxis = ((float)readRegister16(HMC5883L_REG_OUT_X_M) - xOffset) * mgPerDigit;
    v.YAxis = ((float)readRegister16(HMC5883L_REG_OUT_Y_M) - yOffset) * mgPerDigit;
    v.ZAxis = (float)readRegister16(HMC5883L_REG_OUT_Z_M) * mgPerDigit;
    return v;
}
void HMC5883L::setOffset(int xo, int yo) {
    xOffset = xo;    yOffset = yo;
}
void HMC5883L::setRange(hmc5883l_range_t range){
    switch(range)  {
    	case HMC5883L_RANGE_0_88GA:
    	    mgPerDigit = 0.073f;break;   	    
    	case HMC5883L_RANGE_1_3GA:
    	    mgPerDigit = 0.92f;break;//mGauss
    	case HMC5883L_RANGE_1_9GA:
    	    mgPerDigit = 1.22f;break;
    	case HMC5883L_RANGE_2_5GA:
    	    mgPerDigit = 1.52f;break;
    	case HMC5883L_RANGE_4GA:
    	    mgPerDigit = 2.27f;break;
    	case HMC5883L_RANGE_4_7GA:
    	    mgPerDigit = 2.56f;break;
    	case HMC5883L_RANGE_5_6GA:
    	    mgPerDigit = 3.03f;break;
    	case HMC5883L_RANGE_8_1GA:
    	    mgPerDigit = 4.35f;break;
    }
    writeRegister8(HMC5883L_REG_CONFIG_B, range << 5);
}
void HMC5883L::setMeasurementMode(hmc5883l_mode_t mode){
    uint8_t value;
    value = readRegister8(HMC5883L_REG_MODE);
    value &= 0b11111100;
    value |= mode;
    writeRegister8(HMC5883L_REG_MODE, value);
}
void HMC5883L::setDataRate(hmc5883l_dataRate_t dataRate) {
    uint8_t value;
    value = readRegister8(HMC5883L_REG_CONFIG_A);
    value &= 0b11100011;
    value |= (dataRate << 2);
    writeRegister8(HMC5883L_REG_CONFIG_A, value);
}
void HMC5883L::setSamples(hmc5883l_samples_t samples){
    uint8_t value;
    value = readRegister8(HMC5883L_REG_CONFIG_A);
    value &= 0b10011111;
    value |= (samples << 5);
    writeRegister8(HMC5883L_REG_CONFIG_A, value);
}
void HMC5883L::writeRegister8(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}
uint8_t HMC5883L::readRegister8(uint8_t reg){
    uint8_t value;
    Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.requestFrom(HMC5883L_ADDRESS, 1);
    while(!Wire.available()) {}; // Polling
    value = Wire.read();
    Wire.endTransmission();
    return value;
}
int16_t HMC5883L::readRegister16(uint8_t reg){
    int16_t value;
    Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.requestFrom(HMC5883L_ADDRESS, 2);
    while(!Wire.available()) {};
    uint8_t vha = Wire.read();
    uint8_t vla = Wire.read();
    Wire.endTransmission();
    value = vha << 8 | vla;
    return value;
}
