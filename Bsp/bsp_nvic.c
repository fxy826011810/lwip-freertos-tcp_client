#include "main.h"

void bsp_nvicInit(void)
{
	MAP_IntPrioritySet(INT_EMAC0, 0xc0);
	MAP_IntPrioritySet(FAULT_SYSTICK, 0x80);
}


#define __enbale_irq() ROM_IntMasterEnable()
#define __disable_irq() ROM_IntMasterDisable()

void bsp_intEnable(void)
{
  ROM_IntMasterEnable();
}
