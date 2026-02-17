#include "../Inc/pcd8544_driver.h"
#include "../Inc/stm32f401xx_clocks.h"
#include <stddef.h>

#define SET_XADDR_0         0b10000000
#define SET_YADDR_0         0b01000000
#define SET_POWERDOWN       0b00100100
#define SET_POWERUP         0b00100000
#define SET_EXTENDINST      0b00100001
#define SET_BASICINST       0b00100000
#define SET_VOP             0b10000000
#define SET_TC              0b00000100
#define SET_DISPLAYMODE     0b00001000
#define SET_BIAS_1_48       0b00010011

/*************************************\
  fn: @PCD8544_Init
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: turns the display on using the sequence described in the datasheet and sets some basic configurations
  
  note: sets the contrast to PCD8544_CONTRAST_DEFAULT found in the header file
  
\**************************************/

void PCD8544_Init(PCD8544_Handle* pPcd8544Handle)
{
    // Control VCC if user provides the pin, otherwise assume external 3.3V
    if (pPcd8544Handle->pVccPin != NULL)
    {
        GPIO_WritePin(pPcd8544Handle->pVccPin, HIGH);
        UnpreciseDelay(10);  // Wait for VCC to stabilize
    }
    
    // Reset sequence
    GPIO_WritePin(pPcd8544Handle->pResPin, LOW);
    UnpreciseDelay(1);  // Min 100ns, 1ms is safe
    GPIO_WritePin(pPcd8544Handle->pResPin, HIGH);
    UnpreciseDelay(50);  // Wait for internal reset
    
    // Send configuration commands
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    
    u8 command = SET_EXTENDINST;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    command = (SET_VOP | PCD8544_CONTRAST_DEFAULT);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    command = SET_TC;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    command = SET_BIAS_1_48;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    command = SET_BASICINST;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    command = PCD8544_DISPLAYMODE_NORMAL;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

/*************************************\
  fn: @PCD8544_Deinit
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: turns the display off
  
  note: also pulls chip select to HIGH and Data/Command to LOW
  
\**************************************/
void PCD8544_Deinit(PCD8544_Handle* pPcd8544Handle)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    if (pPcd8544Handle->pVccPin != NULL) GPIO_WritePin(pPcd8544Handle->pVccPin, LOW);
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
    GPIO_WritePin(pPcd8544Handle->pLedPin, !isEnabled);
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
        isEnabled = SET_POWERDOWN;
    else
        isEnabled = SET_POWERUP;

    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &isEnabled, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
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
    mode &= (SET_DISPLAYMODE | 0b00000101);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &mode, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

/*************************************\
  fn: @PCD8544_SetTempCoeff
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: the temperature coefficient
  
  return:
  
  desc: sets the temperature coefficient of the display
  
  note: use the PCD8544_TEMPCOEFF_XXX macros as the coefficient arg, view the datasheet for a description of what they do
  
\**************************************/
void PCD8544_SetTempCoeff(PCD8544_Handle* pPcd8544Handle, u8 coefficient)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);
    coefficient &= (SET_TC | 00000011);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &coefficient, 1);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}

/*************************************\
  fn: @PCD8544_SetContrast
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: new contrast of the display
  
  return:
  
  desc: sets the contrast of the display
  
  note: 
  
\**************************************/
void PCD8544_SetContrast(PCD8544_Handle* pPcd8544Handle, u8 contrast)
{
    GPIO_WritePin(pPcd8544Handle->pCsPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);

    u8 command = SET_EXTENDINST;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

    command = (SET_VOP | contrast);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    
    command = SET_BASICINST;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

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
    u8 command = SET_XADDR_0;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);
    command = SET_YADDR_0;
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, &command, 1);

    GPIO_WritePin(pPcd8544Handle->pDcPin, HIGH);
    SPI_TransmitData(pPcd8544Handle->pSpiHandle, pPcd8544Handle->pFrameBuffer, PCD8544_SCREEN_SIZE);
    GPIO_WritePin(pPcd8544Handle->pDcPin, LOW);

    GPIO_WritePin(pPcd8544Handle->pCsPin, HIGH);
}