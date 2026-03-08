#ifndef USER_BOARD_CLOCKS_H_
#define USER_BOARD_CLOCKS_H_

#include <stdint.h>

#ifndef THOUSAND
    #define THOUSAND            1000U
#endif
#ifndef MILLION
    #define MILLION             1000000U
#endif

#define HSI_FREQ                16U*MILLION  // not user-configured, dont change
#define HSE_FREQ                0U*MILLION  // user-configured
#define LSE_FREQ                0U*THOUSAND // user-configured

#define IgnoreClockWarnings     0

#define RCC_CFGR_PPRE1          10
#define RCC_CFGR_HPRE           4
#define RCC_CFGR_SWS            2

#define RCC_SYSCLK_HSI          0b00
#define RCC_SYSCLK_HSE          0b01
#define RCC_SYSCLK_PLL          0b10

#if HSE_FREQ == 0U && !IgnoreClockWarnings
    #warning "HSE_FREQ value is not set inside of Drivers/Inc/stm32f401xx_clocks.h, if your using HSE please set it else turn IgnoreClockWarnings to 1"
#endif

#if LSE_FREQ == 0U && !IgnoreClockWarnings
    #warning "LSE_FREQ value is not set inside of Drivers/Inc/stm32f401xx_clocks.h, if your using LSE please set it else turn IgnoreClockWarnings to 1"
#endif

/*************************************\
  fn: @UnpreciseDelay
  
  param1 u32: the delay in milliseconds
  
  return:
  
  desc: does a rough delay for the amount of milliseconds specified, using a for loop
  
  note: the delay is very unprecise, dont trust this if you need high accurracy,
        but it should have a tolerance of max 75%
  
\**************************************/
void UnpreciseDelay(uint32_t millisecondsDelay);

#endif