#ifndef STM32F401XX_H_
#define STM32F401XX_H_

#include <stdint.h>

#define HIGH                                1
#define LOW                                 0
#define TRUE                                1
#define FALSE                               0
#define ENABLE                              1
#define DISABLE                             0

#define WEAK                                __attribute__((weak))

typedef int64_t                             i64;
typedef int32_t                             i32;
typedef int16_t                             i16;
typedef int8_t                              i8;
typedef uint64_t                            u64;
typedef uint32_t                            u32;
typedef uint16_t                            u16;
typedef uint8_t                             u8;

/******************************** PROCESSOR SPECIFIC DETAILS ********************************/

#define NVIC_ISER0							((volatile u32*)0xE000E100U)
#define NVIC_ISER1							((volatile u32*)0xE000E104U)
#define NVIC_ISER2							((volatile u32*)0xE000E108U)
#define NVIC_ISER3							((volatile u32*)0xE000E10CU)

#define NVIC_ICER0							((volatile u32*)0xE000E180U)
#define NVIC_ICER1							((volatile u32*)0xE000E184U)
#define NVIC_ICER2							((volatile u32*)0xE000E188U)
#define NVIC_ICER3							((volatile u32*)0xE000E18CU)

#define NVIC_PR_BASEADDR					0xE000E400U
#define NVIC_PR								((volatile u32*)NVIC_PR_BASEADDR)

#define NO_PR_BITS_IMPLEMENTED				4

/*********************************************************************************************/

#define ENABLE 								1
#define DISABLE 							0
#define HIGH								1
#define LOW									0

#define IRQ_NO_EXTI0						6
#define IRQ_NO_EXTI1						7
#define IRQ_NO_EXTI2						8
#define IRQ_NO_EXTI3						9
#define IRQ_NO_EXTI4						10
#define IRQ_NO_EXTI9_5						23
#define IRQ_NO_EXTI15_10					40
#define IRQ_NO_SPI1							35
#define IRQ_NO_SPI2							36
#define IRQ_NO_SPI3						    51
#define IRQ_NO_SPI4                         84

#define FLASH_BASEADDR 						0x08000000U
#define SRAM_BASEADDR 						0x20000000U
#define ROM_BASEADDR						0x1FFF0000U

#define PERIPH_BASEADDR						0x40000000U
#define APB1PERIPH_BASEADDR					PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR					0x40010000U
#define AHB1PERIPH_BASEADDR					0x40020000U
#define AHB2PERIPH_BASEADDR					0x50000000U
#define RCC_BASEADDR						0x40023800U

#define GPIOA_BASEADDR						(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR						(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR						(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR						(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR						(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOH_BASEADDR						(AHB1PERIPH_BASEADDR + 0x1C00)

#define I2C1_BASEADDR						(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR						(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR						(APB1PERIPH_BASEADDR + 0x5C00)
#define SPI2_BASEADDR						(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR						(APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR						(APB1PERIPH_BASEADDR + 0x4400)

#define SPI1_BASEADDR						(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR                       (APB1PERIPH_BASEADDR + 0x3400)
#define USART1_BASEADDR						(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR						(APB2PERIPH_BASEADDR + 0x1400)
#define EXTI_BASEADDR						(APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR						(APB2PERIPH_BASEADDR + 0x3800)

typedef struct {
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
} EXTI_RegDef;

#define EXTI								((EXTI_RegDef*)EXTI_BASEADDR)

typedef struct {
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
} GPIO_RegDef;

#define GPIOA								((GPIO_RegDef*)GPIOA_BASEADDR)
#define GPIOB								((GPIO_RegDef*)GPIOB_BASEADDR)
#define GPIOC								((GPIO_RegDef*)GPIOC_BASEADDR)
#define GPIOD								((GPIO_RegDef*)GPIOD_BASEADDR)
#define GPIOE								((GPIO_RegDef*)GPIOE_BASEADDR)
#define GPIOH								((GPIO_RegDef*)GPIOH_BASEADDR)

typedef struct {
	volatile u32 CR1;
	volatile u32 RESERVED;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;
} SPI_RegDef;

