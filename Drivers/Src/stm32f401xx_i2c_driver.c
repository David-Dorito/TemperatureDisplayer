#include "../Inc/stm32f401xx_i2c_driver.h"

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

    // TODO: configure CR2 FREQ field
    
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
    
    // TODO: Configure CCR CCR field

    // TODO: Configure TRISE TRISE field
}

void I2C_Deinit(I2C_Handle* pI2cHandle)
{

}

void I2C_MasterSendData(I2C_Handle* pI2cHandle, u8 slaveAddress, u8* pTxBuffer, u16 len)
{

}

void I2C_MasterReceiveData(I2C_Handle* pI2cHandle, u8 slaveAddress, u8* pRxBuffer, u16 len)
{

}