#include "../Inc/stm32f401xx_gpio_driver.h"

#define GPIO_BASEADDR_TO_CODE(PORT_ADDR)	(((uintptr_t)(PORT_ADDR)-AHB1PERIPH_BASEADDR)/0x400U)

/*************************************\
  fn: @GPIO_PeriphClkCtrl
  
  param1 GPIO_Handle*: the gpio handle
  param2 u8: enable or disable clock
  
  return:
  
  desc: configures the clock for the bus the periph is on
  
  note: 
  
\**************************************/
void GPIO_PeriphClkCtrl(GPIO_Handle* pGpioHandle, u8 isEnabled)
{
    if (isEnabled)
    {
        if (pGpioHandle->pGPIOx == GPIOA) GPIOA_PCLK_EN();
        else if (pGpioHandle->pGPIOx == GPIOB) GPIOB_PCLK_EN();
        else if (pGpioHandle->pGPIOx == GPIOC) GPIOC_PCLK_EN();
        else if (pGpioHandle->pGPIOx == GPIOD) GPIOD_PCLK_EN();
        else if (pGpioHandle->pGPIOx == GPIOE) GPIOE_PCLK_EN();
        else if (pGpioHandle->pGPIOx == GPIOH) GPIOH_PCLK_EN();
    }
    else
    {
        if (pGpioHandle->pGPIOx == GPIOA) GPIOA_PCLK_DI();
        else if (pGpioHandle->pGPIOx == GPIOB) GPIOB_PCLK_DI();
        else if (pGpioHandle->pGPIOx == GPIOC) GPIOC_PCLK_DI();
        else if (pGpioHandle->pGPIOx == GPIOD) GPIOD_PCLK_DI();
        else if (pGpioHandle->pGPIOx == GPIOE) GPIOE_PCLK_DI();
        else if (pGpioHandle->pGPIOx == GPIOH) GPIOH_PCLK_DI();
    }
}

/*************************************\
  fn: @GPIO_Init
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin
  
  note: 
  
\**************************************/
void GPIO_Init(GPIO_Handle* pGpioHandle)
{
    GPIO_PeriphClkCtrl(pGpioHandle, ENABLE);

    //Pinmode config
    pGpioHandle->pGPIOx->MODER &= ~(0b11U << (pGpioHandle->Config.PinNumber * 2));
    pGpioHandle->pGPIOx->MODER |= (pGpioHandle->Config.PinMode << (pGpioHandle->Config.PinNumber * 2));

    //Output type config
    pGpioHandle->pGPIOx->OTYPER &= ~(1U << pGpioHandle->Config.PinNumber);
    pGpioHandle->pGPIOx->OTYPER |= (pGpioHandle->Config.OpType << pGpioHandle->Config.PinNumber);

    //Slew rate config
    pGpioHandle->pGPIOx->OSPEEDR &= ~(0b11U << (pGpioHandle->Config.PinNumber * 2));
    pGpioHandle->pGPIOx->OSPEEDR |= (pGpioHandle->Config.OpSpeed << (pGpioHandle->Config.PinNumber * 2));

    //Pull-up Pull-down config
    pGpioHandle->pGPIOx->PUPDR &= ~(0b11U << (pGpioHandle->Config.PinNumber * 2));
    pGpioHandle->pGPIOx->PUPDR |= (pGpioHandle->Config.PupdCtrl << (pGpioHandle->Config.PinNumber * 2));

    //Alt fun config
    if (pGpioHandle->Config.PinNumber < 8) //AltFun low or high register?
    {
        pGpioHandle->pGPIOx->AFRL &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 0) * 4));
        pGpioHandle->pGPIOx->AFRL |= (pGpioHandle->Config.AltFunNumber << ((pGpioHandle->Config.PinNumber - 0) * 4));
    }
    else
    {
        pGpioHandle->pGPIOx->AFRH &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 8) * 4));
        pGpioHandle->pGPIOx->AFRH |= (pGpioHandle->Config.AltFunNumber << ((pGpioHandle->Config.PinNumber - 8) * 4));
    }
    
    //Interrupt config
    if (pGpioHandle->Config.RtFtDetect)
    {
        if (pGpioHandle->Config.PinNumber < 4)
        {
            SYSCFG->EXTICR1 &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 0) * 4));
            SYSCFG->EXTICR1 |= (GPIO_BASEADDR_TO_CODE(pGpioHandle->pGPIOx) << ((pGpioHandle->Config.PinNumber - 0) * 4));
        }
        else if (pGpioHandle->Config.PinNumber < 8)
        {
            SYSCFG->EXTICR2 &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 4) * 4));
            SYSCFG->EXTICR2 |= (GPIO_BASEADDR_TO_CODE(pGpioHandle->pGPIOx) << ((pGpioHandle->Config.PinNumber - 4) * 4));
        }
        else if (pGpioHandle->Config.PinNumber < 12)
        {
            SYSCFG->EXTICR3 &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 8) * 4));
            SYSCFG->EXTICR3 |= (GPIO_BASEADDR_TO_CODE(pGpioHandle->pGPIOx) << ((pGpioHandle->Config.PinNumber - 8) * 4));
        }
        else
        {
            SYSCFG->EXTICR4 &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 12) * 4));
            SYSCFG->EXTICR4 |= (GPIO_BASEADDR_TO_CODE(pGpioHandle->pGPIOx) << ((pGpioHandle->Config.PinNumber - 12) * 4));
        }
        
        EXTI->IMR |= (1 << pGpioHandle->Config.PinNumber);
        if (pGpioHandle->Config.RtFtDetect == GPIO_RTFTDETECT_RT)
        {
            EXTI->RTSR |= (1U << pGpioHandle->Config.PinNumber);
            EXTI->FTSR &= ~(1U << pGpioHandle->Config.PinNumber);
        }
        else if (pGpioHandle->Config.RtFtDetect == GPIO_RTFTDETECT_FT)
        {
            EXTI->FTSR |= (1U << pGpioHandle->Config.PinNumber);
            EXTI->RTSR &= ~(1U << pGpioHandle->Config.PinNumber);
        }
        else if (pGpioHandle->Config.RtFtDetect == GPIO_RTFTDETECT_RTFT)
        {
            EXTI->RTSR |= (1U << pGpioHandle->Config.PinNumber);
            EXTI->FTSR |= (1U << pGpioHandle->Config.PinNumber);
        }
    }
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
    pGpioHandle->pGPIOx->ODR &= ~(1U << pGpioHandle->Config.PinNumber);
    
    pGpioHandle->pGPIOx->PUPDR &= ~(0b11U << (pGpioHandle->Config.PinNumber * 2));
    
    pGpioHandle->pGPIOx->OSPEEDR &= ~(0b11U << (pGpioHandle->Config.PinNumber * 2));

    pGpioHandle->pGPIOx->OTYPER &= ~(1U << pGpioHandle->Config.PinNumber);

    pGpioHandle->pGPIOx->MODER &= ~(0b11U << (pGpioHandle->Config.PinNumber * 2));
    
    if (pGpioHandle->Config.PinNumber < 8) //AltFun low or high register?
        pGpioHandle->pGPIOx->AFRL &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 0) * 4));
    else
        pGpioHandle->pGPIOx->AFRH &= ~(0b1111U << ((pGpioHandle->Config.PinNumber - 8) * 4));
}

