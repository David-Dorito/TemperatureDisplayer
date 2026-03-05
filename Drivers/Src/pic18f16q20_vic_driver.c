#include "../Inc/pic18f16q20_vic_driver.h"

inline void VIC_SetShadowRegEnabled(u8 isEnabled)
{
    VIC->SHADCON &= ~(1U);
    VIC->SHADCON |= !(isEnabled & 1);
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

inline void VIC_SetIrqPriority(u8 irqNum, u8 priority)
{
    VIC->IPR[irqNum/8] &= ~(1U << (irqNum % 8));
    VIC->IPR[irqNum/8] |= ((priority & 1) << (irqNum % 8));
}