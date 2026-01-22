#ifndef STM32F401XX_H_
#define STM32F401XX_H_

#include <stdint.h>

#define HIGH                1
#define LOW                 0
#define TRUE                1
#define FALSE               0
#define ENABLE              1
#define DISABLE             0

#define WEAK                __attribute__((weak))

typedef int64_t             i64;
typedef int32_t             i32;
typedef int16_t             i16;
typedef int8_t              i8;
typedef uint64_t            u64;
typedef uint32_t            u32;
typedef uint16_t            u16;
typedef uint8_t             u8;

/******************************** PROCESSOR SPECIFIC DETAILS ********************************/

#define NVIC_ISER0							((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1							((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2							((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3							((volatile uint32_t*)0xE000E10C)

#define NVIC_ICER0							((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1							((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2							((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3							((volatile uint32_t*)0xE000E18C)

#define NVIC_PR_BASEADDR					0xE000E400U
#define NVIC_PR								((volatile uint32_t*)0xE000E400)

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
#define GPIO_BASEADDR_TO_CODE(PORT_ADDR)	((PORT_ADDR-AHB1PERIPH_BASEADDR)/0x400U)

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
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} EXTI_RegDef;

#define EXTI								((EXTI_RegDef*)EXTI_BASEADDR)

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIO_RegDef;

#define GPIOA								((GPIO_RegDef*)GPIOA_BASEADDR)
#define GPIOB								((GPIO_RegDef*)GPIOB_BASEADDR)
#define GPIOC								((GPIO_RegDef*)GPIOC_BASEADDR)
#define GPIOD								((GPIO_RegDef*)GPIOD_BASEADDR)
#define GPIOE								((GPIO_RegDef*)GPIOE_BASEADDR)
#define GPIOH								((GPIO_RegDef*)GPIOH_BASEADDR)

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t RESERVED;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
} SPI_RegDef;

#define SPI1								((SPI_RegDef*)SPI1_BASEADDR)
#define SPI2								((SPI_RegDef*)SPI2_BASEADDR)
#define SPI3								((SPI_RegDef*)SPI3_BASEADDR)
#define SPI4                                ((SPI_RegDef*)SPI4_BASEADDR)

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t RESERVED00[2];
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED01[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t RESERVED02[2];
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED03[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED04[2];
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED05[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED06[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t RESERVED07;
	volatile uint32_t DCKCFGR;
} RCC_RegDef;

#define RCC									((RCC_RegDef*)RCC_BASEADDR)

typedef struct {
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED[2];
	volatile uint32_t CMPCR;
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

void IRQ_PriorityControl(uint8_t IRQNumber, uint32_t IRQPriority);
void IRQ_InterruptControl(uint8_t IRQNumber, uint8_t value);

#endif /* STM32F401XX_H_ */
