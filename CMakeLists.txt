cmake_minimum_required(VERSION 3.25)

project(TemperatureDisplayer LANGUAGES C ASM)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(
    -mcpu=cortex-m4
    -mthumb
    -O0
    -g3
)

add_library(HAL
    Drivers/GPIO/stm32f401xx_gpio_driver.c
    Drivers/SPI/stm32f401xx_spi_driver.c
    Drivers/I2C/stm32f401xx_i2c_driver.c
    Drivers/NVIC/stm32f401xx_nvic_driver.c
)
target_include_directories(HAL PUBLIC
    Drivers/GPIO
    Drivers/SPI
    Drivers/I2C
    Drivers/NVIC
)

include_directories(Inc
    Drivers/Inc
    Libs/GfxLib
    Inc/
)

file(GLOB_RECURSE SOURCES
    Src/*.c
    Drivers/Src/*.c
    Startup/*.s
    Libs/GfxLib/*.c
    Inc/*.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${CMAKE_SOURCE_DIR}/STM32F401CCUX_FLASH.ld
    -mcpu=cortex-m4
    -mthumb
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
            -O binary
            ${PROJECT_NAME}.elf
            ${PROJECT_NAME}.bin
)