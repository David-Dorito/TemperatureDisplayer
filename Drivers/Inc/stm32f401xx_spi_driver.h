#ifndef STM32F401XX_SPI_DRIVER_H_
#define STM32F401XX_SPI_DRIVER_H_

#include "stm32f401xx.h"

/******************************** BIT DEFINITION MACROS ********************************/

#define SPI_CR1_BIDIMODE        15
#define SPI_CR1_BIDIOE          14
#define SPI_CR1_CRCEN           13
#define SPI_CR1_CRCNEXT         12
#define SPI_CR1_DFF             11
#define SPI_CR1_RXONLY          10
#define SPI_CR1_SSM             9
#define SPI_CR1_SSI             8
#define SPI_CR1_LSBFIRST        7
#define SPI_CR1_SPE             6
#define SPI_CR1_BR              3
#define SPI_CR1_MSTR            2
#define SPI_CR1_CPOL            1
#define SPI_CR1_CPHA            0

#define SPI_CR2_TXEIE           7
#define SPI_CR2_RXNEIE          6
#define SPI_CR2_ERRIE           5
#define SPI_CR2_FRF             4
#define SPI_CR2_SSOE            2
#define SPI_CR2_TXDMAEN         1
#define SPI_CR2_RXDMAEN         0

#define SPI_SR_FRE              8
#define SPI_SR_BSY              7
#define SPI_SR_OVR              6
#define SPI_SR_MODF             5
#define SPI_SR_CRCERR           4
#define SPI_SR_UDR              3
#define SPI_SR_CHSIDE           2
#define SPI_SR_TXE              1
#define SPI_SR_RXNE             0

/***************************************************************************************/

//DeviceMode
#define SPI_DEVICEMODE_SLAVE    0
#define SPI_DEVICEMODE_MASTER   1

//BusConfig
#define SPI_BUSCONFIG_TWOLINE   0
#define SPI_BUSCONFIG_ONELINE   1

//SclkSpeed
#define SPI_SCLKSPEED_DIV2      0b000
#define SPI_SCLKSPEED_DIV4      0b001
#define SPI_SCLKSPEED_DIV8      0b010
#define SPI_SCLKSPEED_DIV16     0b011
#define SPI_SCLKSPEED_DIV32     0b100
#define SPI_SCLKSPEED_DIV64     0b101
#define SPI_SCLKSPEED_DIV128    0b110
#define SPI_SCLKSPEED_DIV256    0b111

//DFF
#define SPI_DFF_8BIT            0
#define SPI_DFF_16BIT           1

//CPOL
#define SPI_CPOL_LOW            0
#define SPI_CPOL_HIGH           1

//CPHA
#define SPI_CPHA_FIRSTEDGE      0
#define SPI_CPHA_SECONDEDGE     1

//SSM
#define SPI_SSM_HARDWARE        0
#define SPI_SSM_SOFTWARE        1

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
} SPI_Config;

typedef struct {
    SPI_Config Config;
    SPI_RegDef* pSPIx;
} SPI_Handle;

void SPI_PeriphCtrl(SPI_Handle* pSpiHandle, u8 isEnabled);
void SPI_PeriphClkCtrl(SPI_Handle* pSpiHandle, u8 isEnabled);

void SPI_Init(SPI_Handle* pSpiHandle);
void SPI_Deinit(SPI_Handle* pSpiHandle);

void SPI_SendData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u32 len);
void SPI_ReadData(SPI_Handle* pSpiHandle, u8* pRxBuffer, u32 len);
void SPI_SendReadData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u8* pRxBuffer, u32 lenTx, u32 lenRx);

#endif /* STM32F401XX_SPI_DRIVER_H_ */
