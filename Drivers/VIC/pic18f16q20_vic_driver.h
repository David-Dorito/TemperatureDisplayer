#ifndef PIC18F16Q20_VIC_DRIVER_H_
#define PIC18F16Q20_VIC_DRIVER_H_

#include "../Internal/types.h"

#define VIC_IRQ_SOFTWARE                    0x00U
#define VIC_IRQ_INT0                        0x01U
#define VIC_IRQ_INT1                        0x02U
#define VIC_IRQ_INT2                        0x03U
#define VIC_IRQ_DMA1SCNT                    0x04U
#define VIC_IRQ_DMA1DCNT                    0x05U
#define VIC_IRQ_DMA1OR                      0x06U
#define VIC_IRQ_DMA1A                       0x07U
#define VIC_IRQ_DMA2SCNT                    0x08U
#define VIC_IRQ_DMA2DCNT                    0x09U
#define VIC_IRQ_DMA2OR                      0x0AU
#define VIC_IRQ_DMA2A                       0x0BU
#define VIC_IRQ_DMA3SCNT                    0x0CU
#define VIC_IRQ_DMA3DCNT                    0x0DU
#define VIC_IRQ_DMA3OR                      0x0EU
#define VIC_IRQ_DMA3A                       0x0FU
#define VIC_IRQ_DMA4SCNT                    0x10U
#define VIC_IRQ_DMA4DCNT                    0x11U
#define VIC_IRQ_DMA4OR                      0x12U
#define VIC_IRQ_DMA4A                       0x13U
#define VIC_IRQ_VDDIO2                      0x1AU
#define VIC_IRQ_VDDIO3                      0x1BU
#define VIC_IRQ_IOC                         0x1CU
#define VIC_IRQ_TMR0                        0x1DU
#define VIC_IRQ_TMR1                        0x1EU
#define VIC_IRQ_TMR1G                       0x1FU
#define VIC_IRQ_TMR2                        0x20U
#define VIC_IRQ_TMR4                        0x21U
#define VIC_IRQ_TU16A                       0x22U
#define VIC_IRQ_TU16B                       0x23U
#define VIC_IRQ_CCP1                        0x24U
#define VIC_IRQ_CCP2                        0x25U
#define VIC_IRQ_PWM1RINT                    0x26U
#define VIC_IRQ_PWM1GINT                    0x27U
#define VIC_IRQ_PWM2RINT                    0x28U
#define VIC_IRQ_PWM2GINT                    0x29U
#define VIC_IRQ_CWG1                        0x2AU
#define VIC_IRQ_CLC1                        0x2BU
#define VIC_IRQ_CLC2                        0x2CU
#define VIC_IRQ_CLC3                        0x2DU
#define VIC_IRQ_CLC4                        0x2EU
#define VIC_IRQ_IOCSR                       0x2FU
#define VIC_IRQ_U1RX                        0x30U
#define VIC_IRQ_U1TX                        0x31U
#define VIC_IRQ_U1                          0x32U
#define VIC_IRQ_U1E                         0x33U
#define VIC_IRQ_U2RX                        0x34U
#define VIC_IRQ_U2TX                        0x35U
#define VIC_IRQ_U2                          0x36U
#define VIC_IRQ_U2E                         0x37U
#define VIC_IRQ_SPI1RX                      0x38U
#define VIC_IRQ_SPI1TX                      0x39U
#define VIC_IRQ_SPI1                        0x3AU
#define VIC_IRQ_I2C1RX                      0x3BU
#define VIC_IRQ_I2C1TX                      0x3CU
#define VIC_IRQ_I2C1                        0x3DU
#define VIC_IRQ_I2C1E                       0x3EU
#define VIC_IRQ_RESERVED_0X3F               0x3FU
#define VIC_IRQ_I3C1RX                      0x40U
#define VIC_IRQ_I3C1TX                      0x41U
#define VIC_IRQ_I3C1                        0x42U
#define VIC_IRQ_I3C1E                       0x43U
#define VIC_IRQ_I3C1R                       0x44U
#define VIC_IRQ_I3C2RX                      0x45U
#define VIC_IRQ_I3C2TX                      0x46U
#define VIC_IRQ_I3C2                        0x47U
#define VIC_IRQ_I3C2E0                      0x48U
#define VIC_IRQ_I3C2E1                      0x49U
#define VIC_IRQ_I3C2E2                      0x4AU
#define VIC_IRQ_I3C2E3                      0x4BU
#define VIC_IRQ_I3C2R                       0x4CU
#define VIC_IRQ_HLVD                        0x4DU
#define VIC_IRQ_AD                          0x4EU
#define VIC_IRQ_ADT                         0x4FU
#define VIC_IRQ_RESERVED_0X50               0x50U

