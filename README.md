# **SensorDisplaySystem Project**

## Project Overview
SensorDisplaySystem is an embedded systems project built on the STM32F401CCU microcontroller.
The project focuses on bare-metal driver development, with custom drivers written for GPIO, SPI, I²C, and UART and used together in a single application.

The project was developed to apply low-level concepts such as direct register access, interrupt handling, and peripheral configuration in a practical system.

## System Description
When a user presses a button, an external interrupt is generated via EXTI and handled by the NVIC.
Inside the interrupt handler, temperature data is read from a sensor over I²C and transmitted to a display using SPI.

A second button allows the current temperature value to be sent to a connected PC over USART through a UART-to-USB converter.

## Learning Objectives
This project was used to deepen understanding of microcontroller internals, interrupt systems, and peripheral configuration at the register level.
Special emphasis was placed on writing maintainable, reusable drivers without relying on vendor abstraction layers.

## Technical Highlights
- Register-level programming without HAL
- Custom peripheral drivers with configuration structures and handles
- Interrupt-driven input handling
- Integration of GPIO, SPI, I²C, and USART in one project

## Hardware Used
- MCU: **STM32F401CCU**
- Temperature sensor: **Seeed Studio Grove MCP0908**
- Display: **Nokia5110 84x48 LCD**
- USART-USB converter: **QIQIAZI UART-TTL USB Adapter CH340G**

## Project status
This project is currently under development, core drivers are being implemented.

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