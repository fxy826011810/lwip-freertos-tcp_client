
#include "main.h"
#include "chinese_code.h"
#include "image.h"

void delay_us(int i)
{
  int j, k;
  for (j = 0; j < i; j++) for (k = 0; k < 10; k++);
}

void delay(int i)
{
  int j, k;
  for (j = 0; j < i; j++) for (k = 0; k < 110; k++);
}



//*****************************************************************************
//
// The system clock speed.
//
//*****************************************************************************
extern uint32_t g_ui32SysClock;



//*****************************************************************************
//
// Initialize the IO used in this demo
//
//*****************************************************************************
void
LcdIo_init(void)
{

  //Init LCD
  ROM_GPIOPinTypeGPIOOutput(LCD_PORT_BASE, LCD_CS_PIN);
  ROM_GPIOPinTypeGPIOOutput(LCD_PORT_BASE, LCD_RST_PIN);
  ROM_GPIOPinTypeGPIOOutput(LCD_PORT_BASE, LCD_RS_PIN);
  ROM_GPIOPinTypeGPIOOutput(LCD_PORT_BASE, LCD_SCK_PIN);
  ROM_GPIOPinTypeGPIOOutput(LCD_PORT_BASE, LCD_SDA_PIN);

  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_CS_PIN, LCD_CS_PIN); //写1
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RS_PIN, 0);
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SCK_PIN, LCD_SCK_PIN); //写1
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SDA_PIN, 0);
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RST_PIN, LCD_RST_PIN); //写1


}

/*写指令到LCD模块*/
void transfer_command(uint8_t data1)
{
  char i;

  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_CS_PIN, 0);
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RS_PIN, 0);
  for (i = 0; i < 8; i++)
  {
    ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SCK_PIN, 0);
    if (data1 & 0x80) ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SDA_PIN, LCD_SDA_PIN); //1
    else ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SDA_PIN, 0);
    ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SCK_PIN, LCD_SCK_PIN);
    data1 = data1 << 1;
  }
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_CS_PIN, LCD_CS_PIN); //1

}

/*写数据到LCD模块*/
void transfer_data(uint8_t data1)
{
  char i;

  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_CS_PIN, 0);
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RS_PIN, LCD_RS_PIN); //1
  for (i = 0; i < 8; i++)
  {
    ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SCK_PIN, 0);
    if (data1 & 0x80) ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SDA_PIN, LCD_SDA_PIN); //1
    else ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SDA_PIN, 0);
    ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_SCK_PIN, LCD_SCK_PIN);
    data1 = data1 << 1;
  }
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_CS_PIN, LCD_CS_PIN); //1
}

void initial_lcd()
{
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RST_PIN, 0);
  delay(500);
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RST_PIN, LCD_RST_PIN);
  delay(100);

  transfer_command(0x2c);
  delay(200);
  transfer_command(0x2e);
  delay(200);
  transfer_command(0x2f);
  delay(10);

  transfer_command(0xae);   //显示关
  transfer_command(0x38);   //模式设置
  transfer_command(0xb8);   //85HZ
  transfer_command(0xc8);   //行扫描顺序 反转扫描顺序：从下到上
  transfer_command(0xa0);   //列扫描顺序 常规：列地址从左到右
                            //
  //transfer_command(0xc0);   //行扫描顺序 普通扫描顺序：从上到下 
  //transfer_command(0xa1);   //列扫描顺序 反转：列地址从右到左

  transfer_command(0x44);   //Set initial COM0 register
  transfer_command(0x00);
  transfer_command(0x40);   //Set initial display line register
  transfer_command(0x00);

  transfer_command(0xab);
  transfer_command(0x67);
  transfer_command(0x27);   //粗调对比度，可设置范围0x20～0x27
  transfer_command(0x81);   //微调对比度
  transfer_command(0x28);   //微调对比度的值，可设置范围0x00～0x3f

  transfer_command(0x56);   //0x56  1/11 bias
  transfer_command(0xf3);
  transfer_command(0x04);
  transfer_command(0x93);

  transfer_command(0xa6);//for test

  transfer_command(0xaf);   //显示开

}

void lcd_address(unsigned char page, unsigned char column)
{
  ROM_GPIOPinWrite(LCD_PORT_BASE, LCD_RS_PIN, LCD_RS_PIN); //1
  column = column;
  page = page - 1;
  transfer_command(0xb0 + page);
  transfer_command(((column >> 4) & 0x0f) + 0x10);
  transfer_command(column & 0x0f);
}
//清除全部屏幕
void clear_screen()
{
  unsigned char i, j;
  for (j = 0; j < 16; j++)
  {
    lcd_address(j + 1, 0);
    for (i = 0; i < 128; i++)
    {
      transfer_data(0x00);

      transfer_data(0x00);
    }
  }
}
//清除部分屏幕
void clear_partPageScreen(unsigned char page,unsigned char column,unsigned char len)
{
  unsigned char i, j;

  for (j = page; j < page+2; j++)
  {
    lcd_address(j, column);
    for (i = 0; i < 8*len; i++)
    {
      transfer_data(0x00);

      transfer_data(0x00);
    }
  }
}

