#include "../Inc/nokia5110_driver.h"
#include "../Inc/stm32f401xx_clocks.h"

void NOKIA5110_TurnOn(NOKIA5110_Handle* pNokia5110Handle)
{
    GPIO_WritePin(pNokia5110Handle->pResPin, LOW);
    GPIO_WritePin(pNokia5110Handle->pVccPin, HIGH);
    UnpreciseDelay(50);
    GPIO_WritePin(pNokia5110Handle->pResPin, HIGH);
}

void NOKIA5110_TurnOff(NOKIA5110_Handle* pNokia5110Handle)
{
    GPIO_WritePin(pNokia5110Handle->pCsPin, HIGH);
    GPIO_WritePin(pNokia5110Handle->pDcPin, LOW);
    GPIO_WritePin(pNokia5110Handle->pVccPin, LOW);
}

void NOKIA5110_SendCommand(NOKIA5110_Handle* pNokia5110Handle, u8 command)
{
    
}

void NOKIA5110_WriteScreen(NOKIA5110_Handle* pNokia5110Handle, u8 data)
{

}