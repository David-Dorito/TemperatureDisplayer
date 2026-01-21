#include "../Inc/stm32f401xx_gpio_driver.h"

void GPIO_PeriphClkCtrl(GPIO_Handle* pGpioHandle, u8 ENorDI)
{
    if (ENorDI)
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

void GPIO_Init(GPIO_Handle* pGpioHandle)
{
    GPIO_PeriphClkCtrl(pGpioHandle, ENABLE);

    //Pinmode config
    pGpioHandle->pGPIOx->MODER &= ~(0b11 << (pGpioHandle->Config.PinNumber * 2));
    pGpioHandle->pGPIOx->MODER |= (pGpioHandle->Config.PinMode << (pGpioHandle->Config.PinNumber * 2));

    //Output type config
    pGpioHandle->pGPIOx->OTYPER &= ~(1 << pGpioHandle->Config.PinNumber);
    pGpioHandle->pGPIOx->OTYPER |= (pGpioHandle->Config.OpType << pGpioHandle->Config.PinNumber);

    //Slew rate config
    pGpioHandle->pGPIOx->OSPEEDR &= ~(0b11 << (pGpioHandle->Config.PinNumber * 2));
    pGpioHandle->pGPIOx->OSPEEDR |= (pGpioHandle->Config.OpSpeed << (pGpioHandle->Config.PinNumber * 2));

    //Pull-up Pull-down config
    pGpioHandle->pGPIOx->PUPDR &= ~(0b11 << (pGpioHandle->Config.PinNumber * 2));
    pGpioHandle->pGPIOx->PUPDR |= (pGpioHandle->Config.PupdCtrl << (pGpioHandle->Config.PinNumber * 2));

    //Alt fun config
    if (pGpioHandle->Config.PinNumber < 8) //AltFun low or high register?
    {
        pGpioHandle->pGPIOx->AFRL &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 0) * 4));
        pGpioHandle->pGPIOx->AFRL |= (pGpioHandle->Config.AltFunNumber << ((pGpioHandle->Config.PinNumber - 0) * 4));
    }
    else
    {
        pGpioHandle->pGPIOx->AFRH &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 8) * 4));
        pGpioHandle->pGPIOx->AFRH |= (pGpioHandle->Config.AltFunNumber << ((pGpioHandle->Config.PinNumber - 8) * 4));
    }
    
    //Interrupt config
    if (pGpioHandle->Config.RtFtDetect)
    {
        if (pGpioHandle->Config.PinNumber < 4)
        {
            SYSCFG->EXTICR1 &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 0) * 4));
        }
        else if (pGpioHandle->Config.PinNumber < 8)
        {
            SYSCFG->EXTICR2 &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 4) * 4));
        }
        else if (pGpioHandle->Config.PinNumber < 12)
        {
            SYSCFG->EXTICR3 &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 8) * 4));
        }
        else
        {
            SYSCFG->EXTICR4 &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 12) * 4));
        }

        if (pGpioHandle->Config.RtFtDetect == GPIO_RTFTDETECT_RT)
        {
            EXTI->IMR |= (1 << pGpioHandle->Config.PinNumber);
        }
    }
}

void GPIO_Deinit(GPIO_Handle* pGpioHandle)
{
    pGpioHandle->pGPIOx->ODR &= ~(1 << pGpioHandle->Config.PinNumber);
    
    pGpioHandle->pGPIOx->PUPDR &= ~(0b11 << (pGpioHandle->Config.PinNumber * 2));
    
    pGpioHandle->pGPIOx->OSPEEDR &= ~(0b11 << (pGpioHandle->Config.PinNumber * 2));

    pGpioHandle->pGPIOx->OTYPER &= ~(1 << pGpioHandle->Config.PinNumber);

    pGpioHandle->pGPIOx->MODER &= ~(0b11 << (pGpioHandle->Config.PinNumber * 2));
    
    if (pGpioHandle->Config.PinNumber < 8) //AltFun low or high register?
        pGpioHandle->pGPIOx->AFRL &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 0) * 4));
    else
        pGpioHandle->pGPIOx->AFRH &= ~(0b1111 << ((pGpioHandle->Config.PinNumber - 8) * 4));
}

void GPIO_PortReset(GPIO_Handle* pGpioHandle)
{
    if (pGpioHandle->pGPIOx == GPIOA) GPIOA_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOB) GPIOB_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOC) GPIOC_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOD) GPIOD_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOE) GPIOE_REG_RESET();
    else if (pGpioHandle->pGPIOx == GPIOH) GPIOH_REG_RESET();
}

void GPIO_WritePin(GPIO_Handle* pGpioHandle, u8 ENorDI)
{

}

u8 GPIO_ReadPin(GPIO_Handle* pGpioHandle)
{

}
