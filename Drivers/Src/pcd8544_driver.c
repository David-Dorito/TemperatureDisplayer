#include "../Inc/pcd8544_driver.h"
#include "../Inc/stm32f401xx_clocks.h"

#define SETXADDR_0      0b10000000
#define SETYADDR_0      0b01000000

#define SETPOWERDOWN    0b000100100
#define SETPOWERUP      0b000100000

/*************************************\
  fn: @PCD8544_TurnOn
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: turns the display on using the sequence described in the datasheet
  
  note:
  
\**************************************/
void PCD8544_TurnOn(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pResPin, LOW);
    GPIO_WritePin(pPcd8544Handle->pVccPin, HIGH);
    UnpreciseDelay(50);
    GPIO_WritePin(pPcd8544Handle->pResPin, HIGH);
}

/*************************************\
  fn: @PCD8544_TurnOff
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: turns the display off
  
  note: also pulls chip select to HIGH and Data/Command to LOW
  
\**************************************/
void PCD8544_TurnOff(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    GPIO_WritePin(pPcd8544Handle->pVccPin, LOW);
}

/*************************************\
  fn: @PCD8544_SetSleepMode
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: enable or disable sleep mode of the display
  
  return:
  
  desc: enables or disables the sleep mode of the display
  
  note: display will stop displaying an image if turned on but RAM will NOT get cleared,
        so once you turn off sleep mode it will start displaying the image again
  
\**************************************/
void PCD8544_SetSleepMode(PCD8544_Handle* pPcd8544Handle, u8 isEnabled)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);
    
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    if (isEnabled)
        isEnabled = SETPOWERDOWN;
    else
        isEnabled = SETPOWERUP;

    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &isEnabled, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

/*************************************\
  fn: @PCD8544_SetBacklight
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: enable or disable sleep mode of the display
  
  return:
  
  desc: enables or disables the background light of the display
  
  note: function is very basic, just a wrapper for GPIO_WritePin() with the LED pin as the arg
  
\**************************************/
void PCD8544_SetBacklight(PCD8544_Handle* pPcd8544Handle, u8 isEnabled)
{
    GPIO_WritePin(pPcd8544Handle->pLedPin, isEnabled);
}

/*************************************\
  fn: @PCD8544_SetDisplayMode
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: new mode of the display
  
  return:
  
  desc: sets the mode of the display
  
  note: use the PCD8544_DISPLAYMODE_XXX macros as the mode arg, view the datasheet for a description of what they do
  
\**************************************/
void PCD8544_SetDisplayMode(PCD8544_Handle* pPcd8544Handle, u8 mode)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &mode, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

/*************************************\
  fn: @PCD8544_TogglePixelColor
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: x position of the pixel
  param3 u8: y position of the pixel
  
  return:
  
  desc: toggles the colour of the pixel at the specified x and y position
  
  note:
  
\**************************************/
void PCD8544_TogglePixelColor(PCD8544_Handle* pPcd8544Handle, u8 posX, u8 posY)
{
    u16 regIndex = posX+(posY/8)*PCD8544_SCREEN_WIDTH;

    pPcd8544Handle->pFrameBuffer[regIndex] ^= (1U << (posY % 8));
}

/*************************************\
  fn: @PCD8544_SetPixelColor
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: the colour of the pixel
  param3 u8: x position of the pixel
  param4 u8: y position of the pixel
  
  return:
  
  desc: sets the colour of the pixel at the specified x and y position
  
  note:
  
\**************************************/
void PCD8544_SetPixelColor(PCD8544_Handle* pPcd8544Handle, u8 isBlack, u8 posX, u8 posY)
{
    u16 regIndex = posX+(posY/8)*PCD8544_SCREEN_WIDTH;

    if (isBlack)
        pPcd8544Handle->pFrameBuffer[regIndex] |= (1U << (posY % 8));
    else
        pPcd8544Handle->pFrameBuffer[regIndex] &= ~(1U << (posY % 8));
}

/*************************************\
  fn: @PCD8544_GetPixelColor
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: x position of the pixel
  param3 u8: y position of the pixel
  
  return u8: color of the pixel as a bool
  
  desc: returns the colour of the pixel at the specified x and y position
  
  note:
  
\**************************************/
u8 PCD8544_GetPixelColor(PCD8544_Handle* pPcd8544Handle, u8 posX, u8 posY)
{
    u16 regIndex = posX+(posY/8)*PCD8544_SCREEN_WIDTH;

    return ((pPcd8544Handle->pFrameBuffer[regIndex] & (1U << (posY % 8))) >> posY % 8);
}

/*************************************\
  fn: @PCD8544_FillScreenColor
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: the colour to set every pixel to
  
  return:
  
  desc: sets the colour of every pixel on the screen
  
  note:
  
\**************************************/
void PCD8544_FillScreenColor(PCD8544_Handle* pPcd8544Handle, u8 isBlack)
{
    isBlack = isBlack? 0xFF : 0x00;
    for (u16 i = 0; i < PCD8544_SCREEN_SIZE; i++)
        pPcd8544Handle->pFrameBuffer[i] = isBlack;
}

/*************************************\
  fn: @PCD8544_UpdateScreen
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: update the screen with the new changes
  
  note: the reason why you have to update the screen is because the other display screen drawing funcs dont actually write to
        the display RAM, it just writes to the buffer in the handle and this func sets the whole buffer to the displays RAM
  
\**************************************/
void PCD8544_UpdateScreen(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    u8 command = SETXADDR_0;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

    for (u16 i = 0; i < PCD8544_SCREEN_HEIGHT; i++)
    {
        GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
        command = SETYADDR_0 + i;
        SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

        GPIO_WritePin(pPcd8544Handle->pDcPin, HIGH);
        SPI_TransmitData(pPcd8544Handle->pSpiHandle, &pPcd8544Handle->pFrameBuffer[i*PCD8544_SCREEN_WIDTH], PCD8544_SCREEN_WIDTH);
    }
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}