//*****************************************************************************
//
// serial.h - Prototypes for the Serial Port Driver
//
// Copyright (c) 2014-2015 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__


//I2c0 pin config
#define TEMP_ID	0x31
#define TEMP_ADDR 0x4C
#define TEMP_PORT_BASE GPIO_PORTB_BASE
#define TEMP_SCL_PIN   GPIO_PIN_2
#define TEMP_SDA_PIN   GPIO_PIN_3

#define TMP431_DEVICE_ID			0x31

/*
 * The TMP401 registers, note some registers have different addresses for
 * reading and writing
 */
#define TMP401_STATUS				0x02
#define TMP401_CONFIG_READ			0x03
#define TMP401_CONFIG_WRITE			0x09
#define TMP401_CONVERSION_RATE_READ		0x04
#define TMP401_CONVERSION_RATE_WRITE		0x0A
#define TMP401_TEMP_CRIT_HYST			0x21
#define TMP401_MANUFACTURER_ID_REG		0xFE
#define TMP401_DEVICE_ID_REG			0xFF

/* Flags */
#define TMP401_CONFIG_RANGE				(1<<2)
#define TMP401_CONFIG_SHUTDOWN			(1<<6)

#define TMP401_STATUS_LOCAL_CRIT		(1<<0)
#define TMP401_STATUS_REMOTE_CRIT		(1<<1)
#define TMP401_STATUS_REMOTE_OPEN		(1<<2)
#define TMP401_STATUS_REMOTE_LOW		(1<<3)
#define TMP401_STATUS_REMOTE_HIGH		(1<<4)
#define TMP401_STATUS_LOCAL_LOW			(1<<5)
#define TMP401_STATUS_LOCAL_HIGH		(1<<6)

//Read
#define	LOCAL_TMP_H				0x00
#define	REMOTE_TMP_H			0x01
#define STATUS					0x02
#define	CONFIG_1_READ			0x03
#define	CONVERSION_RATE_READ	0x04
#define	LOCAL_TMP_H_LIM_H_READ	0x05
#define	LOCAL_TMP_L_LIM_H_READ	0x06
#define	REMOTE_TMP_H_LIM_H_READ	0x07
#define REMOTE_TMP_L_LIM_H_READ	0x08
#define	REMOTE_TMP_L			0x10
#define	REMOTE_TMP_H_LIM_L		0x13
#define	REMOTE_TMP_L_LIM_L		0x14
#define	LOCAL_TMP_L				0x15
#define	LOCAL_TMP_H_LIM_L		0x16
#define	LOCAL_TMP_L_LIM_L		0x17
#define	N_factor_correction		0x18
#define	REMOTE_THERM_LIM		0x19
#define	CONFIG_2				0x1A
#define	CHANNEL_MASK			0x1F
#define	LOCAL_THERM_LIM			0x20
#define	THERM_hysteresis		0x21
#define	Consecutive_alert		0x22
#define	Beta_range				0x25
#define Manufacturer_ID			0xFE
#define TMP431_device_ID		0xFD
//Write
#define	CONFIG_1_WRITE			0x09
#define	CONVERSION_RATE_WRITE	0x0A
#define	LOCAL_TMP_H_LIM_H_WRITE	0x0B
#define	LOCAL_TMP_L_LIM_H_WRITE	0x0C
#define	REMOTE_TMP_H_LIM_H_WRITE	0x0D
#define REMOTE_TMP_L_LIM_H_WRITE	0x0E
#define Software_reset				0xFC





uint8_t temperture_init(void);
void Tmp_Update(void);
#endif	//__TEMPERATURE_H__
