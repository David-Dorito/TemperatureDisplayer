#ifndef PIC18F16Q20_VIC_DRIVER_H_
#define PIC18F16Q20_VIC_DRIVER_H_

#include "types.h"

#define IRQ_NUM_SOFTWARE                    0x00U
#define IRQ_NUM_EXTERNINT0                  0x01U
#define IRQ_NUM_EXTERNINT1                  0x02U
#define IRQ_NUM_EXTERNINT2                  0x03U
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

#define EXTINT0                             0
#define EXTINT1                             1
#define EXTINT2                             2

/*************************************\
  fn: @VIC_SetShadowRegEnabled
  
  param1 u8: enable or disable?
  
  return:
  
  desc: enables or disables the shadow reg for HIGH priority interrupts
  
  note:
  
\**************************************/
inline void VIC_SetShadowRegEnabled(u8 isEnabled);

/*************************************\
  fn: @VIC_SetExtIntTriggerEdge
  
  param1 u8: the external interrupt number
  param2 u8: rising or falling edge?
  
  return:
  
  desc: configures the external interrupt trigger for rising or falling edge
  
  note:
  
\**************************************/
inline void VIC_SetExtIntTriggerEdge(u8 ExtIntNum, u8 isRising);

/*************************************\
  fn: @VIC_SetIrqPrioEnabled
  
  param1 u8: enable or disable priority levels for interrupts
  
  return:
  
  desc: enables or disables wether all interrupts should count as high prio or if there should be
        low priority ones aswell
  
  note: by default (disabled) all interrupts are high priority
  
\**************************************/
inline void VIC_SetIrqPrioEnabled(u8 isEnabled);

/*************************************\
  fn: @VIC_SetIrqsEnabled
  
  param1 u8: enable or disable high priority interrupts
  param2 u8: enable or disable low priority interrupts
  
  return:
  
  desc: controls if all the interrupts on the high and low priority level should be enabled or disabled
  
  note: disabling high priority interrupts also disables low priority interrupts
  
\**************************************/
inline void VIC_SetIrqsEnabled(u8 isHighPrioEnabled, u8 isLowPrioEnabled);

/*************************************\
  fn: @VIC_SetIrqVTable
  
  param1 u16*: ptr to the vector table of interrupt handler functions
  
  return:
  
  desc: sets the vector table for interrupt handler funcs in VIC
  
  note:
  
\**************************************/
inline void VIC_SetIrqVTable(u16* pVTable);

/*************************************\
  fn: @VIC_SetIrqEnabled
  
  param1 u8: the irq number of the interrupt
  param2 u8: enable or disable?
  
  return:
  
  desc: enables or disables the interrupt which holds the specified IRQ number
  
  note: you have to call this function if you want an interrupt to trigger
  
\**************************************/
inline void VIC_SetIrqEnabled(u8 irqNum, u8 isEnabled);

/*************************************\
  fn: @VIC_SetIrqPrio
  
  param1 u8: the irq number of the interrupt
  param2 u8: the priority of the interrupt (high or low)
  
  return:
  
  desc: sets the interrupt priority for the specified IRQ number
  
  note:
  
\**************************************/
inline void VIC_SetIrqPrio(u8 irqNum, u8 priority);

#endif