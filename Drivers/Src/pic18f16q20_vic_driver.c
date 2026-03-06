#include "../Inc/pic18f16q20_vic_driver.h"

#define VIC_INCON0_IPEN             5
#define VIC_INCON0_GIEL             6
#define VIC_INCON0_GIEH             7

inline void VIC_SetShadowRegEnabled(u8 isEnabled)
{
    VIC->SHADCON &= ~(1U);
    VIC->SHADCON |= !(isEnabled & 1);
}

inline void VIC_SetExtIntTriggerEdge(u8 ExtIntNum, u8 isRising)
{
    VIC->INTCON[0] &= ~(1U << ExtIntNum);
    VIC->INTCON[0] |= ((isRising & 1) << ExtIntNum);
}

inline void VIC_SetIrqPrioEnabled(u8 isEnabled)
{
    VIC->INTCON[0] &= ~(1U << VIC_INCON0_IPEN);
    VIC->INTCON[0] |= ((isEnabled & 1) << VIC_INCON0_IPEN);
}

void VIC_SetIrqsEnabled(u8 isHighPrioEnabled, u8 isLowPrioEnabled)
{
    VIC->INTCON[0] &= ~(1U << VIC_INCON0_GIEL);
    VIC->INTCON[0] |= ((isLowPrioEnabled & 1) << VIC_INCON0_GIEL);
    VIC->INTCON[0] &= ~(1U << VIC_INCON0_GIEH);
    VIC->INTCON[0] |= ((isHighPrioEnabled & 1) << VIC_INCON0_GIEH);
}

inline void VIC_SetIrqVTable(u16* pVTable)
{
    VIC->IVTBASE = (u16)pVTable;
}

inline void VIC_SetIrqEnabled(u8 irqNum, u8 isEnabled)
{
    VIC->PIE[irqNum/8] &= ~(1U << (irqNum % 8));
    VIC->PIE[irqNum/8] |= ((isEnabled & 1) << (irqNum % 8));
}

inline void VIC_SetIrqPrio(u8 irqNum, u8 priority)
{
    VIC->IPR[irqNum/8] &= ~(1U << (irqNum % 8));
    VIC->IPR[irqNum/8] |= ((priority & 1) << (irqNum % 8));
}