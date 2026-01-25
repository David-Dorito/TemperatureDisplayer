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