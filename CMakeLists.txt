
cmake_minimum_required(VERSION 3.25)

project(SensorDisplaySystem LANGUAGES C ASM)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -O2 -g")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4 -mthumb -g")

include_directories(
    ${CMAKE_SOURCE_DIR}/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/Inc
)

# Gather all source files
file(GLOB_RECURSE SOURCES
    Src/*.c
    Drivers/Src/*.c
    Startup/*.s
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F401CCUX_FLASH.ld)
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS "-T${LINKER_SCRIPT}")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)