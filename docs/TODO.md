### **TODO list for this project**

## Driver Layer
1. [X] Complete GPIO drivers
2. [X] Complete SPI drivers
3. [ ] Implement I²C drivers
4. [ ] Implement USART drivers

## Application Layer
1. [ ] Configure GPIO button with external interrupt (EXTI)
2. [ ] Create interrupt handler that sends a read request to the temperature sensor over I²C
3. [ ] Write code to send temperature data to the display using SPI
4. [ ] Configure second GPIO button with external interrupt
5. [ ] Implement interrupt handler to transmit temperature data to PC over USART