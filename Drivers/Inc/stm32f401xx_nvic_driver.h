#ifndef _STM32F401XX_NVIC_DRIVER_H_
#define _STM32F401XX_NVIC_DRIVER_H_

#include <stdint.h>

#define IRQ_NO_EXTI0                        6
#define IRQ_NO_EXTI1                        7
#define IRQ_NO_EXTI2                        8
#define IRQ_NO_EXTI3                        9
#define IRQ_NO_EXTI4                        10
#define IRQ_NO_EXTI9_5                      23
#define IRQ_NO_EXTI15_10                    40
#define IRQ_NO_SPI1                         35
#define IRQ_NO_SPI2                         36
#define IRQ_NO_SPI3                         51
#define IRQ_NO_SPI4                         84

/*************************************\
  fn: @IRQ_PrioCtrl
  
  param1 uint8_t: the IRQ number for which you have to set the priority
  param2 uint8_t: the IRQ priority
  
  return:
  
  desc: sets the IRQ priority of the signal
  
  note: 
  
\**************************************/
void IRQ_PrioCtrl(uint8_t IrqNumber, uint8_t IrqPriority);

/*************************************\
  fn: @IRQ_ItCtrl
  
  param1 uint8_t: the interrupt line
  param2 uint8_t: enable or disable
  
  return:
  
  desc: enables or disables a specific interrupt line in the NVIC
  
  note: 
  
\**************************************/
void IRQ_ItCtrl(uint8_t IrqNumber, uint8_t isEnabled);

#endif