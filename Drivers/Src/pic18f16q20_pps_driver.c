#include "../Inc/pic18f16q20_pps_driver.h"
#include "../Inc/pic18f16q20_errata.h"

#define XXXPPS_PORT             0x03

inline void PPS_SetOutput(u8 port, u8 pin, u8 opSelect)
{
    u8* pPPSReg = GetOutputReg(port, pin);
    if (pPPSReg != NULL)
        *pPPSReg = opSelect;
}

inline void PPS_SetInput(u8 port, u8 pin, u8 inSelect)
{
    u8* pPPSReg = GetInputReg(inSelect);
    if (pPPSReg != NULL)
        *pPPSReg = ((port << XXXPPS_PORT) | pin);
}

void PPS_Lock()
{

}

void PPS_Unlock()
{
    
}

static u8* GetOutputReg(u8 port, u8 pin)
{
    switch (port)
    {
        case PPS_PORTA:
            switch (pin)
            {
                case 0: return &RA0PPS;
                case 1: return &RA1PPS;
                case 2: return &RA2PPS;
                case 4: return &RA4PPS;
                case 5: return &RA5PPS;
                default: return NULL;
            }
            break;
        case PPS_PORTB:
            switch (pin)
            {
                case 5: return &RB5PPS;
                case 6: return &RB6PPS;
                case 7: return &RB7PPS;
                default: return NULL;
            }
            break;
        case PPS_PORTC:
            switch (pin)
            {
                case 0: return &RC0PPS;
                case 1: return &RC1PPS;
                case 3: return &RC3PPS;
                case 4: return &RC4PPS;
                case 5: return &RC5PPS;
                case 6: return &RC6PPS;
                case 7: return &RC7PPS;
                default: return NULL;
            }
            break;
        default: return NULL;
    }
}

static u8* GetInputReg(u8 inSelect)
{
    switch (inSelect)
    {
        case PPS_INSEL_INT0: return &INT0PPS;
        case PPS_INSEL_INT1: return &INT1PPS;
        case PPS_INSEL_INT2: return &INT2PPS;
        case PPS_INSEL_T0CKI: return &T0CKIPPS;
        case PPS_INSEL_T1CKI: return &T1CKIPPS;
        case PPS_INSEL_T1G: return &T1GPPS;
        case PPS_INSEL_T2IN: return &T2INPPS;
        case PPS_INSEL_T4IN: return &T4INPPS;
        case PPS_INSEL_TUIN1: return &TUIN1PPS;
        case PPS_INSEL_TUIN2: return &TUIN2PPS;
        case PPS_INSEL_CCP1: return &CCP1PPS;
        case PPS_INSEL_CCP2: return &CCP2PPS;
        case PPS_INSEL_PWMIN0: return &PWMIN0PPS;
        case PPS_INSEL_PWMIN1: return &PWMIN1PPS;
        case PPS_INSEL_PWM1ERS: return &PWM1ERSPPS;
        case PPS_INSEL_PWM2ERS: return &PWM2ERSPPS;
        case PPS_INSEL_CWG1: return &CWG1PPS;
        case PPS_INSEL_CLCIN0: return &CLCIN0PPS;
        case PPS_INSEL_CLCIN1: return &CLCIN1PPS;
        case PPS_INSEL_CLCIN2: return &CLCIN2PPS;
        case PPS_INSEL_CLCIN3: return &CLCIN3PPS;
        case PPS_INSEL_UART2CTS: return &U2CTSPPS;
        case PPS_INSEL_UART2RX: return &U2RXPPS;
        case PPS_INSEL_UART1CTS: return &U1CTSPPS;
        case PPS_INSEL_UART1RX: return &U1RXPPS;
        case PPS_INSEL_SPI1SCK: return &SPI1SCKPPS;
        case PPS_INSEL_SPI1SDI: return &SPI1SDIPPS;
        case PPS_INSEL_SPI1SS: return &SPI1SSPPS;
        case PPS_INSEL_I2C1SCL: return &I2C1SCLPPS;
        case PPS_INSEL_I2C1SDA: return &I2C1SDAPPS;
        case PPS_INSEL_ADACT: return &ADACTPPS;
        default: return NULL;
    }
}