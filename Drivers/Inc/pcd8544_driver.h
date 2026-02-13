#ifndef PCD8544_DRIVER_H_
#define PCD8544_DRIVER_H_

#include "../Inc/stm32f401xx_gpio_driver.h"
#include "../Inc/stm32f401xx_spi_driver.h"

#define PCD8544_SCREEN_WIDTH            84
#define PCD8544_SCREEN_HEIGHT           48
#define PCD8544_SCREEN_SIZE             PCD8544_SCREEN_WIDTH * (PCD8544_SCREEN_HEIGHT / 8)

#define PCD8544_DISPLAYMODE_BLANK       0b00001000
#define PCD8544_DISPLAYMODE_NORMAL      0b00001100
#define PCD8544_DISPLAYMODE_ALLSEGON    0b00001001
#define PCD8544_DISPLAYMODE_INVERSE     0b00001101

typedef struct {
    SPI_Handle* pSpiHandle;
    GPIO_Handle* pDcPin;
    GPIO_Handle* pResPin;
    GPIO_Handle* pCsPin;
    GPIO_Handle* pLedPin;
    GPIO_Handle* pVccPin;
    u8* pFrameBuffer;
} PCD8544_Handle;

void PCD8544_TurnOn(PCD8544_Handle* pPcd8544Handle);
void PCD8544_TurnOff(PCD8544_Handle* pPcd8544Handle);
void PCD8544_SetSleepMode(PCD8544_Handle* pPcd8544Handle, u8 isEnabled);
void PCD8544_SetBacklight(PCD8544_Handle* pPcd8544Handle, u8 isEnabled);
void PCD8544_SetDisplayMode(PCD8544_Handle* pPcd8544Handle, u8 mode);
void PCD8544_TogglePixel(PCD8544_Handle* pPcd8544Handle, u8 posX, u8 posY);
void PCD8544_DrawPixel(PCD8544_Handle* pPcd8544Handle, u8 isBlack, u8 posX, u8 posY);
void PCD8544_FillScreen(PCD8544_Handle* pPcd8544Handle, u8 isBlack);
void PCD8544_UpdateScreen(PCD8544_Handle* pPcd8544Handle);

#endif