/*************************************\
  fn: @VIC_SetShadowRegEnabled
  
  param1 u8: enable or disable?
  
  return:
  
  desc: enables or disables the shadow reg for HIGH priority interrupts
  
  note:
  
\**************************************/
void VIC_SetShadowRegEnabled(u8 isEnabled);

/*************************************\
  fn: @VIC_SetExtIntTriggerEdge
  
  param1 u8: the external interrupt number
  param2 u8: rising or falling edge?
  
  return:
  
  desc: configures the external interrupt trigger for rising or falling edge
  
  note:
  
\**************************************/
void VIC_SetExtIntTriggerEdge(u8 ExtIntNum, u8 isRising);

/*************************************\
  fn: @VIC_SetIrqPrioEnabled
  
  param1 u8: enable or disable priority levels for interrupts
  
  return:
  
  desc: enables or disables wether all interrupts should count as high prio or if there should be
        low priority ones aswell
  
  note: by default (disabled) all interrupts are high priority
  
\**************************************/
void VIC_SetIrqPrioEnabled(u8 isEnabled);

/*************************************\
  fn: @VIC_SetIrqsEnabled
  
  param1 u8: enable or disable high priority interrupts
  param2 u8: enable or disable low priority interrupts
  
  return:
  
  desc: controls if all the interrupts on the high and low priority level should be enabled or disabled
  
  note: disabling high priority interrupts also disables low priority interrupts
  
\**************************************/
void VIC_SetIrqsEnabled(u8 isHighPrioEnabled, u8 isLowPrioEnabled);

/*************************************\
  fn: @VIC_SetIrqVTable
  
  param1 u16*: ptr to the vector table of interrupt handler functions
  
  return:
  
  desc: sets the vector table for interrupt handler funcs in VIC
  
  note:
  
\**************************************/
void VIC_SetIrqVTable(u16* pVTable);

/*************************************\
  fn: @VIC_SetIrqEnabled
  
  param1 u8: the irq number of the interrupt
  param2 u8: enable or disable?
  
  return:
  
  desc: enables or disables the interrupt which holds the specified IRQ number
  
  note: you have to call this function if you want an interrupt to trigger
  
\**************************************/
void VIC_SetIrqEnabled(u8 irqNum, u8 isEnabled);

/*************************************\
  fn: @VIC_SetIrqPrio
  
  param1 u8: the irq number of the interrupt
  param2 u8: the priority of the interrupt (high or low)
  
  return:
  
  desc: sets the interrupt priority for the specified IRQ number
  
  note:
  
\**************************************/
void VIC_SetIrqPrio(u8 irqNum, u8 priority);

/*************************************\
  fn: @VIC_GetIrqStatus
  
  param1 u8: the irq number of the interrupt
  
  return u8: true if interrupt is being fired because of this irq number, else false
  
  desc: returns true if the given IRQ has triggered an interrupt
  
  note:
  
\**************************************/
u8 VIC_GetIrqStatus(u8 irqNum);

/*************************************\
  fn: @VIC_ClearrIrqStatus
  
  param1 u8: the irq number of the interrupt
  
  return:
  
  desc: clears the interrupt status bit in the status register to avoid another ISR being fired
  
  note:
  
\**************************************/
void VIC_ClearIrqStatus(u8 irqNum);

#endif