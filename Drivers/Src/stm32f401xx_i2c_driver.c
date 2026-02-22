#include "../Inc/stm32f401xx_i2c_driver.h"
#include "../Inc/stm32f401xx_clocks.h"

#define I2C_SCLFREQ_STD     100U*THOUSAND
#define I2C_SCLFREQ_FAST    400U*THOUSAND

#define I2C_TRISE_MAX_STD   1000U
#define I2C_TRISE_MAX_FAST  300U

static u32 GetApb1ClkFreq();

void I2C_PeriphClkCtrl(I2C_Handle* pI2cHandle, u8 isEnabled)
{
    if (isEnabled)
    {
        if (pI2cHandle->pI2Cx == I2C1) I2C1_PCLK_EN();
        else if (pI2cHandle->pI2Cx == I2C2) I2C2_PCLK_EN();
        else if (pI2cHandle->pI2Cx == I2C3) I2C3_PCLK_EN();
    }
    else
    {
        if (pI2cHandle->pI2Cx == I2C1) I2C1_PCLK_DI();
        else if (pI2cHandle->pI2Cx == I2C2) I2C2_PCLK_DI();
        else if (pI2cHandle->pI2Cx == I2C3) I2C3_PCLK_DI();
    }
}

void I2C_PeriphCtrl(I2C_Handle* pI2cHandle, u8 isEnabled)
{
    if (isEnabled)
        pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_PE);
    else
        pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_PE);
}

void I2C_Init(I2C_Handle* pI2cHandle)
{
    I2C_PeriphClkCtrl(pI2cHandle, ENABLE);
    I2C_PeriphCtrl(pI2cHandle, DISABLE);
    
    pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_SWRST);
    pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_SWRST);
    
    pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_NOSTRETCH);
    pI2cHandle->pI2Cx->CR1 |= (pI2cHandle->Config.SclStretching << I2C_CR1_NOSTRETCH);
    
    u32 Apb1ClkFreq = GetApb1ClkFreq();
    pI2cHandle->pI2Cx->CR2 &= ~(0b111111 << I2C_CR2_FREQ);
    pI2cHandle->pI2Cx->CR2 |= (Apb1ClkFreq / MILLION << I2C_CR2_FREQ);
    
    if (pI2cHandle->Config.OwnAddrMode == I2C_OWNADDRMODE_7BIT)
    {
        pI2cHandle->pI2Cx->OAR1 &= ~(0b1111111 << I2C_OAR1_ADD71);
        pI2cHandle->pI2Cx->OAR1 |= (pI2cHandle->Config.OwnAddr << I2C_OAR1_ADD71);
    }
    else
    {
        pI2cHandle->pI2Cx->OAR1 &= ~(0b1111111111 << I2C_OAR1_ADD0);
        pI2cHandle->pI2Cx->OAR1 |= (pI2cHandle->Config.OwnAddr << I2C_OAR1_ADD0);
    }

    u32 ccrValue;
    if (pI2cHandle->Config.SclSpeed == I2C_SCLSPEED_STD)
    {
        pI2cHandle->pI2Cx->CCR &= ~(1 << I2C_CCR_FS);       
        
        ccrValue = Apb1ClkFreq / (2 * I2C_SCLFREQ_STD);

        pI2cHandle->pI2Cx->CCR &= ~(0xFFF);

        pI2cHandle->pI2Cx->CCR |= (ccrValue & 0xFFF);
    }
    else
    {
        pI2cHandle->pI2Cx->CCR |= (1 << I2C_CCR_FS);

        if (pI2cHandle->Config.FMDutyCycle == I2C_FMDUTYCYCLE_2BY1)
        {
            pI2cHandle->pI2Cx->CCR &= ~(1 << I2C_CCR_DUTY);

            ccrValue = Apb1ClkFreq / (3 * I2C_SCLFREQ_FAST);
        }
        else
        {
            pI2cHandle->pI2Cx->CCR |= (1 << I2C_CCR_DUTY);

            ccrValue = Apb1ClkFreq / (25 * I2C_SCLFREQ_FAST);
        }

        pI2cHandle->pI2Cx->CCR &= ~(0xFFF);

        pI2cHandle->pI2Cx->CCR |= (ccrValue & 0xFFF);
    }
    
    u32 trise;
    if (pI2cHandle->Config.SclSpeed == I2C_SCLSPEED_STD)
        trise = ((Apb1ClkFreq * I2C_TRISE_MAX_STD) / 1000000000U) + 1U;
    else
        trise = ((Apb1ClkFreq * I2C_TRISE_MAX_FAST) / 1000000000U) + 1U;
    pI2cHandle->pI2Cx->TRISE = trise;
    
    // TODO: add i2c interrupt support
    
    I2C_PeriphCtrl(pI2cHandle, ENABLE);
    
    pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_ACK);
    pI2cHandle->pI2Cx->CR1 |= (pI2cHandle->Config.DefaultAckCtrl << I2C_CR1_ACK);
}

void I2C_Deinit(I2C_Handle* pI2cHandle)
{
    if (pI2cHandle->pI2Cx == I2C1) I2C1_REG_RESET();
    else if (pI2cHandle->pI2Cx == I2C2) I2C2_REG_RESET();
    else if (pI2cHandle->pI2Cx == I2C3) I2C3_REG_RESET();
}