//显示8x16的点阵的字符串，括号里的参数分别为（页,列，字符串指针）
void display_string_8x16(unsigned char page, unsigned char column, unsigned char *text)
{
  unsigned int i = 0, j, k, n;

  while (text[i] > 0x00)
  {
    if ((text[i] >= 0x20) && (text[i] <= 0x7e))
    {
      j = text[i] - 0x20;
      for (n = 0; n < 2; n++)
      {
        lcd_address(page + n, column);
        for (k = 0; k < 8; k++)
        {
          transfer_data(ascii_table_8x16[j][k + 8 * n]);
          transfer_data(ascii_table_8x16[j][k + 8 * n]);
        }
      }
      i++;
      column += 8;
    }
    else i++;

    if (column > 127)
    {
      column = 0;
      page += 2;
    }
  }
}


//写入一组16x16点阵的汉字字符串（字符串表格中需含有此字）
//括号里的参数：(页，列，汉字字符串）
void display_string_16x16(unsigned char page, unsigned char column, unsigned char *text)
{
  unsigned char i, j, k;
  unsigned int address;
  j = 0;
  while (text[j] != '\0')
  {
    i = 0;
    address = 1;
    while (Chinese_text_16x16[i] > 0x7e)
    {
      if (Chinese_text_16x16[i] == text[j])
      {
        if (Chinese_text_16x16[i + 1] == text[j + 1])
        {
          address = i * 16;
          break;
        }
      }
      i += 2;
    }
    if (column > 127)
    {
      column = 0;
      page += 2;
    }
    if (address != 1)
    {
      for (k = 0; k < 2; k++)
      {
        lcd_address(page + k, column);
        for (i = 0; i < 16; i++)
        {
          transfer_data(Chinese_code_16x16[address]);
          transfer_data(Chinese_code_16x16[address]);
          address++;

        }
      }
      j += 2;
    }
    else
    {
      for (k = 0; k < 2; k++)
      {
        lcd_address(page + k, column);
        for (i = 0; i < 16; i++)
        {
          transfer_data(0x00);
          transfer_data(0x00);
        }
      }
      j++;
    }
    column += 16;
  }
}


//显示16x16点阵的汉字或者ASCII码8x16点阵的字符混合字符串
//括号里的参数：(页，列，字符串）
void display_string_8x16_16x16(unsigned char page, unsigned char column, unsigned char *text)
{
  unsigned char temp[3];
  unsigned char i = 0;
  while (text[i] != '\0')
  {
    if (text[i] > 0x7e)
    {
      temp[0] = text[i];
      temp[1] = text[i + 1];
      temp[2] = '\0';                           //汉字为两个字节
      display_string_16x16(page, column, temp); //显示汉字
      column += 16;
      i += 2;
      if (column > 127)
      {
        column = 0;
        page += 2;
      }
    }
    else
    {
      temp[0] = text[i];
      temp[1] = '\0';                           //字母占一个字节
      display_string_8x16(page, column, temp);  //显示字母
      column += 8;
      i++;
      if (column > 127)
      {
        column = 0;
        page += 2;
      }
    }
  }
}

void display_32x32(unsigned char page, unsigned char column, unsigned char *dp)
{
  int i, j;
  for (j = 0; j < 4; j++)
  {
    lcd_address(page + j, column);
    for (i = 0; i < 32; i++)
    {
      transfer_data(*dp);
      transfer_data(*dp);
      dp++;
    }
  }

}


void display_graphic(unsigned char *dp)
{
  int i, j;
  for (j = 0; j < 16; j++)
  {
    lcd_address(j + 1, 0);
    for (i = 0; i < 128; i++)
    {
      transfer_data(*dp);
      transfer_data(*dp);
      dp++;
    }
  }
}



#define CARD_COUNT 4


