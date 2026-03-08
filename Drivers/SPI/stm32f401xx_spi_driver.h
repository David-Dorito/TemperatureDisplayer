#ifndef STM32F401XX_SPI_DRIVER_H_
#define STM32F401XX_SPI_DRIVER_H_

#define SPI_DUMMYBYTE               0x0000U

#define IgnoreSpiWarnings           0
#if SPI_DUMMYBYTE == 0x0000U && !IgnoreSpiWarnings
    #warning "SPI_DUMMYBYTE was not set, default value is 0x0000. Change it in Drivers/Inc/stm32f401xx_spi_driver.h at the top of the file or enable IgnoreSpiWarnings"
#endif

#include "stm32f401xx.h"

//DeviceMode
#define SPI_DEVICEMODE_SLAVE        0
#define SPI_DEVICEMODE_MASTER       1

//BusConfig
#define SPI_BUSCONFIG_FULLDUPLEX    0
#define SPI_BUSCONFIG_HALFDUPLEX    1

//SclkSpeed
#define SPI_SCLKSPEED_DIV2          0b000
#define SPI_SCLKSPEED_DIV4          0b001
#define SPI_SCLKSPEED_DIV8          0b010
#define SPI_SCLKSPEED_DIV16         0b011
#define SPI_SCLKSPEED_DIV32         0b100
#define SPI_SCLKSPEED_DIV64         0b101
#define SPI_SCLKSPEED_DIV128        0b110
#define SPI_SCLKSPEED_DIV256        0b111

//DFF
#define SPI_DFF_8BIT                0
#define SPI_DFF_16BIT               1

//CPOL
#define SPI_CPOL_LOW                0
#define SPI_CPOL_HIGH               1

//CPHA
#define SPI_CPHA_FIRSTEDGE          0
#define SPI_CPHA_SECONDEDGE         1

//SSM
#define SPI_SSM_HARDWARE            0
#define SPI_SSM_SOFTWARE            1

//BitOrder
#define SPI_BITORDER_MSBFIRST       0
#define SPI_BITORDER_LSBFIRST       1

#define SPI1_REG_RESET() do {RCC->APB2RSTR |= (1 << 12); RCC->APB2RSTR &= ~(1 << 12);} while(0)
#define SPI2_REG_RESET() do {RCC->APB1RSTR |= (1 << 14); RCC->APB1RSTR &= ~(1 << 14);} while(0)
#define SPI3_REG_RESET() do {RCC->APB1RSTR |= (1 << 15); RCC->APB1RSTR &= ~(1 << 15);} while(0)
#define SPI4_REG_RESET() do {RCC->APB2RSTR |= (1 << 13); RCC->APB2RSTR &= ~(1 << 13);} while(0)

typedef struct {
    u8 DeviceMode;
	u8 BusConfig;
	u8 SclkSpeed;
	u8 DFF;
	u8 CPOL;
	u8 CPHA;
	u8 SSM;
    u8 BitOrder;
} SPI_Config;

typedef struct {
    SPI_Config Config;
    SPI_RegDef* pSPIx;
} SPI_Handle;

/*************************************\
  fn: @SPI_PeriphCtrl
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8: enable or disable the spi peripheral using the SPE bit
  
  return:
  
  desc: enable or disable the spi peripheral using the SPE bit in CR1
  
  note: 
  
\**************************************/
void SPI_PeriphCtrl(SPI_Handle* pSpiHandle, u8 isEnabled);

/*************************************\
  fn: @SPI_PeriphClkCtrl
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8: enable or disable the clock which the spi peripheral is on
  
  return:
  
  desc: enables or disables the clock which the spi peripheral is on
  
  note: 
  
\**************************************/
void SPI_PeriphClkCtrl(SPI_Handle* pSpiHandle, u8 isEnabled);

/*************************************\
  fn: @SPI_Init
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  
  return:
  
  desc: configures the spi peripheral registers with the config in the SPI_Config struct of the handle
  
  note: doesnt support interrupts
  
\**************************************/
void SPI_Init(SPI_Handle* pSpiHandle);

/*************************************\
  fn: @SPI_Deinit
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  
  return:
  
  desc: resets the SPI peripheral registers using RCC
  
  note:
  
\**************************************/
void SPI_Deinit(SPI_Handle* pSpiHandle);

/*************************************\
  fn: @SPI_TransmitData
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8*: pointer to the transmit buffer
  param3 u16: length of the transmit buffer
  
  return:
  
  desc: takes data out of the caller defined pTxBuffer and sends it, received data is discarded
  
  note: the function is blocking
  
\**************************************/
void SPI_TransmitData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u16 len);

/*************************************\
  fn: @SPI_ReceiveData
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8*: pointer to the receive buffer
  param3 u16: length of the receive buffer
  
  return:
  
  desc: sends dummy bytes and saves the received data into the caller defined pRxBuffer
  
  note: the function is blocking
  
\**************************************/
void SPI_ReceiveData(SPI_Handle* pSpiHandle, u8* pRxBuffer, u16 len);

/*************************************\
  fn: @SPI_TransmitReceiveData
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8*: pointer to the transmit buffer
  param3 u8*: pointer to the receive buffer
  param4 u16: length of the transmit buffer
  param5 u16: length of the receive buffer
  
  return:
  
  desc: simultaniously transmits and receives data
  
  note: if the pRxBuffer is larger than the pTxBuffer, it will start sending dummy
        bytes after the pTxBuffer runs out. the function is blocking
  
\**************************************/
void SPI_TransmitReceiveData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u8* pRxBuffer, u16 lenTx, u16 lenRx);

#endif /* STM32F401XX_SPI_DRIVER_H_ */
