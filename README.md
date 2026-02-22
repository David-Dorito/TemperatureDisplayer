# **TemperatureDisplayer Project**

## Project Overview
TemperatureDisplayer is a bare-metal firmware project for the STM32F401CCU microcontroller.  
It reads temperature data from an MCP9808 sensor and displays it on a PCD8544 LCD, using fully custom drivers for GPIO, SPI, and I²C.  
The project demonstrates low-level peripheral integration and driver development in a single embedded application.

## System Description
When a user presses the button, an external interrupt is generated via EXTI and handled by the NVIC.  
The interrupt sets a flag that the main loop later processes. In the main loop, temperature data is read from the MCP9808 sensor over I²C, rendered using the graphics layer, and sent to the PCD8544 display via SPI.

## Project Goals
This project was created to practice low-level microcontroller concepts, including direct register access, interrupt handling, and peripheral configuration.  
A key objective was to implement reusable drivers which do not rely on vendor HAL libraries.

## Engineering Highlights
- Structured firmware architecture with explicit separation of concerns  
  (Peripheral → Device → Graphics → Application)
- Device drivers and graphics renderer designed for portability with no coupling, using generic interface functions
- Interrupt-driven input handling for the user button
- Fully register-level implementation without vendor-provided HAL libraries

## Hardware Used
- MCU: **STM32F401CCU**
- Temperature sensor: **Seeed Studio Grove MCP9808**
- Display: **PCD8544 84x48 LCD (also known as Nokia 5110 display)**

## Project status
The project is currently in its first complete version. Future updates may include improvements and additional features.

## Cloning, Building and Flashing this project
### 1. Prerequisites
**You need these installed on your system to build and flash this project:**
- ARM GCC toolchain
    - arm-none-eabi-gcc (tested with version 13.3.1)
- CMake (version 3.25 or higher)
- Ninja
- VS Code (optional) with:
    - CMake Tools extension
    - clangd extension
- STM32CubeProgrammer (recommended), or alternative tools for flashing

*if you have STM32CubeIDE installed, you already have a working ARM toolchain*

### 2. Clone the repository
From the directory you want to clone to:
```bash
git clone https://github.com/David-Dorito/SensorDisplaySystem.git master
cd SensorDisplaySystem
```
This clones the project from the repo and puts bash into the project root.

### 3. Configure the project
From the project root:
```bash
cmake -S . -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=cmake/arm-gcc-toolchain.cmake \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```
This:
- Configures the project for bare metal STM32
- Generates compile_commands.json
- Uses Ninja for fast builds

### 4. Build the project
Again from the project root:
```bash
cmake --build build
```
Output files (`.elf`, `.bin`, `.hex`) will appear in the build/ directory

### 5. Flashing (not included)
Flashing is not handled by CMake. Use one of these to flash the `.elf` file:
- STM32CubeProgrammer
- STM32CubeIDE
- Any other program used for flashing