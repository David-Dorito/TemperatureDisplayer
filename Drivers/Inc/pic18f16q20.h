#ifndef PIC18F16Q20_H_
#define PIC18F16Q20_H_

#include <stdint.h>

#define HIGH                                1
#define LOW                                 0
#define TRUE                                1
#define FALSE                               0
#define ENABLE                              1
#define DISABLE                             0

#define WEAK                                __attribute__((weak))

typedef int32_t                             i32;
typedef int16_t                             i16;
typedef int8_t                              i8;
typedef uint32_t                            u32;
typedef uint16_t                            u16;
typedef uint8_t                             u8;

/******************************** PROCESSOR SPECIFIC DETAILS ********************************/

#define VIC_BASEADDR                        0x376

typedef struct {
    volatile u8 SHADCON;
    volatile u8 RESERVED00[233];
    volatile u8 IVTLOCK;
    volatile u8 INTCON[2];
    volatile u16 IVTAD;
    volatile u8 RESERVED01;
    volatile u16 IVTBASE;
    volatile u8 RESERVED02;
    volatile u8 PIR[10];
    volatile u8 PIE[10];
    volatile u8 IPR[10];
} VIC_RegDef;

#define VIC                                 ((VIC_RegDef*)VIC_BASEADDR)

/*********************************************************************************************/

#define OSC_BASEADDR                        0x7AU

#define GPIO_BASEADDR                       0x030FU

#define UART1_BASEADDR                      0x01AFU
#define UART2_BASEADDR                      0x01C3U

#define SPI1_BASEADDR                       0x01D7U

#define I2C1_BASEADDR                       0x01E4U

typedef struct {
    volatile u8 RB5FEAT;
    volatile u8 RB6FEAT;
    volatile u8 RESERVED00;
    volatile u8 RC0FEAT;
    volatile u8 RC1FEAT;
    volatile u8 RESERVED01;
    volatile u8 RC4FEAT;
    volatile u8 RC5FEAT;
    volatile u8 RESERVED02[255];
    volatile u8 ANSELA;
    volatile u8 WPUA;
    volatile u8 ODCONA;
    volatile u8 SLRCONA;
    volatile u8 INVLA;
    volatile u8 RESERVED03[5];
    volatile u8 ANSELB;
    volatile u8 WPUB;
    volatile u8 ODCONB;
    volatile u8 SLRCONB;
    volatile u8 INLVLB;
    volatile u8 RESERVED04[5];
    volatile u8 ANSELC;
    volatile u8 WPUC;
    volatile u8 ODCONC;
    volatile u8 SLRCONC;
    volatile u8 INLVLC;
    volatile u8 RESERVED05[88];
    volatile u8 PORTA;
    volatile u8 PORTB;
    volatile u8 PORTC;
    volatile u8 RESERVED06[3];
    volatile u8 TRISA;
    volatile u8 TRISB;
    volatile u8 TRISC;
    volatile u8 RESERVED07[3];
    volatile u8 LATA;
    volatile u8 LATB;
    volatile u8 LATC;
} GPIO_RegDef;

#define GPIO                                ((GPIO_RegDef*)GPIO_BASEADDR)

typedef struct {
    volatile u8 RXB;
    volatile u8 RXCHK;
    volatile u8 TXB;
    volatile u8 TXCHK;
    volatile u8 P1;
    volatile u8 P2;
    volatile u8 P3;
    volatile u8 CON0;
    volatile u8 CON1;
    volatile u8 CON2;
    volatile u8 BRG;
    volatile u8 FIFO;
    volatile u8 RESERVED00;
    volatile u8 UIR;
    volatile u8 ERRIR;
    volatile u8 ERRIE;
} UART_RegDef;

#define UART1                               ((UART_RegDef*)UART1_BASEADDR)
#define UART2                               ((UART_RegDef*)UART2_BASEADDR)

typedef struct {
    volatile u8 RXB;
    volatile u8 TXB;
    volatile u8 TCNT;
    volatile u8 CON0;
    volatile u8 CON1;
    volatile u8 CON2;
    volatile u8 STATUS;
    volatile u8 TWIDTH;
    volatile u8 BAUD;
    volatile u8 INTF;
    volatile u8 INTE;
    volatile u8 CLK;
} SPI_RegDef;

#define SPI1                                ((SPI_RegDef*)SPI1_BASEADDR)

typedef struct {
    volatile u8 STAT0;
    volatile u8 STAT1;
    volatile u8 CON0;
    volatile u8 CON1;
    volatile u8 CON2;
    volatile u8 CON3;
    volatile u8 PIR;
    volatile u8 PIE;
    volatile u8 ERR;
    volatile u8 CNT;
    volatile u8 RXB;
    volatile u8 TXB;
    volatile u8 ADB0;
    volatile u8 ADB1;
    volatile u8 ADR0;
    volatile u8 ADR1;
    volatile u8 ADR2;
    volatile u8 ADR3;
    volatile u8 BTO;
    volatile u8 BAUD;
    volatile u8 CLK;
    volatile u8 BTOC;
} I2C_RegDef;

#define I2C1                                ((I2C_RegDef*)I2C1_BASEADDR)

typedef struct {
    volatile u8 OSCCON1;
    volatile u8 OSCCON2;
    volatile u8 OSCCON3;
    volatile u8 OSCSTAT;
    volatile u8 OSCEN;
    volatile u8 OSCTUNE;
    volatile u8 OSCFREQ;
    volatile u8 ACTCON;
    volatile u8 FSCMCON;
} OSC_RegDef;

#define OSC                                 ((OSC_RegDef*)OSC_BASEADDR)

#endif /* STM32F401XX_H_ */