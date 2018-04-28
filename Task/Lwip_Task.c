#include "main.h"
#include "Lwip_Task.h"
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "httpserver_raw/httpd.h"

uint8_t lwipTask_init(void)
{
	uint8_t pui8MACArray[8]={0x01,0x02,0x1c,0x66,0x65,0x66};
	uint32_t ip_address = 0xc0a80278;
	uint32_t mask_address = 0xffffff00;
	uint32_t gateway_address = 0xc0a80201;
	lwIPInit(g_ui32SysClock, pui8MACArray, ip_address, mask_address, gateway_address, IPADDR_USE_STATIC);
	LocatorInit();
	LocatorMACAddrSet(pui8MACArray);
	LocatorAppTitleSet("EK-TM4C1294XL enet_io");

	httpd_init();
	return 0;
}

void lwIPHostTimerHandler(void)
{

}
