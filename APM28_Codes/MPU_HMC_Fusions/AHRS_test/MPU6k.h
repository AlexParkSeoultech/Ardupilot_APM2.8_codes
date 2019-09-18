#include "common.h"
#ifndef __MPU6K_H__
#define __MPU6K_H__
#include <stdint.h>
#include <Arduino.h>
//===============Registers of MPU6000
#define MPUREG_WHOAMI       0x75
#define MPUREG_SMPLRT_DIV   0x19
#define MPUREG_CONFIG       0x1A 
#define MPUREG_GYRO_CONFIG  0x1B  
#define MPUREG_ACCEL_CONFIG 0x1C  
#define MPUREG_FIFO_EN      0x23
#define MPUREG_INT_PIN_CFG  0x37
#define MPUREG_INT_ENABLE   0x38
#define MPUREG_INT_STATUS   0x3A
#define MPUREG_ACCEL_XOUT_H 0x3B 
#define MPUREG_ACCEL_XOUT_L 0x3C 
#define MPUREG_ACCEL_YOUT_H 0x3D 
#define MPUREG_ACCEL_YOUT_L 0x3E 
#define MPUREG_ACCEL_ZOUT_H 0x3F 
#define MPUREG_ACCEL_ZOUT_L 0x40 
#define MPUREG_TEMP_OUT_H   0x41
#define MPUREG_TEMP_OUT_L   0x42
#define MPUREG_GYRO_XOUT_H  0x43 
#define MPUREG_GYRO_XOUT_L  0x44 
#define MPUREG_GYRO_YOUT_H  0x45 
#define MPUREG_GYRO_YOUT_L  0x46 
#define MPUREG_GYRO_ZOUT_H  0x47 
#define MPUREG_GYRO_ZOUT_L  0x48 
#define MPUREG_USER_CTRL    0x6A 
#define MPUREG_PWR_MGMT_1   0x6B 
#define MPUREG_PWR_MGMT_2   0x6C 
#define MPUREG_FIFO_COUNTH  0x72
#define MPUREG_FIFO_COUNTL  0x73
#define MPUREG_FIFO_R_W     0x74
//============= Configuration BITS
#define BIT_SLEEP 0x40
#define BIT_H_RESET 0x80
#define BITS_CLKSEL 0x07
#define MPU_CLK_SEL_PLLGYROX 0x01
#define MPU_CLK_SEL_PLLGYROZ 0x03
#define MPU_EXT_SYNC_GYROX 0x02
#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18
#define BITS_FS_MASK                0x18
#define BITS_AFS_2G                 0x00
#define BITS_AFS_4G                 0x08
#define BITS_AFS_8G                 0x10
#define BITS_AFS_16G                0x18
#define BITS_DLPF_CFG_256HZ_NOLPF2  0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07
#define BIT_INT_ANYRD_2CLEAR        0x10
#define BIT_RAW_RDY_EN              0x01
#define BIT_I2C_IF_DIS              0x10
#define BIT_INT_STATUS_DATA         0x01
//====================================
#define MPU6K_CS_PIN 53
#define EI_INT_6 6

const float _gyro_scale = PI/180*2000./32768.0; 
const float _accel_scale =4*9.81 / 32768.0;
const uint8_t _gyro_data_index[3]  = { 5, 4, 6 };
const int8_t  _gyro_data_sign[3]   = { 1, 1, -1 };
const uint8_t _accel_data_index[3] = { 1, 0, 2 };
const int8_t  _accel_data_sign[3]  = { 1, 1, -1 };
const uint8_t _temp_data_index = 3;

class MPU6000{
  protected:
    static volatile uint8_t _new_data;
    static volatile uint16_t _count;
    static volatile int32_t _sum[7];
    void SPIwrite(byte reg, byte data);
    uint8_t SPIread(byte reg);
    static int16_t spi_transfer_16(void);  
  public:
   Vectorf _gyro,_accel;
   void configureMPU6000();
   bool updateData();
   void initTimer();
   void readData();  
   static void dataReady(void);  
};


#endif
