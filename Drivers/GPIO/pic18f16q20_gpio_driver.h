#ifndef PIC18F16Q20_GPIO_DRIVER_H_
#define PIC18F16Q20_GPIO_DRIVER_H_

#include "../Internal/types.h"

//Port
#define GPIO_PORTA                      0x00
#define GPIO_PORTB                      0x01
#define GPIO_PORTC                      0x02

//Direction
#define GPIO_DIRECTION_OUTPUT           0b0
#define GPIO_DIRECTION_INPUT            0b1

//OpType
#define GPIO_OPTYPE_PP                  0b0
#define GPIO_OPTYPE_OD                  0b1

//OpSpeed
#define GPIO_OPSPEED_LOW                0b00
#define GPIO_OPSPEED_MAX                0b01

//InMode
#define GPIO_INMODE_ST                  0b0
#define GPIO_INMODE_TTL                 0b1

//RtFtDetect
#define GPIO_RTFTDETECT_NONE            0b00
#define GPIO_RTFTDETECT_FT              0b01
#define GPIO_RTFTDETECT_RT              0b10
#define GPIO_RTFTDETECT_RTFT            0b11

//AltFuncNum
#define GPIO_OPFUNC_LATXY               PPS_OPSEL_LATXY
#define GPIO_OPFUNC_CLKR                PPS_OPSEL_CLKR
#define GPIO_OPFUNC_TMR0                PPS_OPSEL_TMR0
#define GPIO_OPFUNC_TU16A               PPS_OPSEL_TU16A
#define GPIO_OPFUNC_TU16B               PPS_OPSEL_TU16B
#define GPIO_OPFUNC_CCP1                PPS_OPSEL_CCP1
#define GPIO_OPFUNC_CCP2                PPS_OPSEL_CCP2
#define GPIO_OPFUNC_PWM1S1P1_OUT        PPS_OPSEL_PWM1S1P1_OUT
#define GPIO_OPFUNC_PWM1S1P2_OUT        PPS_OPSEL_PWM1S1P2_OUT
#define GPIO_OPFUNC_PWM2S1P1_OUT        PPS_OPSEL_PWM2S1P1_OUT
#define GPIO_OPFUNC_PWM2S1P2_OUT        PPS_OPSEL_PWM2S1P2_OUT
#define GPIO_OPFUNC_CWG1A               PPS_OPSEL_CWG1A
#define GPIO_OPFUNC_CWG1B               PPS_OPSEL_CWG1B
#define GPIO_OPFUNC_CWG1C               PPS_OPSEL_CWG1C
#define GPIO_OPFUNC_CWG1D               PPS_OPSEL_CWG1D
#define GPIO_OPFUNC_CLC1OUT             PPS_OPSEL_CLC1OUT
#define GPIO_OPFUNC_CLC2OUT             PPS_OPSEL_CLC2OUT
#define GPIO_OPFUNC_CLC3OUT             PPS_OPSEL_CLC3OUT
#define GPIO_OPFUNC_CLC4OUT             PPS_OPSEL_CLC4OUT
#define GPIO_OPFUNC_UART1TX             PPS_OPSEL_UART1TX
#define GPIO_OPFUNC_UART1RTS            PPS_OPSEL_UART1RTS
#define GPIO_OPFUNC_UART1TXDE           PPS_OPSEL_UART1TXDE
#define GPIO_OPFUNC_UART2TX             PPS_OPSEL_UART2TX
#define GPIO_OPFUNC_UART2RTS            PPS_OPSEL_UART2RTS
#define GPIO_OPFUNC_UART2TXDE           PPS_OPSEL_UART2TXDE
#define GPIO_OPFUNC_SPI1SCK             PPS_OPSEL_SPI1SCK
#define GPIO_OPFUNC_SPI1SDO             PPS_OPSEL_SPI1SDO
#define GPIO_OPFUNC_SPI1SS              PPS_OPSEL_SPI1SS
#define GPIO_OPFUNC_I2C1SCL             PPS_OPSEL_I2C1SCL
#define GPIO_OPFUNC_I2C1SDA             PPS_OPSEL_I2C1SDA
#define GPIO_OPFUNC_ADGRDA              PPS_OPSEL_ADGRDA
#define GPIO_OPFUNC_ADGRDB              PPS_OPSEL_ADGRDB

