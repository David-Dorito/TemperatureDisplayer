#include "../Inc/stm32f401xx.h"
#include "../Inc/stm32f401xx_clocks.h"

void UnpreciseDelay(u32 millisecondsDelay)
{
    u8 SysClk = RCC->CFGR & (0b11U << RCC_CFGR_SWS);
    u32 totalIncrements = 0;
    if (SysClk == RCC_SYSCLK_HSI)
    {
        totalIncrements = ((HSI_FREQ/1000)*millisecondsDelay)/6;
    }
    else if (SysClk == RCC_SYSCLK_HSE)
    {
        totalIncrements = ((HSE_FREQ/1000)*millisecondsDelay)/6;
    }
    else if (SysClk == RCC_SYSCLK_PLL)
    {
        // TODO: Add PLL support for Delay();
    }
    for (volatile int i = 0; i < totalIncrements; i++);
}