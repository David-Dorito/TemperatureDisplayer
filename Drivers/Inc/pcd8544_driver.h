#ifndef PCD8544_DRIVER_H_
#define PCD8544_DRIVER_H_

#include "../Inc/stm32f401xx_gpio_driver.h"
#include "../Inc/stm32f401xx_spi_driver.h"

#define PCD8544_SCREEN_WIDTH            84
#define PCD8544_SCREEN_HEIGHT           48
#define PCD8544_SCREEN_SIZE             PCD8544_SCREEN_WIDTH * (PCD8544_SCREEN_HEIGHT / 8)

#define PCD8544_DISPLAYMODE_BLANK       0b00001000
#define PCD8544_DISPLAYMODE_NORMAL      0b00001100
#define PCD8544_DISPLAYMODE_ALLSEGON    0b00001001
#define PCD8544_DISPLAYMODE_INVERSE     0b00001101

typedef struct {
    SPI_Handle* pSpiHandle;
    GPIO_Handle* pDcPin;
    GPIO_Handle* pResPin;
    GPIO_Handle* pCsPin;
    GPIO_Handle* pLedPin;
    GPIO_Handle* pVccPin;
    u8* pFrameBuffer;
} PCD8544_Handle;

/*************************************\
  fn: @PCD8544_TurnOn
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: turns the display on using the sequence described in the datasheet
  
  note:
  
\**************************************/
void PCD8544_TurnOn(PCD8544_Handle* pPcd8544Handle);

/*************************************\
  fn: @PCD8544_TurnOff
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: turns the display off
  
  note: also pulls chip select to HIGH and Data/Command to LOW
  
\**************************************/
void PCD8544_TurnOff(PCD8544_Handle* pPcd8544Handle);

/*************************************\
  fn: @PCD8544_SetSleepMode
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: enable or disable sleep mode of the display
  
  return:
  
  desc: enables or disables the sleep mode of the display
  
  note: display will stop displaying an image if turned on but RAM will NOT get cleared,
        so once you turn off sleep mode it will start displaying the image again
  
\**************************************/
void PCD8544_SetSleepMode(PCD8544_Handle* pPcd8544Handle, u8 isEnabled);

/*************************************\
  fn: @PCD8544_SetBacklight
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: enable or disable sleep mode of the display
  
  return:
  
  desc: enables or disables the background light of the display
  
  note: function is very basic, just a wrapper for GPIO_WritePin() with the LED pin as the arg
  
\**************************************/
void PCD8544_SetBacklight(PCD8544_Handle* pPcd8544Handle, u8 isEnabled);

/*************************************\
  fn: @PCD8544_SetDisplayMode
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: new mode of the display
  
  return:
  
  desc: sets the mode of the display
  
  note: use the PCD8544_DISPLAYMODE_XXX macros as the mode arg, view the datasheet for a description of what they do
  
\**************************************/
void PCD8544_SetDisplayMode(PCD8544_Handle* pPcd8544Handle, u8 mode);

/*************************************\
  fn: @PCD8544_TogglePixel
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: x position of the pixel
  param3 u8: y position of the pixel
  
  return:
  
  desc: toggles the colour of the pixel at the specified x and y position
  
  note:
  
\**************************************/
void PCD8544_TogglePixel(PCD8544_Handle* pPcd8544Handle, u8 posX, u8 posY);

/*************************************\
  fn: @PCD8544_DrawPixel
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: the colour of the pixel
  param3 u8: x position of the pixel
  param4 u8: y position of the pixel
  
  return:
  
  desc: sets the colour of the pixel at the specified x and y position
  
  note:
  
\**************************************/
void PCD8544_DrawPixel(PCD8544_Handle* pPcd8544Handle, u8 isBlack, u8 posX, u8 posY);

/*************************************\
  fn: @PCD8544_FillScreen
  
  param1 PCD8544_Handle*: the handle of the display
  param2 u8: the colour to set every pixel to
  
  return:
  
  desc: sets the colour of every pixel on the screen
  
  note:
  
\**************************************/
void PCD8544_FillScreen(PCD8544_Handle* pPcd8544Handle, u8 isBlack);

/*************************************\
  fn: @PCD8544_UpdateScreen
  
  param1 PCD8544_Handle*: the handle of the display
  
  return:
  
  desc: update the screen with the new changes
  
  note: the reason why you have to update the screen is because the other display screen drawing funcs dont actually write to
        the display RAM, it just writes to the buffer in the handle and this func sets the whole buffer to the displays RAM
  
\**************************************/
void PCD8544_UpdateScreen(PCD8544_Handle* pPcd8544Handle);

#endif