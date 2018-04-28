#include "main.h"




typedef struct
{
	uint8_t hex;
	float f;
}tmpConver;

tmpConver TmpLow[16]={\
		0x00,0.0f,\
		0x10,0.06f,\
		0x20,0.12f,\
		0x30,0.18f,\
		0x40,0.25f,\
		0x50,0.31f,\
		0x60,0.37f,\
		0x70,0.43f,\
		0x80,0.50f,\
		0x90,0.56f,\
		0xa0,0.62f,\
		0xb0,0.68f,\
		0xc0,0.75f,\
		0xd0,0.81f,\
		0xe0,0.87f,\
		0xf0,0.93f};
//*****************************************************************************
//
// The system clock frequency.
//
//*****************************************************************************
extern uint32_t g_ui32SysClock;



unsigned char temperture_ReadOneByte(uint8_t RegAddr)
{
	return I2C_ReadOneByte(TEMP_ADDR,RegAddr);
}
uint8_t tempertureWriteByte(uint8_t RegAddr, uint8_t WriteData)
{
	return IICwriteByte(TEMP_ADDR,RegAddr, WriteData);
}

uint8_t TMP_Read(void)
{
	uint8_t buf;
	buf=temperture_ReadOneByte(LOCAL_TMP_H);
	return buf;
}
static int tmp431_init_client()
{
	int config, config_orig, status = 0;

	/* Set the conversion rate to 1 Hz */
	tempertureWriteByte(TMP401_CONVERSION_RATE_WRITE, 4);

	/* Start conversions (disable shutdown if necessary) */
	config = temperture_ReadOneByte(TMP401_CONFIG_READ);

	if (config < 0)
		return config;
	config_orig = config;
	config &= ~TMP401_CONFIG_SHUTDOWN;

	if (config != config_orig)
		status = tempertureWriteByte(TMP401_CONFIG_WRITE,config);

	return status;
}

unsigned char temp_id;
unsigned char temp_on;
void Tmp_Update(void)
{
	temp_id=temperture_ReadOneByte(0xFD);
	if(temp_id==TEMP_ID)
	{
		temp_on=1;
	}
	else
	{
		temp_on=0;
	}
	if(temp_on)
	{
		char status,buf[8];
		status=temperture_ReadOneByte(STATUS);
		sprintf(buf,"%d",TMP_Read());
		LcdTmpStateUpdate((unsigned char*)buf,status);
	}
}


uint8_t temperture_init(void)
{

	//reset
	tempertureWriteByte(Software_reset,0xFF);
	//¶ÁÈ¡id
	temp_id=temperture_ReadOneByte(0xFD);

	UARTprintf("id=%x\r\n",temp_id);
	if(temp_id!=TEMP_ID)
	{
		temp_on=0;
		return 1;
	}
	else
	{
		temp_on=1;
	}
	tmp431_init_client();
	return 0;
}

