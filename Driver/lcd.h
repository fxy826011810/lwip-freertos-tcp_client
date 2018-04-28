//*****************************************************************************
//
// io.h - Prototypes for I/O routines for the enet_io example.
//
// Copyright (c) 2009-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#ifndef __LCD_H__
#define __LCD_H__

#ifdef __cplusplus
extern "C"
{
#endif


////lcd pin config
#define LCD_PORT_BASE GPIO_PORTN_BASE
#define LCD_CS_PIN    GPIO_PIN_0
#define LCD_RST_PIN   GPIO_PIN_1
#define LCD_RS_PIN    GPIO_PIN_2
#define LCD_SCK_PIN   GPIO_PIN_3
#define LCD_SDA_PIN   GPIO_PIN_4

#define PW_PORT_BASE GPIO_PORTM_BASE
#define PW1_PIN    GPIO_PIN_0
#define PW2_PIN    GPIO_PIN_1


#define MAX_PAGE 16
#define MIN_PAGE 1

#define MAX_COLUMN 127
#define MIN_COLUMN 0

#define CHAR_COLUMN 8
typedef struct
{
	char state[2];
	unsigned char page;//页 1-16
	unsigned char Tcolumn;//标题列 0-127
	unsigned char Ccolumn;//内容列 0-127
	unsigned char *T;//LCD标题显示内容
	unsigned char *C;//LCD内容显示内容
	char MaxLen;//显示最大长度
}lcdUintDef_t;

//*****************************************************************************
//
// Exported function prototypes.
//
//*****************************************************************************
void lcd_init(void);
void LcdCardStateUpdate(uint32_t ch,unsigned char * buf,uint8_t state);
void LcdTmpStateUpdate(unsigned char * buf,uint8_t state);
void LcdPowerStateUpdate(uint32_t ch,unsigned char * buf,uint8_t state);
void LcdFanStateUpdate(unsigned char * buf,uint8_t state);

void LcdTmpStateDisplay(void);
void LcdFanStateDisplay(void);
void LcdCardStateDisplay(void);
void LcdPowerStateDisplay(void);
#ifdef __cplusplus
}
#endif

#endif // __IO_H__
