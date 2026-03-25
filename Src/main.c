#ifdef __XC8
    #include <xc.h>
#else
    #include "pic18f16q20.h"
#endif
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

void FloatToString(float value, char *buffer, u8 decimals);

volatile u8 isButtonPressed = FALSE;

int main(void)
{
    BSP_Init();
    
    while (TRUE)
    {
        if (isButtonPressed)
        {
            isButtonPressed = FALSE;
        }
    }
    
    return 0;
}

void FloatToString(float value, char* buffer, u8 decimals)
{
    u16 i = 0;

    // handle neg nums
    if (value < 0)
    {
        buffer[i++] = '-';
        value = -value;
    }

    // int part
    int whole = (int)value;
    float fraction = value - whole;

    // convert integer part (array will be reversed, for example 20 would be 02)
    char temp[16];
    u16 j = 0;

    if (whole == 0)
        temp[j++] = '0';
    else
        while (whole > 0)
        {
            temp[j++] = (char)((whole % 10) + (int)'0');
            whole /= 10;
        }

    // reverse integer digits (from the example before, turn 02 back to 20)
    for (u16 k = j - 1; k >= 0; k--)
        buffer[i++] = temp[k];

    // decimal point
    if (decimals > 0)
    {
        buffer[i++] = '.';

        for (int d = 0; d < decimals; d++)
        {
            fraction *= 10;
            int digit = (int)fraction;
            buffer[i++] = (char)(digit + (int)'0');
            fraction -= digit;
        }
    }

    buffer[i] = '\0';
}

void GPIO_AppEvCb(u8 port, u8 pin)
{
    if (pin == btnPin.Pin && port == btnPin.Port)
        isButtonPressed = TRUE;
}

/******************************** interrupt service routines ********************************/

void __interrupt(irq(default), base(8)) Default_ISR(void)
{
    return;
}

void __interrupt(irq(IRQ_IOC), base(8)) IOC_ISR(void)
{
    GPIO_IrqHandled(GPIO_AppEvCb);
}

/********************************************************************************************/