#include "main.h"


#define CARD_STATUS3	(1<<0)
#define CARD_STATUS2	(1<<1)
#define CARD_STATUS1	(1<<2)
#define CARD_STATUS0	(1<<3)
#define CASE_A0			(1<<4)
#define CASE_A1			(1<<5)
#define CASE_A2			(1<<6)
#define CASE_A3			(1<<7)

#define PRESENT1		(1<<0)
#define PRESENT2		(1<<1)
#define PW_OK1			(1<<2)
#define PW_OK2			(1<<3)
#define FAN_STATUS		(1<<4)

#define TCA9535_ADDR 0x20
#define POWER2_ADDR 0xA2
#define POWER1_ADDR 0xA0
unsigned char tca9535_ReadOneByte(uint8_t RegAddr)
{
	return I2C_ReadOneByte(TCA9535_ADDR,RegAddr);
}
uint8_t tca9535WriteByte(uint8_t RegAddr, uint8_t WriteData)
{
	return IICwriteByte(TCA9535_ADDR,RegAddr, WriteData);
}

uint8_t tca9535Check(uint8_t state,uint8_t states)
{
	return state&states;
}
extern lcdUintDef_t CARD[4];
extern lcdUintDef_t Pw[2];//电源
extern lcdUintDef_t fan;//风扇
void tca9535StatusUpdate(void)
{
	uint8_t i=0,check=0,num=0;

	uint8_t addr[6][2]={0x02,0xFF,\
						0x03,0xFF,\
						0x04,0x00,\
						0x05,0x00,\
						0x06,0xFF,\
						0x07,0xFF};
	for(i=0;i<6;i++)
	{
		check=tca9535_ReadOneByte(addr[i][0]);
		if(check==addr[i][1])
		{
			num++;
		}
	}
	if(num==6)
	{
		uint8_t stauts[2]={0};
		stauts[0]=tca9535_ReadOneByte(0x00);//PO;
		stauts[1]=tca9535_ReadOneByte(0x01);//P1;

		if(tca9535Check(stauts[0],CARD_STATUS3)||tca9535Check(stauts[0],CARD_STATUS2)||tca9535Check(stauts[0],CARD_STATUS1)||tca9535Check(stauts[0],CARD_STATUS0))
		{
			UARTprintf("Card ERR\r\n");
		}
		/////////////////////////////////////////////////////////////////
		//四个卡状态信息
		////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////
		//卡三状态信息
		////////////////////////////////////////////////////////////////
		if(tca9535Check(stauts[0],CARD_STATUS3))
		{
			LcdCardStateUpdate(3,"OK",1);
		}
		else
		{
			LcdCardStateUpdate(3,"OFF",0);
		}
		//卡二状态信息
		////////////////////////////////////////////////////////////////
		if(	tca9535Check(stauts[0],CARD_STATUS2))
		{
			LcdCardStateUpdate(2,"OK",1);
		}
		else
		{
			LcdCardStateUpdate(2,"OFF",0);
		}
		////////////////////////////////////////////////////////////////
		//卡1
		if(tca9535Check(stauts[0],CARD_STATUS1))
		{
			LcdCardStateUpdate(1,"OK",1);
		}
		else
		{
			LcdCardStateUpdate(1,"OFF",0);
		}
		////////////////////////////////////////////////////////////////
		//卡0
		if(tca9535Check(stauts[0],CARD_STATUS0))
		{
			LcdCardStateUpdate(0,"OK",1);
		}
		else
		{
			LcdCardStateUpdate(0,"OFF",0);
		}
		/////////////////////////////////////////////////////////////////
		//拨码开关
		////////////////////////////////////////////////////////////////
		if(tca9535Check(stauts[0],CASE_A0))
		{

		}
		else
		{

		}
		if(tca9535Check(stauts[0],CASE_A1))
		{

		}
		else
		{

		}
		if(tca9535Check(stauts[0],CASE_A2))
		{

		}
		else
		{

		}
		if(tca9535Check(stauts[0],CASE_A3))
		{

		}
		else
		{

		}
		/////////////////////////////////////////////////////////////////
		//电源在位
		////////////////////////////////////////////////////////////////
		if(tca9535Check(stauts[1],PRESENT1))
		{
			LcdPowerStateUpdate(0,"OFF",1);
		}
		else
		{
			if(tca9535Check(stauts[1],PW_OK1))
			{
				LcdPowerStateUpdate(0,"OK",1);
			}
			else
			{
				LcdPowerStateUpdate(0,"WAR",0);
			}
		}
		if(tca9535Check(stauts[1],PRESENT2))
		{
			LcdPowerStateUpdate(1,"OFF",1);
		}
		else
		{
			if(tca9535Check(stauts[1],PW_OK2))
				{
					LcdPowerStateUpdate(1,"OK",1);
				}
				else
				{
					LcdPowerStateUpdate(1,"WAR",0);
				}
		}
		/////////////////////////////////////////////////////////////////
		//风扇
		////////////////////////////////////////////////////////////////
		if(tca9535Check(stauts[1],FAN_STATUS))
		{
			LcdFanStateUpdate("OK",1);
		}
		else
		{
			LcdFanStateUpdate("WAR",0);
		}
	}
}
void tca9535Update(void)
{
	tca9535StatusUpdate();
}

typedef struct
{
	uint16_t Block_signal;
	uint8_t Block_version;
	uint8_t Block_length;
	uint16_t Block_checksum;
	uint16_t eeprom_size;
	uint16_t Block_count;
	char OEM_string[20];
	char Product_number[20];
	char Serial_number[30];
	char Part_number[16];
	char Part_version[4];
	char Mfg_deviation[20];
	int16_t Power_consumption;
	char Power_Type[10];
	char Air_flow_direction[8];
}Power_EEPROM;
uint8_t power1Buf[140]={0},power2Buf[140]={0};
Power_EEPROM *power1Info=(Power_EEPROM *)power1Buf;
Power_EEPROM *power2Info=(Power_EEPROM *)power2Buf;
void powerInfoRead(void)
{
	IICreadBytes(POWER1_ADDR,0x00,sizeof(Power_EEPROM),power1Buf);
	IICreadBytes(POWER2_ADDR,0x00,sizeof(Power_EEPROM),power2Buf);

}









