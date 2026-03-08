#include "../Inc/stm32f401xx.h"
#include "../Inc/stm32f401xx_clocks.h"

/*************************************\
  fn: @UnpreciseDelay
  
  param1 u32: the delay in milliseconds
  
  return:
  
  desc: does a rough delay for the amount of milliseconds specified, using a for loop
  
  note: the delay is very unprecise, dont trust this if you need high accurracy,
        but it should have a tolerance of max 75%
  
\**************************************/
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