#ifndef STM32F401XX_GPIO_DRIVER_H_
#define STM32F401XX_GPIO_DRIVER_H_

#include <stdint.h>
#include "stm32f401xx.h"

//PinMode
#define GPIO_PINMODE_INPUT          0
#define GPIO_PINMODE_OUTPUT         1
#define GPIO_PINMODE_ALTFUN         2
#define GPIO_PINMODE_ANALOG         3

//PinOpType
#define GPIO_OPTYPE_PP              0
#define GPIO_OPTYPE_OD              1

//PinOpSpeed
#define GPIO_OPSPEED_LOW            0
#define GPIO_OPSPEED_MED            1
#define GPIO_OPSPEED_HIGH           2
#define GPIO_OPSPEED_VERYHIGH       3

//PinPupdCtrl
#define GPIO_PUPDCTRL_NOPUPD        0
#define GPIO_PUPDCTRL_PULLUP        1
#define GPIO_PUPDCTRL_PULLDOWN      2

//RtFtDetect
#define GPIO_RTFTDETECT_NONE        0b00
#define GPIO_RTFTDETECT_FT          0b01
#define GPIO_RTFTDETECT_RT          0b10
#define GPIO_RTFTDETECT_RTFT        0b11

#define GPIOA_PCLK_EN()             (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()             (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()             (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()             (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()             (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()             (RCC->AHB1ENR |= (1 << 7))

#define GPIOA_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()             (RCC->AHB1ENR &= ~(1 << 7))

#define GPIOA_REG_RESET()           do {RCC->AHB1RSTR |= (1 << 0); RCC->APB2RSTR &= ~(1 << 0);} while(0)
#define GPIOB_REG_RESET()           do {RCC->AHB1RSTR |= (1 << 1); RCC->APB2RSTR &= ~(1 << 1);} while(0)
#define GPIOC_REG_RESET()           do {RCC->AHB1RSTR |= (1 << 2); RCC->APB2RSTR &= ~(1 << 2);} while(0)
#define GPIOD_REG_RESET()           do {RCC->AHB1RSTR |= (1 << 3); RCC->APB2RSTR &= ~(1 << 3);} while(0)
#define GPIOE_REG_RESET()           do {RCC->AHB1RSTR |= (1 << 4); RCC->APB2RSTR &= ~(1 << 4);} while(0)
#define GPIOH_REG_RESET()           do {RCC->AHB1RSTR |= (1 << 7); RCC->APB2RSTR &= ~(1 << 7);} while(0)

typedef struct {
    uint8_t PinNumber;
    uint8_t PinMode;
    uint8_t OpType;
    uint8_t OpSpeed;
    uint8_t PupdCtrl;
    uint8_t AltFunNumber;
    uint8_t RtFtDetect;
} GPIO_Config;

typedef struct {
    GPIO_Config Config;
    GPIO_RegDef* pGPIOx;
} GPIO_Handle;

/*************************************\
  fn: @GPIO_PeriphClkCtrl
  
  param1 GPIO_Handle*: the gpio handle
  param2 uint8_t: enable or disable clock
  
  return:
  
  desc: configures the clock for the bus the periph is on
  
  note: 
  
\**************************************/
void GPIO_PeriphClkCtrl(GPIO_Handle* pGpioHandle, uint8_t isEnabled);

/*************************************\
  fn: @GPIO_Init
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin
  
  note: 
  
\**************************************/
void GPIO_Init(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_Deinit
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin with the reset settings
  
  note: calling this func only resets the parts of the gpio registers responsible
        for this pin, doesnt affect any other gpio pins
  
\**************************************/
void GPIO_Deinit(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_PortReset
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: resets the whole gpio port, every gpio pin on the peripheral will be
        reset using the RCC AHB1RSTR
  
  note: unlike GPIO_Deinit() this affects every pin on the port
  
\**************************************/
void GPIO_PortReset(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_TogglePin
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: toggles the electrical pin state between high and low
  
  note: 
  
\**************************************/
void GPIO_WriteTogglePin(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_WritePin
  
  param1 GPIO_Handle*: the gpio handle
  param2 uint8_t: high or low on the pin
  
  return:
  
  desc: sets the electrical pin state to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePin(GPIO_Handle* pGpioHandle, uint8_t isEnabled);

/*************************************\
  fn: @GPIO_WritePort
  
  param1 GPIO_Handle*: the gpio handle
  param2 uint16_t: the gpio pin output values
  
  return:
  
  desc: sets the electrical pin states of every pin on the peripheral to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePort(GPIO_Handle* pGpioHandle, uint16_t outputReg);

/*************************************\
  fn: @GPIO_ReadPin
  
  param1 GPIO_Handle*: the gpio handle
  
  return uint8_t: first bit is either 1 or 0 depending on electrical pin state
  
  desc: reads the gpio electrical pin state
  
  note: 
  
\**************************************/
uint8_t GPIO_ReadPin(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_ReadPort
  
  param1 GPIO_Handle*: the gpio handle
  
  return uint16_t: returns a bitmap of the electrical states of the gpio pins
  
  desc: reads and returns the pin state of every pin on the gpio peripheral
  
  note: 
  
\**************************************/
uint16_t GPIO_ReadPort(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_IRQHandled
  
  param1 uint8_t: the first pin number the interrupt could have been called from
  param2 uint8_t: the last pin number the interrupt could have been called from
  
  return: 
  
  desc: clears EXTI PR status bits which could have caused the interrupt, for every status clear the
        GPIO_AppEventCallback() func gets called with the pin number as an arg
  
  note: should be called at the end of an EXTI IRQ Handler func that gets called by the CPU when
        an interrupt occurs
  
\**************************************/
void GPIO_IRQHandled(uint8_t firstPinNum, uint8_t lastPinNum);

/*************************************\
  fn: @GPIO_AppEventCallback
  
  param1 uint8_t: the pin number where an interrupt was called
  
  return: 
  
  desc: will be called everytime an interrupt status flag gets cleared in EXTI PR from GPIO_IRQHandled(),
        and only from GPIO_IRQHandled()
  
  note: weak implementation, please implement your own
  
\**************************************/
void GPIO_AppEventCallback(uint8_t pinNumber);

#endif /* STM32F401XX_GPIO_DRIVER_H_ */