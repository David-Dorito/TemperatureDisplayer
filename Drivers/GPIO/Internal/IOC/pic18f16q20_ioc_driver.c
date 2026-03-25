#ifdef __XC8
    #include <xc.h>
#else
    #include "pic18f16q20.h"
#endif
#include "pic18f16q20_ioc_driver.h"

void IOC_SetPinTriggers(u8 port, u8 pin, u8 trigger)
{
    switch (port)
    {
        case IOC_PORTA:
            IOCAP &= ~(1U << pin);
            IOCAP |= ((trigger & IOC_TRIGGER_RISING) << pin);
            IOCAN &= ~(1U << pin);
            IOCAN |= ((trigger & IOC_TRIGGER_FALLING) << pin);
            break;
        case IOC_PORTB:
            IOCBP &= ~(1U << pin);
            IOCBP |= ((trigger & IOC_TRIGGER_RISING) << pin);
            IOCBN &= ~(1U << pin);
            IOCBN |= ((trigger & IOC_TRIGGER_FALLING) << pin);
            break;
        case IOC_PORTC:
            IOCCP &= ~(1U << pin);
            IOCCP |= ((trigger & IOC_TRIGGER_RISING) << pin);
            IOCCN &= ~(1U << pin);
            IOCCN |= ((trigger & IOC_TRIGGER_FALLING) << pin);
            break;
    }
}

u8 IOC_GetPinTriggerStatus(u8 port, u8 pin)
{
    switch (port)
    {
        case IOC_PORTA:
            return ((IOCAF & (1U << pin)) >> pin);
        case IOC_PORTB:
            return ((IOCBF & (1U << pin)) >> pin);
        case IOC_PORTC:
            return ((IOCCF & (1U << pin)) >> pin);
    }
    return 0xFF;
}

void IOC_ClearPinTriggerStatus(u8 port, u8 pin)
{
    switch (port)
    {
        case IOC_PORTA:
            IOCAF &= ~(1U << pin);
            break;
        case IOC_PORTB:
            IOCBF &= ~(1U << pin);
            break;
        case IOC_PORTC:
            IOCCF &= ~(1U << pin);
            break;
    }
}