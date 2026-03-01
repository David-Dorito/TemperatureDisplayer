#ifndef BSP_H_
#define BSP_H_

#include <stddef.h>
#include "../Drivers/Inc/stm32f401xx.h"
#include "../Drivers/Inc/stm32f401xx_gpio_driver.h"
#include "../Drivers/Inc/stm32f401xx_spi_driver.h"
#include "../Drivers/Inc/stm32f401xx_i2c_driver.h"
#include "../Drivers/Inc/pcd8544_driver.h"
#include "../Drivers/Inc/mcp9808_driver.h"
#include "../Drivers/Inc/stm32f401xx_clocks.h"
#include "../Libs/Gfxlib/GfxLib.h"
#include "../Inc/Fonts.h"

extern GPIO_Handle buttonPin;

extern SPI_Handle lcdSpiHandle;
extern GPIO_Handle lcdResetPin;
extern GPIO_Handle lcdSelectPin;
extern GPIO_Handle lcdDcPin;
extern GPIO_Handle lcdSckPin;
extern GPIO_Handle lcdMosiPin;
extern GPIO_Handle lcdBacklightPin;
extern PCD8544_Handle lcdHandle;

extern I2C_Handle sensorI2cHandle;
extern GPIO_Handle sensorSdaPin;
extern GPIO_Handle sensorSclPin;
extern MCP9808_Handle sensorHandle;

extern GfxLib_Handle gfxlibHandle;

#endif