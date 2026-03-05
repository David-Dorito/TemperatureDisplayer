#ifndef PIC18F16Q20_VIC_DRIVER_H_
#define PIC18F16Q20_VIC_DRIVER_H_

#include "pic18f16q20.h"

#define IRQ_NUM_SOFTWARE                    0x00U
#define IRQ_NUM_INT0                        0x01U
#define IRQ_NUM_INT1                        0x02U
#define IRQ_NUM_INT2                        0x03U
#define IRQ_NUM_DMA1SCNT                    0x04U
#define IRQ_NUM_DMA1DCNT                    0x05U
#define IRQ_NUM_DMA1OR                      0x06U
#define IRQ_NUM_DMA1A                       0x07U
#define IRQ_NUM_DMA2SCNT                    0x08U
#define IRQ_NUM_DMA2DCNT                    0x09U
#define IRQ_NUM_DMA2OR                      0x0AU
#define IRQ_NUM_DMA2A                       0x0BU
#define IRQ_NUM_DMA3SCNT                    0x0CU
#define IRQ_NUM_DMA3DCNT                    0x0DU
#define IRQ_NUM_DMA3OR                      0x0EU
#define IRQ_NUM_DMA3A                       0x0FU
#define IRQ_NUM_DMA4SCNT                    0x10U
#define IRQ_NUM_DMA4DCNT                    0x11U
#define IRQ_NUM_DMA4OR                      0x12U
#define IRQ_NUM_DMA4A                       0x13U
#define IRQ_NUM_VDDIO2                      0x1AU
#define IRQ_NUM_VDDIO3                      0x1BU
#define IRQ_NUM_TIMER0                      0x1DU
#define IRQ_NUM_TIMER1                      0x1EU
#define IRQ_NUM_TIMER1G                     0x1FU
#define IRQ_NUM_TIMER2                      0x20U
#define IRQ_NUM_TIMER4                      0x21U
#define IRQ_NUM_UART1RX                     0x30U
#define IRQ_NUM_UART1TX                     0x31U
#define IRQ_NUM_UART1                       0x32U
#define IRQ_NUM_UART1ERR                    0x33U
#define IRQ_NUM_UART2RX                     0x34U
#define IRQ_NUM_UART2TX                     0x35U
#define IRQ_NUM_UART2                       0x36U
#define IRQ_NUM_UART2ERR                    0x37U
#define IRQ_NUM_SPI1RX                      0x38U
#define IRQ_NUM_SPI1TX                      0x39U
#define IRQ_NUM_SPI1                        0x3AU
#define IRQ_NUM_I2C1RX                      0x3BU
#define IRQ_NUM_I2C1TX                      0x3CU
#define IRQ_NUM_I2C1                        0x3DU
#define IRQ_NUM_I2C1ERR                     0x3EU

void VIC_SetShadowRegEnabled(u8 isEnabled);
void VIC_SetIrqVTable(u16* pVTable);
void VIC_SetIrqEnabled(u8 irqNum, u8 isEnabled);
void VIC_SetIrqPriority(u8 irqNum, u8 priority);

#endif