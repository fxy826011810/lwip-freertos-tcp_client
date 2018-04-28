#include "main.h"

void bsp_uartInit(void)
{
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
  
  ROM_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));
  ROM_UARTConfigSetExpClk(UART1_BASE, g_ui32SysClock, 115200,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));
  ROM_UARTConfigSetExpClk(UART2_BASE, g_ui32SysClock, 115200,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));
  ROM_UARTConfigSetExpClk(UART3_BASE, g_ui32SysClock, 115200,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));
  ROM_UARTConfigSetExpClk(UART4_BASE, g_ui32SysClock, 115200,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));
  ROM_UARTConfigSetExpClk(UART5_BASE, g_ui32SysClock, 115200,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));

  ROM_UARTEnable(UART0_BASE);
  ROM_UARTEnable(UART1_BASE);
  ROM_UARTEnable(UART2_BASE);
  ROM_UARTEnable(UART3_BASE);
  ROM_UARTEnable(UART4_BASE);
  ROM_UARTEnable(UART5_BASE);
  
  UARTStdioConfig(0, 115200, g_ui32SysClock);
}
