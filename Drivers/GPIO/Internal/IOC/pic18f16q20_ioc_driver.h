#ifndef PIC18F16Q20_IOC_DRIVER_H_
#define PIC18F16Q20_IOC_DRIVER_H_

#include "../../../Internal/types.h"

#define IOC_PORTA                   0x00
#define IOC_PORTB                   0x01
#define IOC_PORTC                   0x02

#define IOC_TRIGGER_NONE            0b00
#define IOC_TRIGGER_RISING          0b01
#define IOC_TRIGGER_FALLING         0b10
#define IOC_TRIGGER_BOTH            0b11

void IOC_SetPinTriggers(u8 port, u8 pin, u8 trigger);

#endif