#define SPI1								((SPI_RegDef*)SPI1_BASEADDR)
#define SPI2								((SPI_RegDef*)SPI2_BASEADDR)
#define SPI3								((SPI_RegDef*)SPI3_BASEADDR)
#define SPI4                                ((SPI_RegDef*)SPI4_BASEADDR)

typedef struct {
    volatile u32 CR1;
    volatile u32 CR2;
    volatile u32 OAR1;
    volatile u32 OAR2;
    volatile u32 DR;
    volatile u32 SR1;
    volatile u32 SR2;
    volatile u32 CCR;
    volatile u32 TRISE;
    volatile u32 FLTR;
} I2C_RegDef;

#define I2C1                                ((I2C_RegDef*)I2C1_BASEADDR)
#define I2C2                                ((I2C_RegDef*)I2C2_BASEADDR)
#define I2C3                                ((I2C_RegDef*)I2C3_BASEADDR)

typedef struct {
	volatile u32 CR;
	volatile u32 PLLCFGR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 AHB1RSTR;
	volatile u32 AHB2RSTR;
	volatile u32 RESERVED00[2];
	volatile u32 APB1RSTR;
	volatile u32 APB2RSTR;
	volatile u32 RESERVED01[2];
	volatile u32 AHB1ENR;
	volatile u32 AHB2ENR;
	volatile u32 RESERVED02[2];
	volatile u32 APB1ENR;
	volatile u32 APB2ENR;
	volatile u32 RESERVED03[2];
	volatile u32 AHB1LPENR;
	volatile u32 AHB2LPENR;
	volatile u32 RESERVED04[2];
	volatile u32 APB1LPENR;
	volatile u32 APB2LPENR;
	volatile u32 RESERVED05[2];
	volatile u32 BDCR;
	volatile u32 CSR;
	volatile u32 RESERVED06[2];
	volatile u32 SSCGR;
	volatile u32 PLLI2SCFGR;
	volatile u32 RESERVED07;
	volatile u32 DCKCFGR;
} RCC_RegDef;

#define RCC									((RCC_RegDef*)RCC_BASEADDR)

typedef struct {
	volatile u32 MEMRMP;
	volatile u32 PMC;
	volatile u32 EXTICR1;
	volatile u32 EXTICR2;
	volatile u32 EXTICR3;
	volatile u32 EXTICR4;
	volatile u32 RESERVED[2];
	volatile u32 CMPCR;
} SYSCFG_RegDef;

#define SYSCFG								((SYSCFG_RegDef*)SYSCFG_BASEADDR)

#define GPIOA_PCLK_EN()						(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()						(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()						(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()						(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()						(RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()						(RCC->AHB1ENR |= (1 << 7))

#define I2C1_PCLK_EN()						(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()						(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()						(RCC->APB1ENR |= (1 << 23))

#define SPI1_PCLK_EN()						(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()						(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()						(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()						(RCC->APB2ENR |= (1 << 13))

#define USART1_PCLK_EN()					(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()					(RCC->APB1ENR |= (1 << 17))
#define USART6_PCLK_EN()					(RCC->APB2ENR |= (1 << 5))

#define SYSCFG_PCLK_EN()					(RCC->APB2ENR |= (1 << 14))

#define GPIOA_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()						(RCC->AHB1ENR &= ~(1 << 7))

#define I2C1_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 23))

#define SPI1_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()						(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()						(RCC->APB2ENR &= ~(1 << 13))

#define USART1_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()					(RCC->APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 5))

#define SYSCFG_PCLK_DI()					(RCC->APB2ENR &= ~(1 << 14))

/*************************************\
  fn: @IRQ_PrioCtrl
  
  param1 u8: the IRQ number for which you have to set the priority
  param2 u8: the IRQ priority
  
  return:
  
  desc: sets the IRQ priority of the signal
  
  note: 
  
\**************************************/
void IRQ_PrioCtrl(u8 IrqNumber, u8 IrqPriority);

/*************************************\
  fn: @IRQ_ItCtrl
  
  param1 u8: the interrupt line
  param2 u8: enable or disable
  
  return:
  
  desc: enables or disables a specific interrupt line in the NVIC
  
  note: 
  
\**************************************/
void IRQ_ItCtrl(u8 IrqNumber, u8 isEnabled);

#endif /* STM32F401XX_H_ */