//显示单元初始化
void LcdUnitInit(lcdUintDef_t *unit,char page,unsigned char tcolumn,unsigned char *t,unsigned char *c,char MaxLen)
{
	unit->C=c;
	unit->T=t;
	unit->page=page;
	unit->Tcolumn=tcolumn;
	unit->Ccolumn=8*strlen((char const *)unit->T)+unit->Tcolumn;
	unit->MaxLen=MaxLen;
}
//单元状态初始化
void LcdUnitStateInit(lcdUintDef_t *unit,char states)
{
	unit->state[0]=states;
	unit->state[1]=states;
}
//单元状态更新
void LcdUnitStateUpdate(lcdUintDef_t *unit,char state)
{
	unit->state[0]=state;
}
//单元显示标题修改
void LcdUnitTitleUpdate(lcdUintDef_t *unit,unsigned char *t)
{
	unit->T=t;
}
//单元显示内容更新
void LcdUnitContentUpdate(lcdUintDef_t *unit,unsigned char *c)
{
	unit->C=c;
}
//单元显示内容列坐标
void LcdUnitCcolumnUpdate(lcdUintDef_t *unit)
{
	unit->Ccolumn=8*strlen((char const *)unit->T)+unit->Tcolumn;
}
//检测单元内容有没有改变 并执行改变回掉函数(带参数)
void LcdUnitStateCheck(lcdUintDef_t *unit,void (*cailback)(uint32_t p),uint32_t input)
{
	if(unit->state[0]!=unit->state[1])
	{
		cailback(input);
	}
	unit->state[1]=unit->state[0];
}
//检测单元内容有没有改变 并执行改变回掉函数(不带参数)
void LcdUnitStateCheckN(lcdUintDef_t *unit,void (*cailback)(void))
{
	if(unit->state[0]!=unit->state[1])
	{
		cailback();
	}
	unit->state[1]=unit->state[0];
}
//单元显示
void LcdUnitDisplay(lcdUintDef_t *unit)
{
	display_string_8x16_16x16(unit->page,unit->Tcolumn,unit->T);//标题
	display_string_8x16_16x16(unit->page,unit->Ccolumn,unit->C);//内容
}
//---------------//
//用于存放lcd显示的ip地址 和对应的位置坐标
lcdUintDef_t InfoTitle;//标题
lcdUintDef_t CARD[CARD_COUNT];//四个板卡
lcdUintDef_t Pw[2];//电源
lcdUintDef_t fan;//风扇
lcdUintDef_t tmp;////温度
//单元参数初始化
//消息界面初始化
void LcdInfoInit(void)
{
	/*
			"CARD	  tmp:   "
			"1:       2:     "
			"3:       4:     "
			"5:       6:     "
			"Power			 "
			"Pw1: ok  Pw2: ok"
			"Pw1: ok  Pw2: ok"
			"Fan: ok  tmp: ok"
		*/
	//-----------------------------（1-16)---(0||CHAR_COLUMN*9)-------------------------------//
	//----------unit----------------page----Tcolumn---------titleChar-----------char----maxlen//
	LcdUnitInit(&InfoTitle			,1		,0				,"    HEM-SWT     "	,""		,16*CHAR_COLUMN);

	LcdUnitInit(&CARD[0]			,3		,0				,"1:"				,"..."	,6*CHAR_COLUMN);
	LcdUnitInit(&CARD[1]			,5		,0				,"2:"				,"..."	,6*CHAR_COLUMN);
	LcdUnitInit(&CARD[2]			,7		,0				,"3:"				,"..."	,6*CHAR_COLUMN);
	LcdUnitInit(&CARD[3]			,9		,0				,"4:"				,"..."	,6*CHAR_COLUMN);


	LcdUnitInit(&Pw[0]				,13		,0				,"Pw1:"				,"..."	,6*CHAR_COLUMN);
	LcdUnitInit(&Pw[1]				,13		,CHAR_COLUMN*8	,"Pw2:"				,"..."	,6*CHAR_COLUMN);

	LcdUnitInit(&fan				,15		,0				,"Fan:"				,"..."	,6*CHAR_COLUMN);
	LcdUnitInit(&tmp				,15		,CHAR_COLUMN*8	,"tmp:"				,"..."	,6*CHAR_COLUMN);


	char i;

	for(i=0;i<CARD_COUNT;i++)
	{
		LcdUnitStateInit(&CARD[i],(char)-1);
	}

	for(i=0;i<2;i++)
	{
		LcdUnitStateInit(&Pw[i],(char)-1);
	}

	LcdUnitStateInit(&fan,(char)-1);
	LcdUnitStateInit(&tmp,(char)-1);

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//刷新标题
static void LcdDisplayTitle(void)
{
	//清屏
	clear_partPageScreen(InfoTitle.page,InfoTitle.Tcolumn,sizeof(InfoTitle.T));
	clear_partPageScreen(InfoTitle.page,InfoTitle.Ccolumn,sizeof(InfoTitle.C));
	//title
	LcdUnitDisplay(&InfoTitle);
}
//刷新单板卡状态
static void LcdDisplayCARD(uint32_t ch)
{
	clear_partPageScreen(CARD[ch].page,CARD[ch].Tcolumn,sizeof(CARD[ch].T));
	clear_partPageScreen(CARD[ch].page,CARD[ch].Ccolumn,sizeof(CARD[ch].C));
	LcdUnitDisplay(&CARD[ch]);
}
//刷新所有板卡状态
static void LcdDisplayCardALL(void)
{
	char i;
	for(i=0;i<CARD_COUNT;i++)
	{
		LcdDisplayCARD(i);
	}
}
//刷新电源Ok状态
static void LcdDisplayPower(uint32_t ch)
{
	clear_partPageScreen(Pw[ch].page,Pw[ch].Tcolumn,sizeof(Pw[ch].T));
	clear_partPageScreen(Pw[ch].page,Pw[ch].Ccolumn,sizeof(Pw[ch].C));
	LcdUnitDisplay(&Pw[ch]);
}

//刷新风扇
static void LcdDisplayFan(void)
{
	//清屏
	clear_partPageScreen(fan.page,fan.Tcolumn,sizeof(fan.T));
	clear_partPageScreen(fan.page,fan.Ccolumn,sizeof(fan.C));
	//风扇
	LcdUnitDisplay(&fan);
}
//刷新 温度
static void LcdDisplayTmp(void)
{
	//清屏
	clear_partPageScreen(tmp.page,tmp.Tcolumn,sizeof(tmp.T));
	clear_partPageScreen(tmp.page,tmp.Ccolumn,sizeof(tmp.C));
	//温度
	LcdUnitDisplay(&tmp);
}
//刷新全部消息界面
void LcdDisplayALL(void)
{
	char i;
	//清屏
	clear_screen();
	//title
	LcdUnitDisplay(&InfoTitle);
	//state
	for(i=0;i<CARD_COUNT;i++)
		{
			LcdUnitDisplay(&CARD[i]);
		}
	//powerOK
	for(i=0;i<2;i++)
		{
			LcdUnitDisplay(&Pw[i]);
		}
	//风扇
	LcdUnitDisplay(&fan);
	//温度
	LcdUnitDisplay(&tmp);
}



///////////////////////////////////////////////////////////////////////////
//消息状态更新
void LcdCardStateUpdate(uint32_t ch,unsigned char * buf,uint8_t state)
{
	LcdUnitStateUpdate(&CARD[ch],state);
	LcdUnitContentUpdate(&CARD[ch],buf);
}
////////////////////////////////////////////////////////////////////////////
//温度状态更新
void LcdTmpStateUpdate(unsigned char * buf,uint8_t state)
{
	LcdUnitStateUpdate(&tmp,state);
	LcdUnitContentUpdate(&tmp,buf);
	LcdTmpStateDisplay();
}

////////////////////////////////////////////////////////////////////////////
//电源ok状态更新
void LcdPowerStateUpdate(uint32_t ch,unsigned char * buf,uint8_t state)
{
	LcdUnitStateUpdate(&Pw[ch],state);
	LcdUnitContentUpdate(&Pw[ch],buf);
}

////////////////////////////////////////////////////////////////////////////
//风扇状态更新
void LcdFanStateUpdate(unsigned char * buf,uint8_t state)
{
	LcdUnitStateUpdate(&fan,state);
	LcdUnitContentUpdate(&fan,buf);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//温度
////////////////////////////////////////////////////////////////
void LcdTmpStateDisplay(void)
{
	LcdUnitStateCheckN(&tmp,&LcdDisplayTmp);

}
/////////////////////////////////////////////////////////////////
//风扇
////////////////////////////////////////////////////////////////
void LcdFanStateDisplay(void)
{
	LcdUnitStateCheckN(&fan,&LcdDisplayFan);

}
////////////////////////////////////////////////////////////////
//四块板卡
///////////////////////////////////////////////////////////////
void LcdCardStateDisplay(void)
{
	int i;
	for(i=0;i<CARD_COUNT;i++)
	{
		LcdUnitStateCheck(&CARD[i],&LcdDisplayCARD,i);
	}
}
////////////////////////////////////////////////////////////////////
//电源OK状态更新
void LcdPowerStateDisplay(void)
{
	int i;
	for(i=0;i<2;i++)
	{
		LcdUnitStateCheck(&Pw[i],&LcdDisplayPower,i);
	}
}

//屏幕io初始化
//屏幕ic初始化
//屏幕显示
void lcd_init(void)
{
	initial_lcd();
	LcdInfoInit();
	LcdDisplayALL();
}
