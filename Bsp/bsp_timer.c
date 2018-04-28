#include "main.h"




static void bsp_systickInit(void)
{
	MAP_SysTickPeriodSet(g_ui32SysClock / 1000);
	MAP_SysTickEnable();
	MAP_SysTickIntEnable();
}

void bsp_timerInit(void)
{
	bsp_systickInit();
}
