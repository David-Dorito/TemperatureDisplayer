#include <stdint.h>
#include <stddef.h>
#include "../Drivers/Inc/stm32f401xx.h"
#include "../Drivers/Inc/stm32f401xx_gpio_driver.h"
#include "../Drivers/Inc/stm32f401xx_spi_driver.h"
#include "../Drivers/Inc/pcd8544_driver.h"
#include "../Drivers/Inc/stm32f401xx_clocks.h"
#include "../Libs/Gfxlib/GfxLib.h"
#include "../Inc/Fonts.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*************************************\
  
  Vcc  -> LCD Vcc
  PA01 -> LCD Reset
  PA02 -> LCD Chip select
  PA03 -> LCD Data/Command select
  PA05 -> LCD Spi clock 
  PA07 -> LCD Spi MOSI
  PA09 -> LCD Backlight through a 220 to 330 Ohm resistor
  PA10 -> GND over a button
  
\*************************************/

void PCD8544_SetPixelColor_Bridge(void* pHandle, u16 posX, u16 posY, u32 color);

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
            .CPHA = SPI_CPHA_FIRSTEDGE,
            .CPOL = SPI_CPOL_LOW,
            .DeviceMode = SPI_DEVICEMODE_MASTER,
            .SclkSpeed = SPI_SCLKSPEED_DIV64,
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
            .OpSpeed = GPIO_OPSPEED_HIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };

    GPIO_Handle lcdDcPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 3,
            .PinMode = GPIO_PINMODE_OUTPUT,
            .OpSpeed = GPIO_OPSPEED_MED,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };

    GPIO_Handle lcdSckPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 5,
            .PinMode = GPIO_PINMODE_ALTFUN,
            .AltFunNumber = 5,
            .OpSpeed = GPIO_OPSPEED_HIGH,
            .OpType = GPIO_OPTYPE_PP,
            .RtFtDetect = GPIO_RTFTDETECT_NONE
        }
    };
    
    GPIO_Handle lcdMosiPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 7,
        .PinMode = GPIO_PINMODE_ALTFUN,
        .AltFunNumber = 5,
        .OpSpeed = GPIO_OPSPEED_HIGH,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};
    
    GPIO_Handle lcdBacklightPin = (GPIO_Handle){
        .pGPIOx = GPIOA,
        .Config = (GPIO_Config){
            .PinNumber = 9,
            .PinMode = GPIO_PINMODE_OUTPUT,
            .OpSpeed = GPIO_OPSPEED_LOW,
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
        .pResPin = &lcdResetPin,
        .pLedPin = &lcdBacklightPin,
        .pVccPin = NULL
    };
    
    GfxLib_Handle gfxlibHandle = (GfxLib_Handle){
        .pFont = &basicFont,
        .DrawPixelFunc = PCD8544_SetPixelColor_Bridge,
        .pDisplayHandle = &lcdHandle
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
    
    SPI_Init(&lcdSpiHandle);
    
    PCD8544_Init(&lcdHandle);
    PCD8544_SetBacklight(&lcdHandle, ENABLE);
    
    PCD8544_FillScreenColor(&lcdHandle, FALSE);
    PCD8544_UpdateScreen(&lcdHandle);

    u8 isDrawn = FALSE;
    while (TRUE)
    {
        if (isButtonPressed)
        {
            isDrawn = !isDrawn;
            GfxLib_DrawChar(&gfxlibHandle, 'A', 10, 2, isDrawn);
            GfxLib_DrawString(&gfxlibHandle, "AAAAAA", 10, 10, isDrawn);
            GfxLib_DrawChar(&gfxlibHandle, 'E', 10, 18, isDrawn);
            GfxLib_DrawString(&gfxlibHandle, "ABCDEFGHIJKLM", 0, 26, isDrawn);
            GfxLib_DrawString(&gfxlibHandle, "NOPQRSTUVWXYZ", 0, 34, isDrawn);
            PCD8544_UpdateScreen(&lcdHandle);
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

void PCD8544_SetPixelColor_Bridge(void* pHandle, u16 posX, u16 posY, u32 color)
{
    PCD8544_SetPixelColor((PCD8544_Handle*)pHandle, color? TRUE : FALSE, posX, posY);
}