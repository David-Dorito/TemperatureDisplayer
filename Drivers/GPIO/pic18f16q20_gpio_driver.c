#include <pic18f16q20.h>
#include "pic18f16q20_gpio_driver.h"

/*************************************\
  fn: @GPIO_Init
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin
  
  note: 
  
\**************************************/
void GPIO_Init(GPIO_Handle* pGpioHandle)
{

}

/*************************************\
  fn: @GPIO_Deinit
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin with the reset settings
  
  note: calling this func only resets the parts of the gpio registers responsible
        for this pin, doesnt affect any other gpio pins
  
\**************************************/
void GPIO_Deinit(GPIO_Handle* pGpioHandle)
{

}

/*************************************\
  fn: @GPIO_PortReset
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: resets the whole gpio port, every gpio pin on the peripheral will be
        reset using the RCC AHB1RSTR
  
  note: unlike GPIO_Deinit() this affects every pin on the port
  
\**************************************/
void GPIO_DeinitPort(GPIO_Handle* pGpioHandle)
{

}

/*************************************\
  fn: @GPIO_WriteTogglePin
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: toggles the electrical pin state between high and low
  
  note: 
  
\**************************************/
void GPIO_WriteTogglePin(GPIO_Handle* pGpioHandle)
{

}

/*************************************\
  fn: @GPIO_WritePin
  
  param1 GPIO_Handle*: the gpio handle
  param2 u8: high or low on the pin
  
  return:
  
  desc: sets the electrical pin state to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePin(GPIO_Handle* pGpioHandle, u8 isEnabled)
{
    switch (pGpioHandle->Port)
    {
        case GPIO_PORTA:
            LATA &= ~(1U << pGpioHandle->Pin);
            LATA |= ((isEnabled & 1U) << pGpioHandle->Pin);
            break;
        case GPIO_PORTB:
            LATB &= ~(1U << pGpioHandle->Pin);
            LATB |= ((isEnabled & 1U) << pGpioHandle->Pin);
            break;
        case GPIO_PORTC:
            LATC &= ~(1U << pGpioHandle->Pin);
            LATC |= ((isEnabled & 1U) << pGpioHandle->Pin);
            break;
    }
}

/*************************************\
  fn: @GPIO_WritePort
  
  param1 GPIO_Handle*: the gpio handle
  param2 u16: the gpio pin output values
  
  return:
  
  desc: sets the electrical pin states of every pin on the peripheral to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePort(GPIO_Handle* pGpioHandle, u8 outputReg)
{

}

/*************************************\
  fn: @GPIO_ReadPin
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: first bit is either 1 or 0 depending on electrical pin state
  
  desc: reads the gpio electrical pin state
  
  note: 
  
\**************************************/
u8 GPIO_ReadPin(GPIO_Handle* pGpioHandle)
{
    switch (pGpioHandle->Port)
    {
        case GPIO_PORTA:
            return ((PORTA & (1U << pGpioHandle->Pin)) >> pGpioHandle->Pin);
        case GPIO_PORTB:
            return ((PORTB & (1U << pGpioHandle->Pin)) >> pGpioHandle->Pin);
        case GPIO_PORTC:
            return ((PORTC & (1U << pGpioHandle->Pin)) >> pGpioHandle->Pin);
    }
}

/*************************************\
  fn: @GPIO_ReadPort
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: returns a bitmap of the electrical states of the gpio pins
  
  desc: reads and returns the pin state of every pin on the gpio peripheral
  
  note: 
  
\**************************************/
u8 GPIO_ReadPort(GPIO_Handle* pGpioHandle)
{

}

/*************************************\
  fn: @GPIO_IRQHandled
  
  param1 u8: the first pin number the interrupt could have been called from
  param2 u8: the last pin number the interrupt could have been called from
  
  return: 
  
  desc: clears IOC flag reg status bits which could have caused the interrupt, for every status clear the
        GPIO_AppEventCallback() func gets called with the pin number as an arg
  
  note: should be called at the end of an IRQ Handler func that gets called when an interrupt occurs
  
\**************************************/
void GPIO_IRQHandled(u8 firstPinNum, u8 lastPinNum)
{

}