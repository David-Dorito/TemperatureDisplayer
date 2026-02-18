#include <stdint.h>
#include <stddef.h>
#include "../Drivers/Inc/stm32f401xx.h"
#include "../Drivers/Inc/stm32f401xx_gpio_driver.h"
#include "../Drivers/Inc/stm32f401xx_spi_driver.h"
#include "../Drivers/Inc/pcd8544_driver.h"
#include "../Drivers/Inc/stm32f401xx_clocks.h"
#include "../Libs/Gfxlib/GfxLib.h"

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
    
    const uint8_t bitmap_A[] = {0x7A, 0x18, 0x7F, 0x86, 0x10};
    const uint8_t bitmap_B[] = {0xFA, 0x1F, 0xA1, 0x87, 0xE0};
    const uint8_t bitmap_C[] = {0x7A, 0x18, 0x20, 0x85, 0xE0};
    const uint8_t bitmap_D[] = {0xF2, 0x28, 0x61, 0x8B, 0xC0};
    const uint8_t bitmap_E[] = {0xFE, 0x0F, 0x20, 0x83, 0xF0};
    const uint8_t bitmap_F[] = {0xFE, 0x0F, 0x20, 0x82, 0x00};
    const uint8_t bitmap_G[] = {0x7A, 0x18, 0x27, 0x85, 0xE0};
    const uint8_t bitmap_H[] = {0x86, 0x1F, 0xE1, 0x86, 0x10};
    const uint8_t bitmap_I[] = {0xFC, 0xC3, 0x0C, 0x33, 0xF0};
    const uint8_t bitmap_J[] = {0x1C, 0x20, 0x82, 0x89, 0xC0};
    const uint8_t bitmap_K[] = {0x8E, 0x6E, 0x26, 0x8E, 0x10};
    const uint8_t bitmap_L[] = {0x82, 0x08, 0x20, 0x83, 0xF0};
    const uint8_t bitmap_M[] = {0x87, 0x3B, 0x61, 0x86, 0x10};
    const uint8_t bitmap_N[] = {0x87, 0x1A, 0x65, 0x8E, 0x10};
    const uint8_t bitmap_O[] = {0x7A, 0x18, 0x61, 0x85, 0xE0};
    const uint8_t bitmap_P[] = {0xFA, 0x18, 0x7E, 0x82, 0x00};
    const uint8_t bitmap_Q[] = {0x7A, 0x18, 0x61, 0x89, 0xD0};
    const uint8_t bitmap_R[] = {0xFA, 0x18, 0x7E, 0x8E, 0x10};
    const uint8_t bitmap_S[] = {0x7A, 0x18, 0x1E, 0x07, 0xE0};
    const uint8_t bitmap_T[] = {0xFC, 0x82, 0x08, 0x20, 0x80};
    const uint8_t bitmap_U[] = {0x86, 0x18, 0x61, 0x85, 0xE0};
    const uint8_t bitmap_V[] = {0x86, 0x18, 0x52, 0x48, 0xC0};
    const uint8_t bitmap_W[] = {0x86, 0x18, 0x6D, 0xCE, 0x10};
    const uint8_t bitmap_X[] = {0x85, 0x23, 0x0C, 0x4A, 0x10};
    const uint8_t bitmap_Y[] = {0x86, 0x14, 0x8C, 0x30, 0xC0};
    const uint8_t bitmap_Z[] = {0xFC, 0x63, 0x18, 0xC3, 0xF0};

    const uint8_t* basicFontBitMaps[] = {
        bitmap_A,
        bitmap_B,
        bitmap_C,
        bitmap_D,
        bitmap_E,
        bitmap_F,
        bitmap_G,
        bitmap_H,
        bitmap_I,
        bitmap_J,
        bitmap_K,
        bitmap_L,
        bitmap_M,
        bitmap_N,
        bitmap_O,
        bitmap_P,
        bitmap_Q,
        bitmap_R,
        bitmap_S,
        bitmap_T,
        bitmap_U,
        bitmap_V,
        bitmap_W,
        bitmap_X,
        bitmap_Y,
        bitmap_Z
    };

    GfxLib_Font basicFont = (GfxLib_Font){
        .ppCharBitmaps = basicFontBitMaps,
        .CharCount = sizeof(basicFontBitMaps) / sizeof(basicFontBitMaps[0]),
        .CharHeight = 6,
        .CharWidth = 6,
        .StartChar = 'A'
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