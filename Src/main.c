#include "../Inc/bsp.h"

/*************************************\
  
  GND  -> LCD, Sensor GND
  3V3  -> LCD, Sensor Vcc
  PA01 -> LCD Reset
  PA02 -> LCD Chip select
  PA03 -> LCD Data/Command select
  PA05 -> LCD Spi clock 
  PA07 -> LCD Spi MOSI
  PA09 -> LCD Backlight through a 220 to 330 Ohm resistor
  PA10 -> GND over a button
  PB08 -> Sensor SCL
  PB09 -> Sensor SDA
  
\*************************************/

#define WHITE               0
#define BLACK               1

void FloatToString(float value, char *buffer, int decimals);

volatile u8 isButtonPressed = FALSE;

int main(void)
{
    SYSCFG_PCLK_EN();
    IRQ_ItCtrl(IRQ_NO_EXTI15_10, ENABLE);
    
    GPIO_Init(&buttonPin);

    GPIO_Init(&lcdResetPin);
    GPIO_Init(&lcdSelectPin);
    GPIO_Init(&lcdDcPin);
    GPIO_Init(&lcdMosiPin);
    GPIO_Init(&lcdSckPin);
    GPIO_Init(&lcdBacklightPin);

    GPIO_Init(&sensorSclPin);
    GPIO_Init(&sensorSdaPin);
    
    SPI_Init(&lcdSpiHandle);
    
    I2C_Init(&sensorI2cHandle);
    
    PCD8544_Init(&lcdHandle);
    PCD8544_SetBacklight(&lcdHandle, ENABLE);
    
    MCP9808_Init(&sensorHandle);
    
    PCD8544_FillScreenColor(&lcdHandle, FALSE);
    PCD8544_UpdateScreen(&lcdHandle);

    while (TRUE)
    {
        if (isButtonPressed)
        {
            float temperature = MCP9808_GetTemperature(&sensorHandle);
            char temperatureString[16] = "";
            FloatToString(temperature, temperatureString, 4);
            
            PCD8544_FillScreenColor(&lcdHandle, WHITE);
            GfxLib_DrawString(&gfxlibHandle, "TEMPERATURE:", 2, 12, BLACK);
            GfxLib_DrawString(&gfxlibHandle, temperatureString, 18, 20, BLACK);
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

void FloatToString(float value, char* buffer, int decimals)
{
    int i = 0;

    // Handle negative numbers
    if (value < 0)
    {
        buffer[i++] = '-';
        value = -value;
    }

    // Integer part
    int whole = (int)value;
    float fraction = value - (float)whole;

    // Convert integer part
    char temp[16];
    int j = 0;

    if (whole == 0)
        temp[j++] = '0';
    else
        while (whole > 0)
        {
            temp[j++] = (whole % 10) + '0';
            whole /= 10;
        }

    // Reverse integer digits
    for (int k = j - 1; k >= 0; k--)
        buffer[i++] = temp[k];

    // Decimal point
    if (decimals > 0)
    {
        buffer[i++] = '.';

        for (int d = 0; d < decimals; d++)
        {
            fraction *= 10;
            int digit = (int)fraction;
            buffer[i++] = digit + '0';
            fraction -= digit;
        }
    }

    buffer[i] = '\0';
}