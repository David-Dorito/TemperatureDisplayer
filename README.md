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

## Project status
The project is currently in its first complete version. Future updates may include improvements and additional features.

## Setup
For hardware wiring, required components, and flashing instructions, see [Setup.md](Setup.md).