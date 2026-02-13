#include "../Inc/pcd8544_driver.h"
#include "../Inc/stm32f401xx_clocks.h"

#define SETXADDR_0      0b10000000
#define SETYADDR_0      0b01000000

#define SETPOWERDOWN    0b000100100
#define SETPOWERUP      0b000100000

void PCD8544_TurnOn(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pResPin, LOW);
    GPIO_WritePin(pPcd8544Handle->pVccPin, HIGH);
    UnpreciseDelay(50);
    GPIO_WritePin(pPcd8544Handle->pResPin, HIGH);
}

void PCD8544_TurnOff(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    GPIO_WritePin(pPcd8544Handle->pVccPin, LOW);
}

void PCD8544_SetSleepMode(PCD8544_Handle* pPcd8544Handle, u8 isEnabled)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);
    
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    if (isEnabled)
        isEnabled = SETPOWERDOWN;
    else
        isEnabled = SETPOWERUP;

    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &isEnabled, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

void PCD8544_SetBacklight(PCD8544_Handle* pPcd8544Handle, u8 isEnabled)
{
    GPIO_WritePin(pPcd8544Handle->pLedPin, isEnabled);
}

void PCD8544_SetDisplayMode(PCD8544_Handle* pPcd8544Handle, u8 mode)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &mode, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

void PCD8544_TogglePixel(PCD8544_Handle* pPcd8544Handle, u8 posX, u8 posY)
{
    u16 regIndex = posX+(posY/8)*PCD8544_SCREEN_WIDTH;

    pPcd8544Handle->pFrameBuffer[regIndex] ^= (1U << (posY % 8));
}

void PCD8544_DrawPixel(PCD8544_Handle* pPcd8544Handle, u8 isBlack, u8 posX, u8 posY)
{
    u16 regIndex = posX+(posY/8)*PCD8544_SCREEN_WIDTH;

    if (isBlack)
        pPcd8544Handle->pFrameBuffer[regIndex] |= (1U << (posY % 8));
    else
        pPcd8544Handle->pFrameBuffer[regIndex] &= ~(1U << (posY % 8));
}

void PCD8544_FillScreen(PCD8544_Handle* pPcd8544Handle, u8 isBlack)
{
    isBlack = isBlack? 0xFF : 0x00;
    for (u16 i = 0; i < PCD8544_SCREEN_SIZE; i++)
        pPcd8544Handle->pFrameBuffer[i] = isBlack;
}

void PCD8544_UpdateScreen(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    u8 command = SETXADDR_0;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

    for (u16 i = 0; i < PCD8544_SCREEN_HEIGHT; i++)
    {
        GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
        command = SETYADDR_0 + i;
        SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

        GPIO_WritePin(pPcd8544Handle->pDcPin, HIGH);
        SPI_TransmitData(pPcd8544Handle->pSpiHandle, &pPcd8544Handle->pFrameBuffer[i*PCD8544_SCREEN_WIDTH], PCD8544_SCREEN_WIDTH);
    }
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}