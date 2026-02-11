#include "../Inc/stm32f401xx_i2c_driver.h"
#include "../Inc/stm32f401xx_clocks.h"

#define I2C_SCLFREQ_STD     100U*THOUSAND
#define I2C_SCLFREQ_FAST    400U*THOUSAND

#define I2C_TRISE_MAX_STD   (1000e-9)
#define I2C_TRISE_MAX_FAST  (300e-9)

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
    
    pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_ACK);
    pI2cHandle->pI2Cx->CR1 |= (pI2cHandle->Config.DefaultAckCtrl << I2C_CR1_ACK);
    
    pI2cHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_NOSTRETCH);
    pI2cHandle->pI2Cx->CR1 |= (pI2cHandle->Config.SclStretching << I2C_CR1_NOSTRETCH);
    
    u8 Apb1ClkFreq = GetApb1ClkFreq() / MILLION;
    pI2cHandle->pI2Cx->CR2 &= ~(0b111111 << I2C_CR2_FREQ);
    pI2cHandle->pI2Cx->CR2 |= (Apb1ClkFreq << I2C_CR2_FREQ);
    
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

    pI2cHandle->pI2Cx->CCR &= ~(1U << I2C_CCR_FS);
    pI2cHandle->pI2Cx->CCR |= (pI2cHandle->Config.SclSpeed << I2C_CCR_FS);

    pI2cHandle->pI2Cx->CCR &= ~(1U << I2C_CCR_DUTY);
    pI2cHandle->pI2Cx->CCR |= (pI2cHandle->Config.FMDutyCycle << I2C_CCR_DUTY);
    
    u8 t_scl;
    u8 t_pclk1 = 1 / Apb1ClkFreq;
    if (pI2cHandle->Config.SclSpeed == I2C_SCLSPEED_STD)
    {
        t_scl = 1 / I2C_SCLFREQ_STD;
        
        pI2cHandle->pI2Cx->CCR &= ~(0b111111111111 << I2C_CCR_CCR);
        pI2cHandle->pI2Cx->CCR |= ((t_scl / (2 * t_pclk1)) << I2C_CCR_CCR);
    }
    else if (pI2cHandle->Config.SclSpeed == I2C_SCLSPEED_FAST)
    {
        t_scl = 1 / I2C_SCLFREQ_FAST;
        if (pI2cHandle->Config.FMDutyCycle == I2C_FMDUTYCYCLE_2BY1)
        {
            pI2cHandle->pI2Cx->CCR &= ~(0b111111111111 << I2C_CCR_CCR);
            pI2cHandle->pI2Cx->CCR |= ((t_scl / (3 * t_pclk1)) << I2C_CCR_CCR);
        }
        else if (pI2cHandle->Config.FMDutyCycle == I2C_FMDUTYCYCLE_16BY9)
        {
            pI2cHandle->pI2Cx->CCR &= ~(0b111111111111 << I2C_CCR_CCR);            
            pI2cHandle->pI2Cx->CCR |= ((t_scl / (25 * t_pclk1)) << I2C_CCR_CCR);
        }
    }
    // TODO: Add checks to make sure the t_low and t_high cant be over or under the limit because of APB1 clk freq

    pI2cHandle->pI2Cx->TRISE &= ~(0b111111);
    if (pI2cHandle->Config.SclSpeed == I2C_SCLSPEED_STD)
        pI2cHandle->pI2Cx->TRISE |= (u32)((I2C_TRISE_MAX_STD / t_pclk1) + 1);
    else
        pI2cHandle->pI2Cx->TRISE |= (u32)((I2C_TRISE_MAX_FAST / t_pclk1) + 1);
    
    // TODO: add i2c interrupt support
}

void I2C_Deinit(I2C_Handle* pI2cHandle)
{
    if (pI2cHandle->pI2Cx == I2C1) I2C1_REG_RESET();
    else if (pI2cHandle->pI2Cx == I2C2) I2C2_REG_RESET();
    else if (pI2cHandle->pI2Cx == I2C3) I2C3_REG_RESET();
}

void I2C_MasterTransmitData(I2C_Handle* pI2cHandle, u16 slaveAddr, u8 AddrMode, u8* pTxBuffer, u16 len)
{
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
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_STOPF)));
}

void I2C_MasterReceiveData(I2C_Handle* pI2cHandle, u16 slaveAddr, u8 AddrMode, u8* pRxBuffer, u16 len)
{
    u32 tempread;
    pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_START);
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_SB)));
    if (AddrMode == I2C_OWNADDRMODE_7BIT)
    {
        pI2cHandle->pI2Cx->DR = (((u8)slaveAddr << 1) | 1);
        while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_ADDR)));
        tempread = pI2cHandle->pI2Cx->SR1;
        tempread = pI2cHandle->pI2Cx->SR2;
        (void)tempread;
        while (len > 0)
        {
            while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_RXNE)));
            *pRxBuffer = (u8)pI2cHandle->pI2Cx->DR;
            pRxBuffer++;
            len--;
        }
    }
    else
    {
        // TODO: add 10-bit address mode support
    }
    
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_BTF)));
    pI2cHandle->pI2Cx->CR1 |= (1U << I2C_CR1_STOP);
    while (!(pI2cHandle->pI2Cx->SR1 & (1U << I2C_SR1_STOPF)));
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