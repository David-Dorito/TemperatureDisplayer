#include "../Inc/stm32f401xx.h"

/*************************************\
  fn: @IRQ_PriorityControl
  
  param1 u8: the IRQ number for which you have to set the priority
  param2 u8: the IRQ priority
  
  return:
  
  desc: sets the IRQ priority of the signal
  
  note: 
  
\**************************************/
void IRQ_PriorityControl(u8 IRQNumber, u32 IRQPriority)
{
	u8 iprx = IRQNumber / 4;
	u8 iprx_section = IRQNumber % 4;

	*(NVIC_PR + iprx) |= (IRQPriority << ((8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED)));
}

/*************************************\
  fn: @IRQ_InterruptControl
  
  param1 u8: the interrupt line
  param2 u8: enable or disable
  
  return:
  
  desc: enables or disables a specific interrupt line in the NVIC
  
  note: 
  
\**************************************/
void IRQ_InterruptControl(u8 IRQNumber, u8 value)
{
	if (value)
	{
		if (IRQNumber <= 31)
			*NVIC_ISER0 |= (1 << IRQNumber);

		else if (IRQNumber > 31 && IRQNumber < 64)
			*NVIC_ISER1 |= (1 << (IRQNumber - 32));

		else if (IRQNumber >= 64 && IRQNumber < 95)
			*NVIC_ISER2 |= (1 << (IRQNumber - 64));
	}
	else
	{
		if (IRQNumber <= 31)
			*NVIC_ICER0 |= (1 << IRQNumber);

		else if (IRQNumber > 31 && IRQNumber < 64)
			*NVIC_ICER1 |= (1 << (IRQNumber - 32));

		else if (IRQNumber >= 64 && IRQNumber < 95)
			*NVIC_ICER2 |= (1 << (IRQNumber - 64));
	}
}
