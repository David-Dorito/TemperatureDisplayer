#ifndef PIC18F16Q20_PPS_DRIVER_H_
#define PIC18F16Q20_PPS_DRIVER_H_

#include "../../../Internal/types.h"

#define PPS_PORTA                   0x00
#define PPS_PORTB                   0x01
#define PPS_PORTC                   0x02

#define PPS_OPSEL_LATXY             0x00
#define PPS_OPSEL_CLKR              0x01
#define PPS_OPSEL_TMR0              0x02
#define PPS_OPSEL_TU16A             0x03
#define PPS_OPSEL_TU16B             0x04
#define PPS_OPSEL_CCP1              0x05
#define PPS_OPSEL_CCP2              0x06
#define PPS_OPSEL_PWM1S1P1_OUT      0x07
#define PPS_OPSEL_PWM1S1P2_OUT      0x08
#define PPS_OPSEL_PWM2S1P1_OUT      0x09
#define PPS_OPSEL_PWM2S1P2_OUT      0x0A
#define PPS_OPSEL_CWG1A             0x0B
#define PPS_OPSEL_CWG1B             0x0C
#define PPS_OPSEL_CWG1C             0x0D
#define PPS_OPSEL_CWG1D             0x0E
#define PPS_OPSEL_CLC1OUT           0x0F
#define PPS_OPSEL_CLC2OUT           0x10
#define PPS_OPSEL_CLC3OUT           0x11
#define PPS_OPSEL_CLC4OUT           0x12
#define PPS_OPSEL_UART1TX           0x13
#define PPS_OPSEL_UART1RTS          0x14
#define PPS_OPSEL_UART1TXDE         0x15
#define PPS_OPSEL_UART2TX           0x16
#define PPS_OPSEL_UART2RTS          0x17
#define PPS_OPSEL_UART2TXDE         0x18
#define PPS_OPSEL_SPI1SCK           0x19
#define PPS_OPSEL_SPI1SDO           0x1A
#define PPS_OPSEL_SPI1SS            0x1B
#define PPS_OPSEL_I2C1SCL           0x1C
#define PPS_OPSEL_I2C1SDA           0x1D
#define PPS_OPSEL_ADGRDA            0x1E
#define PPS_OPSEL_ADGRDB            0x1F

#define PPS_INSEL_INT0              0x00
#define PPS_INSEL_INT1              0x01
#define PPS_INSEL_INT2              0x02
#define PPS_INSEL_T0CKI             0x03
#define PPS_INSEL_T1CKI             0x04
#define PPS_INSEL_T1G               0x05
#define PPS_INSEL_T2IN              0x06
#define PPS_INSEL_T4IN              0x07
#define PPS_INSEL_TUIN1             0x08
#define PPS_INSEL_TUIN2             0x09
#define PPS_INSEL_CCP1              0x0A
#define PPS_INSEL_CCP2              0x0B
#define PPS_INSEL_PWMIN0            0x0C
#define PPS_INSEL_PWMIN1            0x0D
#define PPS_INSEL_PWM1ERS           0x0E
#define PPS_INSEL_PWM2ERS           0x0F
#define PPS_INSEL_CWG1              0x10
#define PPS_INSEL_CLCIN0            0x11
#define PPS_INSEL_CLCIN1            0x12
#define PPS_INSEL_CLCIN2            0x13
#define PPS_INSEL_CLCIN3            0x14
#define PPS_INSEL_UART2CTS          0x15
#define PPS_INSEL_UART2RX           0x16
#define PPS_INSEL_UART1CTS          0x17
#define PPS_INSEL_UART1RX           0x18
#define PPS_INSEL_SPI1SCK           0x19
#define PPS_INSEL_SPI1SDI           0x1A
#define PPS_INSEL_SPI1SS            0x1B
#define PPS_INSEL_I2C1SCL           0x1C
#define PPS_INSEL_I2C1SDA           0x1D
#define PPS_INSEL_ADACT             0x1E

void PPS_SetOutput(u8 port, u8 pin, u8 opSelect);
void PPS_SetInput(u8 port, u8 pin, u8 inSelect);
void PPS_SetLock(u8 isLocked);

#endif