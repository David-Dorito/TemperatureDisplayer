#ifndef PIC18F16Q20_GPIO_DRIVER_H_
#define PIC18F16Q20_GPIO_DRIVER_H_

#include "../Internal/types.h"

//Port
#define GPIO_PORTA                      0
#define GPIO_PORTB                      1
#define GPIO_PORTC                      2

//Direction
#define GPIO_DIRECTION_OUTPUT           0
#define GPIO_DIRECTION_INPUT            1

//OpType
#define GPIO_OPTYPE_PP                  0
#define GPIO_OPTYPE_OD                  1

//OpSpeed
#define GPIO_OPSPEED_MAX                0
#define GPIO_OPSPEED_LIMITED            1

//InMode
#define GPIO_INMODE_TTL                 0
#define GPIO_INMODE_ST                  1

//RtFtDetect
#define GPIO_RTFTDETECT_NONE            0b00
#define GPIO_RTFTDETECT_FT              0b01
#define GPIO_RTFTDETECT_RT              0b10
#define GPIO_RTFTDETECT_RTFT            0b11

//IntSrc
#define GPIO_INTSRC_IOC                 0
#define GPIO_INTSRC_INT0                1
#define GPIO_INTSRC_INT1                2
#define GPIO_INTSRC_INT2                3

//AltFuncNum
#define GPIO_OPFUNC_LATXY               0x00
#define GPIO_OPFUNC_CLKR                0x01
#define GPIO_OPFUNC_TMR0                0x02
#define GPIO_OPFUNC_TU16A               0x03
#define GPIO_OPFUNC_TU16B               0x04
#define GPIO_OPFUNC_CCP1                0x05
#define GPIO_OPFUNC_CCP2                0x06
#define GPIO_OPFUNC_PWM1S1P1_OUT        0x07
#define GPIO_OPFUNC_PWM1S1P2_OUT        0x08
#define GPIO_OPFUNC_PWM2S1P1_OUT        0x09
#define GPIO_OPFUNC_PWM2S1P2_OUT        0x0A
#define GPIO_OPFUNC_CWG1A               0x0B
#define GPIO_OPFUNC_CWG1B               0x0C
#define GPIO_OPFUNC_CWG1C               0x0D
#define GPIO_OPFUNC_CWG1D               0x0E
#define GPIO_OPFUNC_CLC1OUT             0x0F
#define GPIO_OPFUNC_CLC2OUT             0x10
#define GPIO_OPFUNC_CLC3OUT             0x11
#define GPIO_OPFUNC_CLC4OUT             0x12
#define GPIO_OPFUNC_UART1TX             0x13
#define GPIO_OPFUNC_UART1RTS            0x14
#define GPIO_OPFUNC_UART1TXDE           0x15
#define GPIO_OPFUNC_UART2TX             0x16
#define GPIO_OPFUNC_UART2RTS            0x17
#define GPIO_OPFUNC_UART2TXDE           0x18
#define GPIO_OPFUNC_SPI1SCK             0x19
#define GPIO_OPFUNC_SPI1SDO             0x1A
#define GPIO_OPFUNC_SPI1SS              0x1B
#define GPIO_OPFUNC_I2C1SCL             0x1C
#define GPIO_OPFUNC_I2C1SDA             0x1D
#define GPIO_OPFUNC_ADGRDA              0x1E
#define GPIO_OPFUNC_ADGRDB              0x1F

#define GPIO_INFUNC_INT0                0x00
#define GPIO_INFUNC_INT1                0x01
#define GPIO_INFUNC_INT2                0x02
#define GPIO_INFUNC_T0CKI               0x03
#define GPIO_INFUNC_T1CKI               0x04
#define GPIO_INFUNC_T1G                 0x05
#define GPIO_INFUNC_T2IN                0x06
#define GPIO_INFUNC_T4IN                0x07
#define GPIO_INFUNC_TUIN1               0x08
#define GPIO_INFUNC_TUIN2               0x09
#define GPIO_INFUNC_CCP1                0x0A
#define GPIO_INFUNC_CCP2                0x0B
#define GPIO_INFUNC_PWMIN0              0x0C
#define GPIO_INFUNC_PWMIN1              0x0D
#define GPIO_INFUNC_PWM1ERS             0x0E
#define GPIO_INFUNC_PWM2ERS             0x0F
#define GPIO_INFUNC_CWG1                0x10
#define GPIO_INFUNC_CLCIN0              0x11
#define GPIO_INFUNC_CLCIN1              0x12
#define GPIO_INFUNC_CLCIN2              0x13
#define GPIO_INFUNC_CLCIN3              0x14
#define GPIO_INFUNC_U2CTS               0x15
#define GPIO_INFUNC_U2RX                0x16
#define GPIO_INFUNC_U1CTS               0x17
#define GPIO_INFUNC_U1RX                0x18
#define GPIO_INFUNC_SPI1SCK             0x19
#define GPIO_INFUNC_SPI1SDI             0x1A
#define GPIO_INFUNC_SPI1SS              0x1B
#define GPIO_INFUNC_I2C1SCL             0x1C
#define GPIO_INFUNC_I2C1SDA             0x1D
#define GPIO_INFUNC_ADACT               0x1E

typedef struct {
    u8 Direction: 1;        // direction of the pin, input or output
    u8 OpType: 1;           // output type, push pull or open drain
    u8 OpSpeed: 1;          // output speed, limited or max
    u8 InMode: 1;           // input mode
    u8 InAnalogEn: 1;       // input analog enable
    u8 PullupEn: 1;         // pull-up enable (there is no internal pull-down resistor on this mcu)
    u8 RtFtDetect: 2;       // rise/fall detect
    u8 IntSrc: 2;           // the interrupt which the pin should generate on rise/fall, only applicable if RtFtDetect is not NONE
    u8 AltFuncEn: 1;        // enable or disable alternate functionalities for this pin
    u8 AltFuncNum: 5;       // alternate function number, can allow a pin to be SPI SCK using PPS for example
} GPIO_Config;

typedef struct {
    u8 Pin: 3;              // the pin number on the port, from 0 to 7
    u8 Port: 2;             // the port, from 0 to 2, each number corresponds to a port (GPIO_PORTA, GPIO_PORTB, GPIO_PORTC macros)
    GPIO_Config Config;     // the config struct from above, contains all the settings for the pin
} GPIO_Handle;

#define GPIO_INIT_OK                    0
#define GPIO_INIT_INVALIDTRIGGERS       1
/*************************************\
  fn: @GPIO_Init
  
  param1 GPIO_Handle*: the gpio handle
  
  return u8: error status return, 0 means OK
  
  desc: configures the gpio pin
  
  note: 
  
\**************************************/
u8 GPIO_Init(GPIO_Handle* pGpioHandle);

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
  
  param1 funcptr: callback function ptr, will get called for every interrupt status that got cleared
  
  return: 
  
  desc: calls the callback with port and pin as params for each set flag bit and clears the flags afterwards
  
  note: should be called at the end of every GPIO ISR
  
\**************************************/
void GPIO_IrqHandled(void (*GPIO_AppEvCb)(u8 port, u8 pin));

#endif