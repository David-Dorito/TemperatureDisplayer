#ifndef BSP_H_
#define BSP_H_

#include "definitions.h"
#include "stm32f401xx.h"
#include "stm32f401xx_nvic_driver.h"
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx_i2c_driver.h"
#include "pcd8544_driver.h"
#include "mcp9808_driver.h"
#include "stm32f401xx_clocks.h"
#include "GfxLib.h"
#include "Fonts.h"

extern GPIO_Handle buttonPin;
extern PCD8544_Handle lcdHandle;
extern MCP9808_Handle sensorHandle;
extern GfxLib_Handle gfxlibHandle;

void BSP_Init();

#endif