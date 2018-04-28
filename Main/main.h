#ifndef __MAIN_H
#define __MAIN_H
//systemlib
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
//inc
#include "inc/hw_sysctl.h"
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "inc/hw_gpio.h"
#include "inc/hw_i2c.h"
#include "inc/hw_ssi.h"
#include "inc/hw_i2c.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"
#include "inc/hw_memmap.h"
//driverlib
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/ssi.h"
#include "driverlib/i2c.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
//freertos
#include "FreeRtos.h"
#include "task.h"
#include "queue.h"
//utils
#include "utils/uartstdio.h"
#include "utils/lwiplib.h"
#include "utils/uartstdio.h"
#include "utils/locator.h"
//lwip
#include "httpserver_raw/httpd.h"
//bsp
#include "bsp_sysctl.h"
#include "bsp_gpio.h"
#include "bsp_i2c.h"
#include "bsp_nvic.h"
#include "bsp_spi.h"
#include "bsp_timer.h"
#include "bsp_uart.h"
//user
#include "lcd.h"
#include "temperature.h"
#include "backplane.h"



#include "Lwip_Task.h"
#include "tcpClient.h"


//#include "bsp_.h"


extern uint32_t g_ui32SysClock;
#endif //__MAIN_H
