#ifndef PCD8544_DRIVER_H_
#define PCD8544_DRIVER_H_

#include "../Inc/stm32f401xx_gpio_driver.h"
#include "../Inc/stm32f401xx_spi_driver.h"

typedef struct {
    SPI_Handle* pSpiHandle;
    GPIO_Handle* pDcPin;
    GPIO_Handle* pResPin;
    GPIO_Handle* pCsPin;
    GPIO_Handle* pLedPin;
    GPIO_Handle* pVccPin;
} NOKIA5110_Handle;

void NOKIA5110_TurnOn(NOKIA5110_Handle* pNokia5110Handle);
void NOKIA5110_TurnOff(NOKIA5110_Handle* pNokia5110Handle);
void NOKIA5110_SendCommand(NOKIA5110_Handle* pNokia5110Handle, u8 command);
void NOKIA5110_WriteScreen(NOKIA5110_Handle* pNokia5110Handle, u8 data);

#endif