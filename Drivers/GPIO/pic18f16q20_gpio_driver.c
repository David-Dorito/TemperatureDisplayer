#include <pic18f16q20.h>
#include "pic18f16q20_gpio_driver.h"
#include "Internal/IOC/pic18f16q20_ioc_driver.h"
#include "Internal/PPS/pic18f16q20_pps_driver.h"
#include "../VIC/pic18f16q20_vic_driver.h"

#define ANSELX          0
#define WPUX            1
#define ODCONX          2
#define SLRCONX         3
#define INLVLX          4
#define PORTX           5
#define TRISX           6
#define LATX            7

#define ANSELX_RST      0xFF
#define WPUX_RST        0x00
#define ODCONX_RST      0x00
#define SLRCONX_RST     0xFF
#define INLVLX_RST      0xFF
#define TRISX_RST       0xFF

static volatile u8* const GPIO_REGS[3][8] = {
    {&ANSELA, &WPUA, &ODCONA, &SLRCONA, &INLVLA, &PORTA, &TRISA, &LATA},
    {&ANSELB, &WPUB, &ODCONB, &SLRCONB, &INLVLB, &PORTB, &TRISB, &LATB},
    {&ANSELC, &WPUC, &ODCONC, &SLRCONC, &INLVLC, &PORTC, &TRISC, &LATC}
};

/*************************************\
  fn: @GPIO_Init
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: error status return, 0 means OK 
  
  desc: configures the gpio pin
  
  note: 
  
\**************************************/
u8 GPIO_Init(GPIO_Handle* pGpioHandle)
{
    *GPIO_REGS[pGpioHandle->Port][TRISX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][TRISX] |= (pGpioHandle->Config.Direction << pGpioHandle->Pin);
    
    *GPIO_REGS[pGpioHandle->Port][ANSELX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][ANSELX] |= (pGpioHandle->Config.InAnalogEn << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][WPUX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][WPUX] |= (pGpioHandle->Config.PullupEn << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][ODCONX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][ODCONX] |= (pGpioHandle->Config.OpType << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][SLRCONX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][SLRCONX] |= (pGpioHandle->Config.OpSpeed << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][INLVLX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][INLVLX] |= (pGpioHandle->Config.InMode << pGpioHandle->Pin);
    
    if (pGpioHandle->Config.AltFuncEn)
    {
        if (pGpioHandle->Config.Direction == GPIO_DIRECTION_INPUT)
            PPS_SetInput(pGpioHandle->Port, pGpioHandle->Pin, pGpioHandle->Config.AltFuncNum);
        else
            PPS_SetOutput(pGpioHandle->Port, pGpioHandle->Pin, pGpioHandle->Config.AltFuncNum);
    }
    
    if (pGpioHandle->Config.RtFtDetect)
    {
        if (pGpioHandle->Config.IntSrc != GPIO_INTSRC_IOC)
        {
            if (pGpioHandle->Config.RtFtDetect == GPIO_RTFTDETECT_RTFT)
                return GPIO_INIT_INVALIDTRIGGERS;
            VIC_SetExtIntTriggerEdge(pGpioHandle->Config.IntSrc, pGpioHandle->Config.RtFtDetect == GPIO_RTFTDETECT_RT);
        }
        else
            IOC_SetPinTriggers(pGpioHandle->Port, pGpioHandle->Pin, pGpioHandle->Config.RtFtDetect);
    }
    
    return GPIO_INIT_OK;
}

/*************************************\
  fn: @GPIO_Deinit
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin with the reset settings
  
  note: calling this func only resets the parts of the gpio registers responsible
        for this pin, doesnt affect any other gpio pins
  
\**************************************/
void GPIO_Deinit(GPIO_Handle* pGpioHandle)
{
    *GPIO_REGS[pGpioHandle->Port][TRISX] |= (1U << pGpioHandle->Pin);
    
    *GPIO_REGS[pGpioHandle->Port][ANSELX] |= (1U << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][WPUX] &= ~(1U << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][ODCONX] &= ~(1U << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][SLRCONX] |= (1U << pGpioHandle->Pin);

    *GPIO_REGS[pGpioHandle->Port][INLVLX] |= (1U << pGpioHandle->Pin);
    
    IOC_SetPinTriggers(pGpioHandle->Port, pGpioHandle->Pin, GPIO_RTFTDETECT_NONE);
}

