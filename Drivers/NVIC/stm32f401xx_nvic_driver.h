#ifndef _STM32F401XX_NVIC_DRIVER_H_
#define _STM32F401XX_NVIC_DRIVER_H_

#include <stdint.h>

#define NVIC_ISER0                          ((volatile uint32_t*)0xE000E100U)
#define NVIC_ISER1                          ((volatile uint32_t*)0xE000E104U)
#define NVIC_ISER2                          ((volatile uint32_t*)0xE000E108U)
#define NVIC_ISER3                          ((volatile uint32_t*)0xE000E10CU)

#define NVIC_ICER0                          ((volatile uint32_t*)0xE000E180U)
#define NVIC_ICER1                          ((volatile uint32_t*)0xE000E184U)
#define NVIC_ICER2                          ((volatile uint32_t*)0xE000E188U)
#define NVIC_ICER3                          ((volatile uint32_t*)0xE000E18CU)

#define NVIC_PR_BASEADDR                    0xE000E400U
#define NVIC_PR                             ((volatile uint32_t*)NVIC_PR_BASEADDR)

#define NO_PR_BITS_IMPLEMENTED              4

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
  fn: @NVIC_SetIrqPrio
  
  param1 uint8_t: the IRQ number for which you have to set the priority
  param2 uint8_t: the IRQ priority
  
  return:
  
  desc: sets the IRQ priority of the signal
  
  note: 
  
\**************************************/
void NVIC_SetIrqPrio(uint8_t IrqNumber, uint8_t IrqPriority);

/*************************************\
  fn: @NVIC_SetIrqEnabled
  
  param1 uint8_t: the interrupt line
  param2 uint8_t: enable or disable
  
  return:
  
  desc: enables or disables a specific interrupt line in the NVIC
  
  note: 
  
\**************************************/
void NVIC_SetIrqEnabled(uint8_t IrqNumber, uint8_t isEnabled);

#endif