void I2C_MasterTransmitData(I2C_Handle* pI2cHandle, u16 slaveAddr, u8 AddrMode, u8* pTxBuffer, u16 len)
{
    while (pI2cHandle->pI2Cx->SR2 & I2C_SR2_BUSY);
    u32 tempread;
    pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_START);
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_SB)));
    if (AddrMode == I2C_OWNADDRMODE_7BIT)
    {
        pI2cHandle->pI2Cx->DR = (u8)slaveAddr << 1;
        while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_ADDR)));
        tempread = pI2cHandle->pI2Cx->SR1;
        tempread = pI2cHandle->pI2Cx->SR2;
        (void)tempread;
        while (len > 0)
        {
            while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_TXE)));
            pI2cHandle->pI2Cx->DR = *pTxBuffer;
            pTxBuffer++;
            len--;
        }
    }
    else
    {
        // TODO: add 10-bit address mode support
    }
    
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_BTF)));
    pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_STOP);
    
    while (pI2cHandle->pI2Cx->SR2 & I2C_SR2_BUSY);
}

void I2C_MasterReceiveData(I2C_Handle* pI2cHandle, u16 slaveAddr, u8 AddrMode, u8* pRxBuffer, u16 len)
{
    while (pI2cHandle->pI2Cx->SR2 & I2C_SR2_BUSY);
    u32 tempread;
    pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_START);
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_SB)));
    if (AddrMode == I2C_ADDRMODE_7BIT)
    {
        pI2cHandle->pI2Cx->DR = (((u8)slaveAddr << 1) | 1);
        while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_ADDR)));
        if (len == 1)
        {
            pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_ACK);
            
            tempread = pI2cHandle->pI2Cx->SR1;
            tempread = pI2cHandle->pI2Cx->SR2;
            (void)tempread;
            
            pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_STOP);
            
            *pRxBuffer = (u8)pI2cHandle->pI2Cx->DR;
        }
        else if (len == 2)
        {
            pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_ACK);
            pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_POS);
            
            tempread = pI2cHandle->pI2Cx->SR1;
            tempread = pI2cHandle->pI2Cx->SR2;
            (void)tempread;
            
            while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_BTF)));
            pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_STOP);
            
            pRxBuffer[0] = (u8)pI2cHandle->pI2Cx->DR;
            pRxBuffer[1] = (u8)pI2cHandle->pI2Cx->DR;
        }
        else
        {
            pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_ACK);

            tempread = pI2cHandle->pI2Cx->SR1;
            tempread = pI2cHandle->pI2Cx->SR2;
            (void)tempread;
            
            while (len > 3)
            {
                while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_RXNE)));
                *pRxBuffer = (u8)pI2cHandle->pI2Cx->DR;
                pRxBuffer++;
                len--;
            }
            while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_BTF)));
            pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_ACK);
            *pRxBuffer++ = (u8)pI2cHandle->pI2Cx->DR;
            while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_BTF)));
            pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_STOP);
            pRxBuffer[0] = (u8)pI2cHandle->pI2Cx->DR;
            pRxBuffer[1] = (u8)pI2cHandle->pI2Cx->DR;
        }
    }
    else
    {
        // TODO: add 10-bit address mode support
    }
    
    while (pI2cHandle->pI2Cx->SR2 & I2C_SR2_BUSY);
    pI2cHandle->pI2Cx->CR1 |= (pI2cHandle->Config.DefaultAckCtrl << I2C_CR1_ACK);
}

/******************************** Helper functions ********************************/

static u32 GetApb1ClkFreq()
{
    const u16 AhbPrescalars[] = {1, 2, 4, 8, 16, 64, 128, 256, 512};
    const u8 Apb1Prescalars[] = {1, 2, 4, 8, 16};
    
    u16 AhbPrescalar;
    u8 ClkPrescalarConfig = (RCC->CFGR & (0b1111U << RCC_CFGR_HPRE) >> RCC_CFGR_HPRE);
    if (ClkPrescalarConfig < 0b1000)
        AhbPrescalar = AhbPrescalars[0];
    else
        AhbPrescalar = AhbPrescalars[(ClkPrescalarConfig % 0b1000) + 1];

    u8 Apb1Prescalar;
    ClkPrescalarConfig = ((RCC->CFGR & (0b111U << RCC_CFGR_PPRE1)) >> RCC_CFGR_PPRE1);
    if (ClkPrescalarConfig < 0b100)
        Apb1Prescalar = Apb1Prescalars[0];
    else
        Apb1Prescalar = Apb1Prescalars[(ClkPrescalarConfig % 0b100) + 1];
    
    u8 SysClk = RCC->CFGR & (0b11U << RCC_CFGR_SWS);
    if (SysClk == RCC_SYSCLK_HSI)
    {
        return (HSI_FREQ / AhbPrescalar) / Apb1Prescalar;
    }
    else if (SysClk == RCC_SYSCLK_HSE)
    {
        return (HSE_FREQ / AhbPrescalar) / Apb1Prescalar;
    }
    else if (SysClk == RCC_SYSCLK_PLL)
    {
        // TODO: Add PLL support for GetApb1ClkFreq
        return 0;
    }
    else
    {
        // TODO: Add error return for GetApb1ClkFreq
        return 0;
    }
}

/**********************************************************************************/