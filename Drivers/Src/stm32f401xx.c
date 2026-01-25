#include "../Inc/stm32f401xx.h"

/*************************************\
  fn: @IRQ_PrioCtrl
  
  param1 u8: the IRQ number for which you have to set the priority
  param2 u8: the IRQ priority
  
  return:
  
  desc: sets the IRQ priority of the signal
  
  note: 
  
\**************************************/
void IRQ_PrioCtrl(u8 IrqNumber, u8 IrqPriority)
{
	u8 iprx = IrqNumber / 4;
	u8 iprx_section = IrqNumber % 4;

	*(NVIC_PR + iprx) |= (IrqPriority << ((8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED)));
}

/*************************************\
  fn: @IRQ_ItCtrl
  
  param1 u8: the interrupt line
  param2 u8: enable or disable
  
  return:
  
  desc: enables or disables a specific interrupt line in the NVIC
  
  note: 
  
\**************************************/
void IRQ_ItCtrl(u8 IrqNumber, u8 isEnabled)
{
	if (isEnabled)
	{
		if (IrqNumber <= 31)
			*NVIC_ISER0 |= (1 << IrqNumber);

		else if (IrqNumber > 31 && IrqNumber < 64)
			*NVIC_ISER1 |= (1 << (IrqNumber - 32));

		else if (IrqNumber >= 64 && IrqNumber < 95)
			*NVIC_ISER2 |= (1 << (IrqNumber - 64));
	}
	else
	{
		if (IrqNumber <= 31)
			*NVIC_ICER0 |= (1 << IrqNumber);

		else if (IrqNumber > 31 && IrqNumber < 64)
			*NVIC_ICER1 |= (1 << (IrqNumber - 32));

		else if (IrqNumber >= 64 && IrqNumber < 95)
			*NVIC_ICER2 |= (1 << (IrqNumber - 64));
	}
}