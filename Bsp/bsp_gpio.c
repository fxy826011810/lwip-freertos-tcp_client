#include "main.h"


void bsp_gpioInit(void)
{
  //lcd
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_0);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_1);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_2);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_3);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_4);
  //UART
    // PA0-1 are used for UART0.
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // PC7-6 are used for UART5.
    ROM_GPIOPinConfigure(GPIO_PC7_U5TX);
    ROM_GPIOPinConfigure(GPIO_PC6_U5RX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_7 | GPIO_PIN_6);

    // PB0-1 are used for UART1.
    ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
    ROM_GPIOPinConfigure(GPIO_PB1_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // PA6-7 are used for UART2.
    ROM_GPIOPinConfigure(GPIO_PA6_U2RX);
    ROM_GPIOPinConfigure(GPIO_PA7_U2TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    // PA4-5 are used for UART3.
    ROM_GPIOPinConfigure(GPIO_PA4_U3RX);
    ROM_GPIOPinConfigure(GPIO_PA5_U3TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    // PA2-3 are used for UART4.
    ROM_GPIOPinConfigure(GPIO_PA2_U4RX);
    ROM_GPIOPinConfigure(GPIO_PA3_U4TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3);
  //��̫��
    ROM_GPIOPinConfigure(GPIO_PF0_EN0LED0);
    ROM_GPIOPinConfigure(GPIO_PF4_EN0LED1);
    GPIOPinTypeEthernetLED(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  //I2C0
    ROM_GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    ROM_GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    ROM_GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    ROM_GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
    
}
