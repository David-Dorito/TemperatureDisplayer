#include <pic18f16q20.h>
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