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