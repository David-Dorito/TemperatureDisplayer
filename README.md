### **SensorDisplaySystem Project**

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
- Display: **AZDelivery 84x48 LCD**
- USART-USB converter: **QIQIAZI UART-TTL USB Adapter CH340G**

## Project status
This project is currently under development, core drivers are being implemented.