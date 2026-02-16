#include <stdint.h>
#include <stddef.h>
#include "../Drivers/Inc/stm32f401xx.h"
#include "../Drivers/Inc/stm32f401xx_gpio_driver.h"
#include "../Drivers/Inc/stm32f401xx_spi_driver.h"
#include "../Drivers/Inc/pcd8544_driver.h"
#include "../Drivers/Inc/stm32f401xx_clocks.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


/*************************************\
  
  PA01 -> LCD Reset
  PA02 -> LCD Chip select
  PA03 -> LCD Data/Command select
  PA05 -> LCD Spi clock 
  PA07 -> LCD Spi MOSI
  PA09 -> LCD Backlight
  PA10 -> Gpio button, connect to GND over the button
  
\*************************************/

void TestBlankVsAllOn(PCD8544_Handle* pHandle);

GPIO_Handle buttonPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 10,
        .PinMode = GPIO_PINMODE_INPUT,
        .PupdCtrl = GPIO_PUPDCTRL_PULLUP,
        .RtFtDetect = GPIO_RTFTDETECT_FT
    }
};

volatile u8 isButtonPressed = FALSE;

int main(void)
{
    SPI_Handle lcdSpiHandle = (SPI_Handle){
        .pSPIx = SPI1,
        .Config = (SPI_Config){
            .BusConfig = SPI_BUSCONFIG_FULLDUPLEX,
            .BitOrder = SPI_BITORDER_MSBFIRST,
            .CPHA = SPI_CPHA_SECONDEDGE,
            .CPOL = SPI_CPOL_LOW,
            .DeviceMode = SPI_DEVICEMODE_MASTER,
            .SclkSpeed = SPI_SCLKSPEED_DIV256,
            .SSM = SPI_SSM_SOFTWARE,
            .DFF = SPI_DFF_8BIT
        }
    };
    
    GPIO_Handle lcdResetPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 1,
            .PinMode = GPIO_PINMODE_OUTPUT,
            .OpSpeed = GPIO_OPSPEED_VERYHIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };
    
    GPIO_Handle lcdSelectPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 2,
            .PinMode = GPIO_PINMODE_OUTPUT,
            .OpSpeed = GPIO_OPSPEED_VERYHIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };

    GPIO_Handle lcdDcPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 3,
            .PinMode = GPIO_PINMODE_OUTPUT,
            .OpSpeed = GPIO_OPSPEED_VERYHIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };

    GPIO_Handle lcdSckPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 5,
            .PinMode = GPIO_PINMODE_OUTPUT,  // Changed from ALTFUN
            .OpSpeed = GPIO_OPSPEED_VERYHIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };
    
    GPIO_Handle lcdMosiPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 7,
        .PinMode = GPIO_PINMODE_OUTPUT,  // Changed from ALTFUN
        .OpSpeed = GPIO_OPSPEED_VERYHIGH,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};
    
    GPIO_Handle lcdBacklightPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 9,
            .PinMode = GPIO_PINMODE_OUTPUT,
            .OpSpeed = GPIO_OPSPEED_VERYHIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };

    u8 pLcdFrameBuffer[PCD8544_SCREEN_SIZE] = {0};

    PCD8544_Handle lcdHandle = (PCD8544_Handle){
        .pFrameBuffer = pLcdFrameBuffer,
        .pSpiHandle = &lcdSpiHandle,
        .pCsPin = &lcdSelectPin,
        .pDcPin = &lcdDcPin,
        .pVccPin = NULL,
        .pResPin = &lcdResetPin,
        .pLedPin = &lcdBacklightPin,
        .pMosiPin = &lcdMosiPin,  // ADD THIS
        .pSckPin = &lcdSckPin     // ADD THIS
    };
    
    SYSCFG_PCLK_EN();
    IRQ_ItCtrl(IRQ_NO_EXTI15_10, ENABLE);
    
    GPIO_Init(&lcdResetPin);
    GPIO_Init(&lcdSelectPin);
    GPIO_Init(&lcdDcPin);
    GPIO_Init(&lcdMosiPin);
    GPIO_Init(&lcdSckPin);
    GPIO_Init(&lcdBacklightPin);
    GPIO_Init(&buttonPin);
    
    //SPI_Init(&lcdSpiHandle);
    
    /*
    PCD8544_Init(&lcdHandle);
    PCD8544_SetDisplayMode(&lcdHandle, PCD8544_DISPLAYMODE_ALLSEGON);
    PCD8544_SetBacklight(&lcdHandle, DISABLE);

    u8 isDisplayFilledBlack = FALSE;
    PCD8544_FillScreenColor(&lcdHandle, isDisplayFilledBlack);
    PCD8544_UpdateScreen(&lcdHandle);

    while (TRUE)
    {
        if (isButtonPressed)
        {
            isDisplayFilledBlack = !isDisplayFilledBlack;
            PCD8544_FillScreenColor(&lcdHandle, isDisplayFilledBlack);
            PCD8544_UpdateScreen(&lcdHandle);
            isButtonPressed = FALSE;
        }
    }
    */
    
    
    PCD8544_Init(&lcdHandle);
    PCD8544_SetBacklight(&lcdHandle, DISABLE);
    
    while (TRUE)
    {
        if (isButtonPressed)
        {
            TestBlankVsAllOn(&lcdHandle);
            isButtonPressed = FALSE;
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    GPIO_IRQHandled(10, 15);
}

void GPIO_AppEventCallback(u8 pinNumber)
{
    if (pinNumber == buttonPin.Config.PinNumber)
        isButtonPressed = TRUE;
}

void TestBlankVsAllOn(PCD8544_Handle* pHandle)
{
    PCD8544_SetBacklight(pHandle, HIGH);  // Backlight ON
    
    uint8_t cmd;
    
    GPIO_WritePin(pHandle->pCsPin, LOW);
    UnpreciseDelay(5);
    GPIO_WritePin(pHandle->pDcPin, LOW);  // Command mode
    UnpreciseDelay(5);
    
    // Configure display once
    cmd = 0x21;  // Extended
    SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
    
    cmd = 0x14;  // Bias 4
    SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
    
    cmd = 0xBF;  // VOP = 0x3F (good contrast)
    SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
    
    cmd = 0x20;  // Basic mode
    SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
    SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
    
    GPIO_WritePin(pHandle->pCsPin, HIGH);
    UnpreciseDelay(5);
    
    // Now alternate forever
    while(1)
    {
        // BLANK mode
        GPIO_WritePin(pHandle->pCsPin, LOW);
        UnpreciseDelay(5);
        GPIO_WritePin(pHandle->pDcPin, LOW);
        UnpreciseDelay(5);
        
        cmd = 0x08;  // Display blank (D=0, E=0)
        SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
        
        GPIO_WritePin(pHandle->pCsPin, HIGH);
        UnpreciseDelay(1000);  // 1 second blank
        
        // ALL SEGMENTS ON
        GPIO_WritePin(pHandle->pCsPin, LOW);
        UnpreciseDelay(5);
        GPIO_WritePin(pHandle->pDcPin, LOW);
        UnpreciseDelay(5);
        
        cmd = 0x09;  // All segments on (D=0, E=1)
        SPI_TransmitData_Software(pHandle->pMosiPin, pHandle->pSckPin, &cmd, 1);
        
        GPIO_WritePin(pHandle->pCsPin, HIGH);
        UnpreciseDelay(1000);  // 1 second all-on (should be black)
    }
}