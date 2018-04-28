#ifndef __BSP_NVIC_H
#define __BSP_NVIC_H

#define __enbale_irq() ROM_IntMasterEnable()
#define __disable_irq() ROM_IntMasterDisable()

void bsp_nvicInit(void);
void bsp_intEnable(void);

#endif //__BSP_NVIC_H