/*************************************\
  fn: @GPIO_PortReset
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: resets the whole gpio port, every gpio pin on the peripheral will be
        reset using the RCC AHB1RSTR
  
  note: unlike GPIO_Deinit() this affects every pin on the port
  
\**************************************/
void GPIO_PortReset(GPIO_Handle* pGpioHandle)
{
    if (pGpioHandle->pGPIOx == GPIOA) GPIOA_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOB) GPIOB_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOC) GPIOC_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOD) GPIOD_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOE) GPIOE_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOH) GPIOH_REG_RESET();
}

/*************************************\
  fn: @GPIO_TogglePin
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: toggles the electrical pin state between high and low
  
  note: 
  
\**************************************/
void GPIO_WriteTogglePin(GPIO_Handle* pGpioHandle)
{
    if (pGpioHandle->pGPIOx->ODR & (1U << pGpioHandle->Config.PinNumber))
        pGpioHandle->pGPIOx->BSRR = (1U << (pGpioHandle->Config.PinNumber + 16)); //set LOW
    else
        pGpioHandle->pGPIOx->BSRR = (1U << (pGpioHandle->Config.PinNumber + 0)); //set HIGH
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
    if (isEnabled) pGpioHandle->pGPIOx->BSRR = (1U << (pGpioHandle->Config.PinNumber + 0)); //set HIGH
    else pGpioHandle->pGPIOx->BSRR = (1U << (pGpioHandle->Config.PinNumber + 16)); //set LOW
}

/*************************************\
  fn: @GPIO_WritePort
  
  param1 GPIO_Handle*: the gpio handle
  param2 u16: the gpio pin output values
  
  return:
  
  desc: sets the electrical pin states of every pin on the peripheral to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePort(GPIO_Handle* pGpioHandle, u16 outputReg)
{
    pGpioHandle->pGPIOx->BSRR = outputReg;
    pGpioHandle->pGPIOx->BSRR = (((u32)~outputReg & 0xFFFF) << 16);
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
    return (pGpioHandle->pGPIOx->IDR & (1U << pGpioHandle->Config.PinNumber)) >> pGpioHandle->Config.PinNumber;
}

/*************************************\
  fn: @GPIO_ReadPort
  
  param1 GPIO_Handle*: the gpio handle
  
  return u16: returns a bitmap of the electrical states of the gpio pins
  
  desc: reads and returns the pin state of every pin on the gpio peripheral
  
  note: 
  
\**************************************/
u16 GPIO_ReadPort(GPIO_Handle* pGpioHandle)
{
    return (pGpioHandle->pGPIOx->IDR & 0xFFFF);
}

/*************************************\
  fn: @GPIO_IRQHandled
  
  param1 u8: the first pin number the interrupt could have been called from
  param2 u8: the last pin number the interrupt could have been called from
  
  return: 
  
  desc: clears EXTI PR status bits which could have caused the interrupt, for every status clear the
        GPIO_AppEventCallback() func gets called with the pin number as an arg
  
  note: should be called at the end of an EXTI IRQ Handler func that gets called by the CPU when
        an interrupt occurs
  
\**************************************/
void GPIO_IRQHandled(u8 firstPinNum, u8 lastPinNum)
{
    for (u8 i = firstPinNum; i <= lastPinNum; i++)
    {
        if (EXTI->PR & (1U << i))
        {
            EXTI->PR |= (1U << i);
            GPIO_AppEventCallback(i);
        }
    }
}

/*************************************\
  fn: @GPIO_AppEventCallback
  
  param1 u8: the pin number where an interrupt was called
  
  return: 
  
  desc: will be called everytime an interrupt status flag gets cleared in EXTI PR from GPIO_IRQHandled(),
        and only from GPIO_IRQHandled()
  
  note: weak implementation, please implement your own
  
\**************************************/
WEAK void GPIO_AppEventCallback(u8 pinNumber)
{

}