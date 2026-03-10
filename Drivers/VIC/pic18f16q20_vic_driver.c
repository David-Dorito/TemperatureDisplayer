#include "pic18f16q20_vic_driver.h"
#include <pic18f16q20.h>

static volatile u8* const IPR[] = {
    &IPR0, &IPR1, &IPR2, &IPR3, &IPR4, &IPR5, &IPR6, &IPR7, &IPR8, &IPR9
};

static volatile u8* const PIE[] = {
    &PIE0, &PIE1, &PIE2, &PIE3, &PIE4, &PIE5, &PIE6, &PIE7, &PIE8, &PIE9
};

static volatile u8* const PIR[] = {
    &PIR0, &PIR1, &PIR2, &PIR3, &PIR4, &PIR5, &PIR6, &PIR7, &PIR8, &PIR9
};

void VIC_SetShadowRegEnabled(u8 isEnabled)
{
    SHADCON = (isEnabled & 1);
}

void VIC_SetExtIntTriggerEdge(u8 ExtIntNum, u8 isRising)
{
    INTCON0 &= ~(1U << ExtIntNum);
    INTCON0 |= ((isRising & 1) << ExtIntNum);
}

void VIC_SetIrqPrioEnabled(u8 isEnabled)
{
    INTCON0bits.IPEN = (isEnabled & 1);
}

void VIC_SetIrqsEnabled(u8 isHighPrioEnabled, u8 isLowPrioEnabled)
{
    INTCON0bits.GIEL = (isLowPrioEnabled & 1);
    INTCON0bits.GIEH = (isHighPrioEnabled & 1);
}

void VIC_SetIrqVTable(u16* pVTable)
{
    IVTBASE = (u16)pVTable;
}

void VIC_SetIrqEnabled(u8 irqNum, u8 isEnabled)
{
    *PIE[irqNum/8] &= ~(1U << (irqNum % 8));
    *PIE[irqNum/8] |= ((isEnabled & 1) << (irqNum % 8));
}

void VIC_SetIrqPrio(u8 irqNum, u8 priority)
{
    *IPR[irqNum/8] &= ~(1U << (irqNum % 8));
    *IPR[irqNum/8] |= ((priority & 1) << (irqNum % 8));
}