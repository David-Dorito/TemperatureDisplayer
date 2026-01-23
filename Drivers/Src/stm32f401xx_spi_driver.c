#include "../Inc/stm32f401xx_spi_driver.h"

void SPI_PeriphCtrl(SPI_Handle* pSpiHandle, u8 ENorDI)
{
    if (ENorDI)
        pSpiHandle->pSPIx->CR1 |= (1U << SPI_CR1_SPE);
    else
        pSpiHandle->pSPIx->CR1 &= ~(1U << SPI_CR1_SPE);
}

void SPI_PeriphClkCtrl(SPI_Handle* pSpiHandle, u8 ENorDI)
{
    if (ENorDI)
    {
        if (pSpiHandle->pSPIx == SPI1) SPI1_PCLK_EN();
        else if (pSpiHandle->pSPIx == SPI2) SPI2_PCLK_EN();
        else if (pSpiHandle->pSPIx == SPI3) SPI3_PCLK_EN();
        else if (pSpiHandle->pSPIx == SPI4) SPI4_PCLK_EN();
    }
    else
    {
        if (pSpiHandle->pSPIx == SPI1) SPI1_PCLK_DI();
        else if (pSpiHandle->pSPIx == SPI2) SPI2_PCLK_DI();
        else if (pSpiHandle->pSPIx == SPI3) SPI3_PCLK_DI();
        else if (pSpiHandle->pSPIx == SPI4) SPI4_PCLK_DI();
    }
}

void SPI_Init(SPI_Handle* pSpiHandle)
{
    pSpiHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_SPE); //disabe periph to safely manipulate CR1

    u16 tempReg = 0;

    //configure tempReg to assign it to CR1 afterwards
    tempReg |= (pSpiHandle->Config.CPHA << SPI_CR1_CPHA);
    tempReg |= (pSpiHandle->Config.CPOL << SPI_CR1_CPOL);
    tempReg |= (pSpiHandle->Config.DeviceMode << SPI_CR1_MSTR);
    tempReg |= (pSpiHandle->Config.SclkSpeed << SPI_CR1_BR);
    tempReg |= (pSpiHandle->Config.BitOrder << SPI_CR1_LSBFIRST);
    tempReg |= ((pSpiHandle->Config.SSM & pSpiHandle->Config.DeviceMode) << SPI_CR1_SSI);
    tempReg |= (pSpiHandle->Config.SSM << SPI_CR1_SSM);
    tempReg |= (pSpiHandle->Config.DFF << SPI_CR1_DFF);
    tempReg |= (pSpiHandle->Config.BusConfig << SPI_CR1_BIDIMODE);

    pSpiHandle->pSPIx->CR1 = tempReg;
    
    // TODO: Add interrupt support
}

void SPI_Deinit(SPI_Handle* pSpiHandle)
{
    if (pSpiHandle->pSPIx == SPI1) SPI1_REG_RESET();
    else if (pSpiHandle->pSPIx == SPI2) SPI2_REG_RESET();
    else if (pSpiHandle->pSPIx == SPI3) SPI3_REG_RESET();
    else if (pSpiHandle->pSPIx == SPI4) SPI4_REG_RESET(); 
}

void SPI_SendData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u32 len)
{
    
}

void SPI_ReadData(SPI_Handle* pSpiHandle, u8* pRxBuffer, u32 len)
{

}

void SPI_SendReadData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u8* pRxBuffer, u32 lenTx, u32 lenRx)
{

}