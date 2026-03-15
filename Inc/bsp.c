#include "bsp.h"

GPIO_Handle btnPin = (GPIO_Handle){
    .Port = GPIO_PORTB,
    .Pin = 7,
    .Config = (GPIO_Config){
        .AltFuncEn = FALSE,
        .Direction = GPIO_DIRECTION_INPUT,
        .InAnalogEn = FALSE,
        .InMode = GPIO_INMODE_ST,
        .IntSrc = GPIO_INTSRC_IOC,
        .PullupEn = TRUE,
        .RtFtDetect = GPIO_RTFTDETECT_FT
    }
};

void BSP_Init(void)
{
    VIC_SetShadowRegEnabled(TRUE);
    VIC_SetIrqsEnabled(TRUE, FALSE);
    VIC_SetIrqEnabled(VIC_IRQ_IOC, TRUE);
    
    GPIO_Init(&btnPin);
}