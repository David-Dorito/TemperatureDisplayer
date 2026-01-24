
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Prevent CMake from trying to link executables
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU flags (adjust if needed)
set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4 -mthumb")