#define GPIO_INFUNC_INT0                PPS_INSEL_INT0
#define GPIO_INFUNC_INT1                PPS_INSEL_INT1
#define GPIO_INFUNC_INT2                PPS_INSEL_INT2
#define GPIO_INFUNC_T0CKI               PPS_INSEL_T0CKI
#define GPIO_INFUNC_T1CKI               PPS_INSEL_T1CKI
#define GPIO_INFUNC_T1G                 PPS_INSEL_T1G
#define GPIO_INFUNC_T2IN                PPS_INSEL_T2IN
#define GPIO_INFUNC_T4IN                PPS_INSEL_T4IN
#define GPIO_INFUNC_TUIN1               PPS_INSEL_TUIN1
#define GPIO_INFUNC_TUIN2               PPS_INSEL_TUIN2
#define GPIO_INFUNC_CCP1                PPS_INSEL_CCP1
#define GPIO_INFUNC_CCP2                PPS_INSEL_CCP2
#define GPIO_INFUNC_PWMIN0              PPS_INSEL_PWMIN0
#define GPIO_INFUNC_PWMIN1              PPS_INSEL_PWMIN1
#define GPIO_INFUNC_PWM1ERS             PPS_INSEL_PWM1ERS
#define GPIO_INFUNC_PWM2ERS             PPS_INSEL_PWM2ERS
#define GPIO_INFUNC_CWG1                PPS_INSEL_CWG1
#define GPIO_INFUNC_CLCIN0              PPS_INSEL_CLCIN0
#define GPIO_INFUNC_CLCIN1              PPS_INSEL_CLCIN1
#define GPIO_INFUNC_CLCIN2              PPS_INSEL_CLCIN2
#define GPIO_INFUNC_CLCIN3              PPS_INSEL_CLCIN3
#define GPIO_INFUNC_UART2CTS            PPS_INSEL_UART2CTS
#define GPIO_INFUNC_UART2RX             PPS_INSEL_UART2RX
#define GPIO_INFUNC_UART1CTS            PPS_INSEL_UART1CTS
#define GPIO_INFUNC_UART1RX             PPS_INSEL_UART1RX
#define GPIO_INFUNC_SPI1SCK             PPS_INSEL_SPI1SCK
#define GPIO_INFUNC_SPI1SDI             PPS_INSEL_SPI1SDI
#define GPIO_INFUNC_SPI1SS              PPS_INSEL_SPI1SS
#define GPIO_INFUNC_I2C1SCL             PPS_INSEL_I2C1SCL
#define GPIO_INFUNC_I2C1SDA             PPS_INSEL_I2C1SDA
#define GPIO_INFUNC_ADACT               PPS_INSEL_ADACT

typedef struct {
    u8 Direction: 1;
    u8 OpType: 1;
    u8 OpSpeed: 1;
    u8 InMode: 1;
    u8 InAnalogEn: 1;
    u8 PullupEn: 1;
    u8 RtFtDetect: 2;
    u8 AltFuncNum: 5;
} GPIO_Config;

typedef struct {
    u8 Pin: 3;
    u8 Port: 2;
    GPIO_Config Config;
} GPIO_Handle;

/*************************************\
  fn: @GPIO_Init
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin
  
  note: 
  
\**************************************/
void GPIO_Init(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_Deinit
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: configures the gpio pin with the reset settings
  
  note: calling this func only resets the parts of the gpio registers responsible
        for this pin, doesnt affect any other gpio pins
  
\**************************************/
void GPIO_Deinit(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_PortReset
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: resets the whole gpio port, every gpio pin on the peripheral will be
        reset using the RCC AHB1RSTR
  
  note: unlike GPIO_Deinit() this affects every pin on the port
  
\**************************************/
void GPIO_DeinitPort(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_WriteTogglePin
  
  param1 GPIO_Handle*: the gpio handle
  
  return:
  
  desc: toggles the electrical pin state between high and low
  
  note: 
  
\**************************************/
void GPIO_WriteTogglePin(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_WritePin
  
  param1 GPIO_Handle*: the gpio handle
  param2 u8: high or low on the pin
  
  return:
  
  desc: sets the electrical pin state to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePin(GPIO_Handle* pGpioHandle, u8 isEnabled);

/*************************************\
  fn: @GPIO_WritePort
  
  param1 GPIO_Handle*: the gpio handle
  param2 u16: the gpio pin output values
  
  return:
  
  desc: sets the electrical pin states of every pin on the peripheral to high or low
  
  note: 
  
\**************************************/
void GPIO_WritePort(GPIO_Handle* pGpioHandle, u8 outputReg);

/*************************************\
  fn: @GPIO_ReadPin
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: first bit is either 1 or 0 depending on electrical pin state
  
  desc: reads the gpio electrical pin state
  
  note: 
  
\**************************************/
u8 GPIO_ReadPin(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_ReadPort
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: returns a bitmap of the electrical states of the gpio pins
  
  desc: reads and returns the pin state of every pin on the gpio peripheral
  
  note: 
  
\**************************************/
u8 GPIO_ReadPort(GPIO_Handle* pGpioHandle);

/*************************************\
  fn: @GPIO_IRQHandled
  
  param1 u8: the first pin number the interrupt could have been called from
  param2 u8: the last pin number the interrupt could have been called from
  
  return: 
  
  desc: clears IOC flag reg status bits which could have caused the interrupt, for every status clear the
        GPIO_AppEventCallback() func gets called with the pin number as an arg
  
  note: should be called at the end of an IRQ Handler func that gets called when an interrupt occurs
  
\**************************************/
void GPIO_IRQHandled(u8 firstPinNum, u8 lastPinNum);

/*************************************\
  fn: @GPIO_AppEventCallback
  
  param1 u8: the pin number where an interrupt was called
  
  return: 
  
  desc: will be called everytime an interrupt status flag gets cleared in IOC flag reg from GPIO_IRQHandled(),
        and only from GPIO_IRQHandled()
  
  note: weak implementation, please implement your own
  
\**************************************/
WEAK void GPIO_AppEventCallback(u8 pinNumber);

#endif