/*************************************\
  fn: @GPIO_PortReset
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: resets the whole gpio port, every gpio pin on the peripheral will be
        reset using the RCC AHB1RSTR
  
  note: unlike GPIO_Deinit() this affects every pin on the port
  
\**************************************/
void GPIO_DeinitPort(GPIO_Handle* pGpioHandle)
{
    *GPIO_REGS[pGpioHandle->Port][TRISX] = TRISX_RST;

    *GPIO_REGS[pGpioHandle->Port][ANSELX] = ANSELX_RST;

    *GPIO_REGS[pGpioHandle->Port][WPUX] = WPUX_RST;

    *GPIO_REGS[pGpioHandle->Port][ODCONX] = ODCONX_RST;

    *GPIO_REGS[pGpioHandle->Port][SLRCONX] = SLRCONX_RST;

    *GPIO_REGS[pGpioHandle->Port][INLVLX] = INLVLX_RST;
    
    for (u8 i = 0; i < 8; i++)
        IOC_SetPinTriggers(pGpioHandle->Port, i, GPIO_RTFTDETECT_NONE);
}

/*************************************\
  fn: @GPIO_WriteTogglePin
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: toggles the electrical pin state between high and low
  
  note: 
  
\**************************************/
void GPIO_WriteTogglePin(GPIO_Handle* pGpioHandle)
{
    *GPIO_REGS[pGpioHandle->Port][LATX] ^= (1U << pGpioHandle->Pin);
}

/*************************************\
  fn: @GPIO_WritePin
  
  param1 GPIO_Handle*: the gpio handle
  param2 u8: high or low on the pin
  
  return:
  
  desc: sets the electrical pin state to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePin(GPIO_Handle* pGpioHandle, u8 isEnabled)
{
    *GPIO_REGS[pGpioHandle->Port][LATX] &= ~(1U << pGpioHandle->Pin);
    *GPIO_REGS[pGpioHandle->Port][LATX] |= ((isEnabled & 1) << pGpioHandle->Pin);
}

/*************************************\
  fn: @GPIO_WritePort
  
  param1 GPIO_Handle*: the gpio handle
  param2 u16: the gpio pin output values
  
  return:
  
  desc: sets the electrical pin states of every pin on the peripheral to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePort(GPIO_Handle* pGpioHandle, u8 outputReg)
{
    *GPIO_REGS[pGpioHandle->Port][LATX] = outputReg;
}

/*************************************\
  fn: @GPIO_ReadPin
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: first bit is either 1 or 0 depending on electrical pin state
  
  desc: reads the gpio electrical pin state
  
  note: 
  
\**************************************/
u8 GPIO_ReadPin(GPIO_Handle* pGpioHandle)
{
    return ((*GPIO_REGS[pGpioHandle->Port][PORTX] & (1U << pGpioHandle->Pin)) >> pGpioHandle->Pin);
}

/*************************************\
  fn: @GPIO_ReadPort
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: returns a bitmap of the electrical states of the gpio pins
  
  desc: reads and returns the pin state of every pin on the gpio peripheral
  
  note: 
  
\**************************************/
u8 GPIO_ReadPort(GPIO_Handle* pGpioHandle)
{
    return *GPIO_REGS[pGpioHandle->Port][PORTX];
}

/*************************************\
  fn: @GPIO_IRQHandled
  
  param1 u8: the first pin number the interrupt could have been called from
  param2 u8: the last pin number the interrupt could have been called from
  
  return: 
  
  desc: clears IOC flag reg status bits which could have caused the interrupt, for every status clear the
        GPIO_AppEventCallback() func gets called with the pin number as an arg
  
  note: should be called at the end of an IRQ Handler func that gets called when an interrupt occurs
  
\**************************************/
void GPIO_IrqHandled()
{
    if (PIE0bits.INT0IE && PIR0bits.INT0IF)
    {
        GPIO_AppEvCb(INT0PPS >> 3, INT0PPS & 0x7);
        PIR0bits.INT0IF = 0;
    }
    if (PIE0bits.INT1IE && PIR0bits.INT1IF)
    {
        GPIO_AppEvCb(INT1PPS >> 3, INT1PPS & 0x7);
        PIR0bits.INT1IF = 0;
    }
    if (PIE0bits.INT2IE && PIR0bits.INT2IF)
    {
        GPIO_AppEvCb(INT2PPS >> 3, INT2PPS & 0x7);
        PIR0bits.INT2IF = 0;
    }
    
    if (PIE3bits.IOCIE && PIR3bits.IOCIF)
        for (u8 port = GPIO_PORTA; port <= GPIO_PORTC; port++)
            for (u8 pin = 0; pin < 8; pin++)
                if (IOC_GetPinTriggerStatus(port, pin))
                {
                    GPIO_AppEvCb(port, pin);
                    IOC_ClearPinTriggerStatus(port, pin);
                }
}

/*************************************\
  fn: @GPIO_AppEvCb
  
  param1 u8: the pin number where an interrupt was called
  param2 u8: the port number where an interrupt was called
  
  return: 
  
  desc: will be called everytime an interrupt status flag gets cleared in IOC flag reg from GPIO_IRQHandled(),
        and only from GPIO_IrqHandled()
  
  note: weak implementation, please implement your own
  
\**************************************/
WEAK void GPIO_AppEvCb(u8 port, u8 pin)
{

}