#ifndef BSP_H_
#define BSP_H_

//#include "../Drivers/SPI/pic18f16q20_spi_driver.h"
//#include "../Drivers/I2C/pic18f16q20_i2c_driver.h"
//#include "../Drivers/Clock/stm32f401xx_clocks.h"
#include "../Drivers/Internal/types.h"
#include "../Drivers/GPIO/pic18f16q20_gpio_driver.h"
#include "../Drivers/VIC/pic18f16q20_vic_driver.h"
#include "../Drivers/PCD8544/pcd8544_driver.h"
#include "../Drivers/MCP9808/mcp9808_driver.h"
#include "../Libs/GfxLib/GfxLib.h"
#include "../Inc/Fonts.h"

extern GPIO_Handle btnPin;

void BSP_Init(void);

#endif