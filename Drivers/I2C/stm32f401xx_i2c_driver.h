#ifndef _STM32F401XX_I2C_DRIVER_H_
#define _STM32F401XX_I2C_DRIVER_H_

#include <stdint.h>
#include "stm32f401xx.h"

//SclSpeed
#define I2C_SCLSPEED_STD                0
#define I2C_SCLSPEED_FAST               1

//SclStretching
#define I2C_SCLSTRETCHING_EN            0
#define I2C_SCLSTRETCHING_DI            1

//FMDutyCycle
#define I2C_FMDUTYCYCLE_2BY1            0
#define I2C_FMDUTYCYCLE_16BY9           1

//OwnAddrMode
#define I2C_OWNADDRMODE_7BIT            0
#define I2C_OWNADDRMODE_10BIT           1

#define I2C_ADDRMODE_7BIT               I2C_OWNADDRMODE_7BIT
#define I2C_ADDRMODE_10BIT              I2C_OWNADDRMODE_10BIT

//DefaultAckCtrl
#define I2C_DEFAULTACKCTRL_DI           0
#define I2C_DEFAULTACKCTRL_EN           1

#define I2C1_PCLK_EN()                  (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()                  (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()                  (RCC->APB1ENR |= (1 << 23))

#define I2C1_PCLK_DI()                  (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()                  (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()                  (RCC->APB1ENR &= ~(1 << 23))

#define I2C1_REG_RESET()                do {RCC->APB1RSTR |= (1 << 21); RCC->APB1RSTR &= ~(1 << 21);} while(0)
#define I2C2_REG_RESET()                do {RCC->APB1RSTR |= (1 << 22); RCC->APB1RSTR &= ~(1 << 22);} while(0)
#define I2C3_REG_RESET()                do {RCC->APB1RSTR |= (1 << 23); RCC->APB1RSTR &= ~(1 << 23);} while(0)

typedef struct {
    uint16_t OwnAddr;
    uint8_t OwnAddrMode;
    uint8_t SclSpeed;
    uint8_t SclStretching;
    uint8_t FMDutyCycle;
    uint8_t DefaultAckCtrl;
} I2C_Config;

typedef struct {
    I2C_Config Config;
    I2C_RegDef* pI2Cx;
} I2C_Handle;

/*************************************\
  fn: @I2C_PeriphClkCtrl
  
  param1 I2C_Handle*: the handle struct for the i2c peripheral
  param2 uint8_t: enable or disable the clock which the i2c peripheral is on
  
  return:
  
  desc: enables or disables the clock which the i2c peripheral is on
  
  note: 
  
\**************************************/
void I2C_PeriphClkCtrl(I2C_Handle* pI2cHandle, uint8_t isEnabled);

/*************************************\
  fn: @I2C_PeriphCtrl
  
  param1 I2C_Handle*: the handle struct for the i2c peripheral
  param2 uint8_t: enable or disable the i2c peripheral
  
  return:
  
  desc: enables or disables the i2c peripheral
  
  note: 
  
\**************************************/
void I2C_PeriphCtrl(I2C_Handle* pI2cHandle, uint8_t isEnabled);

/*************************************\
  fn: @I2C_Init
  
  param1 I2C_Handle*: the handle struct for the i2c peripheral
  
  return:
  
  desc: initializes the I2C peripheral
  
  note: doesnt currently support interrupts
  
\**************************************/
void I2C_Init(I2C_Handle* pI2cHandle);

/*************************************\
  fn: @I2C_Deinit
  
  param1 I2C_Handle*: the handle struct for the i2c peripheral
  
  return:
  
  desc: deinitializes the I2C peripheral, that means resets the registers and such
  
  note: 
  
\**************************************/
void I2C_Deinit(I2C_Handle* pI2cHandle);

/*************************************\
  fn: @I2C_MasterTransmitData
  
  param1 I2C_Handle*: the handle struct for the i2c peripheral
  param2 uint16_t: the slave address
  param3 uint8_t: the address mode of the slave address
  param4 uint8_t*: the pointer to the buffer of data to write to
  param5 uint16_t: the length of the data to transmit
  
  return:
  
  desc: transmits data from the given TxBuffer to the specified slave address
  
  note: this function is blocking, and does not contain bounds checking
  
\**************************************/
void I2C_MasterTransmitData(I2C_Handle* pI2cHandle, uint16_t slaveAddr, uint8_t AddrMode, uint8_t* pTxBuffer, uint16_t len);

/*************************************\
  fn: @I2C_MasterReceiveData
  
  param1 I2C_Handle*: the handle struct for the i2c peripheral
  param2 uint16_t: the slave address
  param3 uint8_t: the address mode of the slave address
  param4 uint8_t*: the pointer to the buffer to write received data to
  param5 uint16_t: the amount of bytes to receive
  
  return:
  
  desc: writes received data into the given RxBuffer, overflow can occur if len arg > actual buffer length
  
  note: this function is blocking, and does not contain bounds checking
  
\**************************************/
void I2C_MasterReceiveData(I2C_Handle* pI2cHandle, uint16_t slaveAddr, uint8_t AddrMode, uint8_t* pRxBuffer, uint16_t len);

#endif