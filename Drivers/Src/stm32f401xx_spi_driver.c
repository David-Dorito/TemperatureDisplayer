#include "../Inc/stm32f401xx_spi_driver.h"

#ifndef SPI_DUMMYBYTE
    #define SPI_DUMMYBYTE 0x0000U
#endif

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

    pSpiHandle->pSPIx->I2SCFGR &= ~(1U << SPI_I2SCFGR_I2SMOD); //make sure the periph is in SPI mode
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

void SPI_TransmitData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u32 len)
{
    u8 spiEnabled = (pSpiHandle->pSPIx->CR1 & (1U << SPI_CR1_SPE)); //save peripheral enabled state for later
    pSpiHandle->pSPIx->CR1 |= (1U << SPI_CR1_SPE); //make sure peripheral is enabled

    if (pSpiHandle->Config.BusConfig == SPI_BUSCONFIG_FULLDUPLEX)
    {
        if (pSpiHandle->Config.DFF == SPI_DFF_8BIT)
        {
            while (len > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = *pTxBuffer;
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                (void)pSpiHandle->pSPIx->DR; //Read DR to clear RXNE
                pTxBuffer++;
                len--;
            }
        }
        else if (pSpiHandle->Config.DFF == SPI_DFF_16BIT)
        {
            while (len > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = *((u16*)pTxBuffer);
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                (void)pSpiHandle->pSPIx->DR; //Read DR to clear RXNE
                pTxBuffer+=2;
                len-=2;
            }
        }
    }
    else if (pSpiHandle->Config.BusConfig == SPI_BUSCONFIG_HALFDUPLEX)
    {
        // TODO: add half duplex support SPI Tx
    }
    
    while (pSpiHandle->pSPIx->SR & (1U << SPI_SR_BSY) || !(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
    pSpiHandle->pSPIx->CR1 &= ~(!spiEnabled << SPI_CR1_SPE); //restore SPE to its original state
}

void SPI_ReceiveData(SPI_Handle* pSpiHandle, u8* pRxBuffer, u32 len)
{
    u8 spiEnabled = (pSpiHandle->pSPIx->CR1 & (1U << SPI_CR1_SPE)); //save peripheral enabled state for later
    pSpiHandle->pSPIx->CR1 |= (1U << SPI_CR1_SPE); //make sure peripheral is enabled

    if (pSpiHandle->Config.BusConfig == SPI_BUSCONFIG_FULLDUPLEX)
    {
        if (pSpiHandle->Config.DFF == SPI_DFF_8BIT)
        {
            while (len > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = (u8)SPI_DUMMYBYTE;
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                *pRxBuffer = pSpiHandle->pSPIx->DR;
                pRxBuffer++;
                len--;
            }
        }
        else if (pSpiHandle->Config.DFF == SPI_DFF_16BIT)
        {
            while (len > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = (u16)SPI_DUMMYBYTE;
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                *((u16*)pRxBuffer) = pSpiHandle->pSPIx->DR;
                pRxBuffer+=2;
                len-=2;
            }
        }
    }
    else if (pSpiHandle->Config.BusConfig == SPI_BUSCONFIG_HALFDUPLEX)
    {
        // TODO: add half duplex support SPI Rx
    }
    
    while (pSpiHandle->pSPIx->SR & (1U << SPI_SR_BSY) || !(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
    pSpiHandle->pSPIx->CR1 &= ~(!spiEnabled << SPI_CR1_SPE); //restore SPE to its original state
}

void SPI_TransmitReceiveData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u8* pRxBuffer, u32 lenTx, u32 lenRx)
{
    u8 spiEnabled = (pSpiHandle->pSPIx->CR1 & (1U << SPI_CR1_SPE)); //save peripheral enabled state for later
    pSpiHandle->pSPIx->CR1 |= (1U << SPI_CR1_SPE); //make sure peripheral is enabled

    if (pSpiHandle->Config.BusConfig == SPI_BUSCONFIG_FULLDUPLEX)
    {
        if (pSpiHandle->Config.DFF == SPI_DFF_8BIT)
        {
            while (lenTx > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = *pTxBuffer;
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                if (lenRx > 0)
                {
                    *pRxBuffer = pSpiHandle->pSPIx->DR;
                    pRxBuffer++;
                    lenRx--;
                }
                else (void)pSpiHandle->pSPIx->DR; //Read DR to clear RXNE
                pTxBuffer++;
                lenTx--;
            }
            while (lenRx > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = (u8)SPI_DUMMYBYTE;
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                *pRxBuffer = pSpiHandle->pSPIx->DR;
                pRxBuffer++;
                lenRx--;
            }
        }
        else if (pSpiHandle->Config.DFF == SPI_DFF_16BIT)
        {
            while (lenTx > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = *((u16*)pTxBuffer);
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                if (lenRx > 0)
                {
                    *((u16*)pRxBuffer) = pSpiHandle->pSPIx->DR;
                    pRxBuffer+=2;
                    lenRx-=2;
                }
                else (void)pSpiHandle->pSPIx->DR; //Read DR to clear RXNE
                pTxBuffer+=2;
                lenTx-=2;
            }
            while (lenRx > 0)
            {
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
                pSpiHandle->pSPIx->DR = (u16)SPI_DUMMYBYTE;
                while (!(pSpiHandle->pSPIx->SR & (1U << SPI_SR_RXNE)));
                *((u16*)pRxBuffer) = pSpiHandle->pSPIx->DR;
                pRxBuffer+=2;
                lenRx-=2;
            }
        }
    }
    else if (pSpiHandle->Config.BusConfig == SPI_BUSCONFIG_HALFDUPLEX)
    {
        // TODO: add half duplex support SPI TxRx
    }
    
    while (pSpiHandle->pSPIx->SR & (1U << SPI_SR_BSY) || !(pSpiHandle->pSPIx->SR & (1U << SPI_SR_TXE)));
    pSpiHandle->pSPIx->CR1 &= ~(!spiEnabled << SPI_CR1_SPE); //restore SPE to its original state
}