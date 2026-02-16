#include "../Inc/stm32f401xx_spi_driver.h"

/*************************************\
  fn: @SPI_PeriphCtrl
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8: enable or disable the spi peripheral using the SPE bit
  
  return:
  
  desc: enable or disable the spi peripheral using the SPE bit in CR1
  
  note: 
  
\**************************************/
void SPI_PeriphCtrl(SPI_Handle* pSpiHandle, u8 isEnabled)
{
    if (isEnabled)
        pSpiHandle->pSPIx->CR1 |= (1U << SPI_CR1_SPE);
    else
        pSpiHandle->pSPIx->CR1 &= ~(1U << SPI_CR1_SPE);
}

/*************************************\
  fn: @SPI_PeriphClkCtrl
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8: enable or disable the clock which the spi peripheral is on
  
  return:
  
  desc: enables or disables the clock which the spi peripheral is on
  
  note: 
  
\**************************************/
void SPI_PeriphClkCtrl(SPI_Handle* pSpiHandle, u8 isEnabled)
{
    if (isEnabled)
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

/*************************************\
  fn: @SPI_Init
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  
  return:
  
  desc: configures the spi peripheral registers with the config in the SPI_Config struct of the handle
  
  note: doesnt support interrupts
  
\**************************************/
void SPI_Init(SPI_Handle* pSpiHandle)
{
    SPI_PeriphClkCtrl(pSpiHandle, ENABLE);
    SPI_PeriphCtrl(pSpiHandle, DISABLE); //disabe periph to safely manipulate CR1

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
    
    SPI_PeriphCtrl(pSpiHandle, ENABLE); //disabe periph to safely manipulate CR1
}

/*************************************\
  fn: @SPI_Deinit
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  
  return:
  
  desc: resets the SPI peripheral registers using RCC
  
  note:
  
\**************************************/
void SPI_Deinit(SPI_Handle* pSpiHandle)
{
    if (pSpiHandle->pSPIx == SPI1) SPI1_REG_RESET();
    else if (pSpiHandle->pSPIx == SPI2) SPI2_REG_RESET();
    else if (pSpiHandle->pSPIx == SPI3) SPI3_REG_RESET();
    else if (pSpiHandle->pSPIx == SPI4) SPI4_REG_RESET(); 
}

/*************************************\
  fn: @SPI_TransmitData
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8*: pointer to the transmit buffer
  param3 u16: length of the transmit buffer
  
  return:
  
  desc: takes data out of the caller defined pTxBuffer and sends it, received data is discarded
  
  note: the function is blocking
  
\**************************************/
void SPI_TransmitData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u16 len)
{
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
}

/*************************************\
  fn: @SPI_ReceiveData
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8*: pointer to the receive buffer
  param3 u16: length of the receive buffer
  
  return:
  
  desc: sends dummy bytes and saves the received data into the caller defined pRxBuffer
  
  note: the function is blocking
  
\**************************************/
void SPI_ReceiveData(SPI_Handle* pSpiHandle, u8* pRxBuffer, u16 len)
{
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
}

/*************************************\
  fn: @SPI_TransmitReceiveData
  
  param1 SPI_Handle*: the handle struct for the spi peripheral
  param2 u8*: pointer to the transmit buffer
  param3 u8*: pointer to the receive buffer
  param4 u16: length of the transmit buffer
  param5 u16: length of the receive buffer
  
  return:
  
  desc: simultaniously transmits and receives data
  
  note: if the pRxBuffer is larger than the pTxBuffer, it will start sending dummy
        bytes after the pTxBuffer runs out. the function is blocking
  
\**************************************/
void SPI_TransmitReceiveData(SPI_Handle* pSpiHandle, u8* pTxBuffer, u8* pRxBuffer, u16 lenTx, u16 lenRx)
{
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
}

void SPI_TransmitData_Software(GPIO_Handle* pMosi, GPIO_Handle* pSck, u8* pTxBuffer, u16 len)
{
    for(u16 byte = 0; byte < len; byte++)
    {
        u8 data = pTxBuffer[byte];
        
        // Send 8 bits, MSB first
        for(int i = 7; i >= 0; i--)
        {
            // Set data bit
            if(data & (1 << i)) {
                GPIO_WritePin(pMosi, HIGH);
            } else {
                GPIO_WritePin(pMosi, LOW);
            }
            
            // Clock pulse HIGH
            GPIO_WritePin(pSck, HIGH);
            
            // Clock pulse LOW
            GPIO_WritePin(pSck, LOW);
        }
    }
}