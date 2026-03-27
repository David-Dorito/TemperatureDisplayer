cmake_minimum_required(VERSION 3.25)

project(TemperatureDisplayer LANGUAGES C ASM)

set(CMAKE_BUILD_TYPE Debug)
set(TARGET ${PROJECT_NAME}.elf)

add_compile_options(
    -mcpu=cortex-m4
    -mthumb
    -O0
    -g3
)

add_library(Drivers
    Drivers/GPIO/stm32f401xx_gpio_driver.c
    Drivers/SPI/stm32f401xx_spi_driver.c
    Drivers/I2C/stm32f401xx_i2c_driver.c
    Drivers/NVIC/stm32f401xx_nvic_driver.c
    Drivers/Clock/stm32f401xx_clocks.c
    Drivers/PCD8544/pcd8544_driver.c
    Drivers/MCP9808/mcp9808_driver.c
)
target_include_directories(Drivers PUBLIC
    Drivers/
    Drivers/GPIO
    Drivers/SPI
    Drivers/I2C
    Drivers/NVIC
    Drivers/Clock
    Drivers/MCP9808
    Drivers/PCD8544
)

add_library(GfxLib
    Libs/GfxLib/GfxLib.c
)
target_include_directories(GfxLib PUBLIC
    Libs/GfxLib/
)


file(GLOB_RECURSE SOURCES
    Src/*.c
    Startup/*.s
    Inc/*.c
)

add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PUBLIC Inc
    Inc/
)

target_link_options(${TARGET} PRIVATE
    -T${CMAKE_SOURCE_DIR}/STM32F401CCUX_FLASH.ld
    -mcpu=cortex-m4
    -mthumb
)

target_link_libraries(${TARGET} Drivers)
target_link_libraries(${TARGET} GfxLib)

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
            -O binary
            ${PROJECT_NAME}.elf
            ${PROJECT_NAME}.bin
)