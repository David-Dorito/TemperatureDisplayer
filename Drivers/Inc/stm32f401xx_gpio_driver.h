#ifndef STM32F401XX_GPIO_DRIVER_H_
#define STM32F401XX_GPIO_DRIVER_H_

#include "stm32f401xx.h"

//PinMode
#define GPIO_PINMODE_INPUT          0b00
#define GPIO_PINMODE_OUTPUT         0b01
#define GPIO_PINMODE_ALTFUN         0b10
#define GPIO_PINMODE_ANALOG         0b11

//PinOpType
#define GPIO_PINOPTYPE_PP           0b0
#define GPIO_PINOPTYPE_OD           0b1

//PinOpSpeed
#define GPIO_PINOPSPEED_LOW         0b00
#define GPIO_PINOPSPEED_MED         0b01
#define GPIO_PINOPSPEED_HIGH        0b10
#define GPIO_PINOPSPEED_VERYHIGH    0b11

//PinPupdCtrl
#define GPIO_PINPUPDCTRL_NOPUPD     0b00
#define GPIO_PINPUPDCTRL_PULLUP     0b01
#define GPIO_PINPUPDCTRL_PULLDOWN   0b10

//RtFtDetect
#define GPIO_RTFTDETECT_NONE        0b00
#define GPIO_RTFTDETECT_FT          0b01
#define GPIO_RTFTDETECT_RT          0b10
#define GPIO_RTFTDETECT_RTFT        0b11

#define GPIOA_REG_RESET() do {RCC->AHB1RSTR |= (1 << 0); RCC->APB2RSTR &= ~(1 << 0);} while(0)
#define GPIOB_REG_RESET() do {RCC->AHB1RSTR |= (1 << 1); RCC->APB2RSTR &= ~(1 << 1);} while(0)
#define GPIOC_REG_RESET() do {RCC->AHB1RSTR |= (1 << 2); RCC->APB2RSTR &= ~(1 << 2);} while(0)
#define GPIOD_REG_RESET() do {RCC->AHB1RSTR |= (1 << 3); RCC->APB2RSTR &= ~(1 << 3);} while(0)
#define GPIOE_REG_RESET() do {RCC->AHB1RSTR |= (1 << 4); RCC->APB2RSTR &= ~(1 << 4);} while(0)
#define GPIOH_REG_RESET() do {RCC->AHB1RSTR |= (1 << 7); RCC->APB2RSTR &= ~(1 << 7);} while(0)

typedef struct {
    u8 PinNumber;
    u8 PinMode;
    u8 OpType;
    u8 OpSpeed;
    u8 PupdCtrl;
    u8 AltFunNumber;
    u8 RtFtDetect;
} GPIO_Config;

typedef struct {
    GPIO_Config Config;
    GPIO_RegDef* pGPIOx;
} GPIO_Handle;

void GPIO_PeriphClkCtrl(GPIO_Handle* pGpioHandle, u8 ENorDI);

void GPIO_Init(GPIO_Handle* pGpioHandle);
void GPIO_Deinit(GPIO_Handle* pGpioHandle);
void GPIO_PortReset(GPIO_Handle* pGpioHandle);

void GPIO_TogglePin(GPIO_Handle* pGpioHandle);
void GPIO_WritePin(GPIO_Handle* pGpioHandle, u8 ENorDI);
void GPIO_WritePort(GPIO_Handle* pGpioHandle, u16 outputReg);

u8 GPIO_ReadPin(GPIO_Handle* pGpioHandle);
u16 GPIO_ReadPort(GPIO_Handle* pGpioHandle);

#endif /* STM32F401XX_GPIO_DRIVER_H_ */