#include "../Inc/pcd8544_driver.h"

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

}