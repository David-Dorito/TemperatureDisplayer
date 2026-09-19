cmake_minimum_required(VERSION 4.3.0)

project(TemperatureDisplayer LANGUAGES C ASM)

add_library(stm32f401xx INTERFACE)
target_compile_options(stm32f401xx
INTERFACE
	-mcpu=cortex-m4
	-mthumb
	-O0
	-g3
)
target_link_options(stm32f401xx
INTERFACE
	-T${CMAKE_SOURCE_DIR}/STM32F401CCUX_FLASH.ld
	-mcpu=cortex-m4
	-mthumb
)

add_library(drivers)
target_sources(drivers
PRIVATE
	Drivers/GPIO/stm32f401xx_gpio_driver.c
	Drivers/SPI/stm32f401xx_spi_driver.c
	Drivers/I2C/stm32f401xx_i2c_driver.c
	Drivers/NVIC/stm32f401xx_nvic_driver.c
	Drivers/Clock/stm32f401xx_clocks.c
	Drivers/MCP9808/mcp9808_driver.c
)
target_include_directories(drivers
PUBLIC
	Drivers/
	Drivers/GPIO
	Drivers/SPI
	Drivers/I2C
	Drivers/NVIC
	Drivers/Clock
	Drivers/MCP9808
)
target_link_libraries(drivers stm32f401xx)

add_subdirectory(Libs/GfxLib)
target_link_libraries(gfxlib stm32f401xx)

add_subdirectory(Drivers/PCD8544)
target_link_libraries(pcd8544_drivers stm32f401xx)

set(TARGET "${PROJECT_NAME}.elf")
add_executable(${TARGET})
target_sources(${TARGET}
PRIVATE
	Src/main.c
	Src/syscalls.c
	Src/sysmem.c
	Startup/startup_stm32f401ccux.s
	Inc/bsp.c
	Inc/Fonts.c
)
target_include_directories(${TARGET} PRIVATE Inc
	Inc/
)
target_link_libraries(${TARGET}
PRIVATE
	stm32f401xx
	gfxlib
	drivers
	pcd8544_drivers
)
