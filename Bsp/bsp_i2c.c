#include "main.h"



void bsp_i2cInit(void)
{
  ROM_I2CMasterInitExpClk(I2C0_BASE,g_ui32SysClock,true);
  ROM_I2CMasterEnable(I2C0_BASE);
}


unsigned char I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr)
{
  uint8_t value=0;
  while(ROM_I2CMasterBusy(I2C0_BASE));
  //ָ�����豸��ַ  ��
  ROM_I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, false);
  //���ͼĴ�����ַ
  ROM_I2CMasterDataPut(I2C0_BASE, RegAddr);
  ROM_I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_SEND);
  ROM_SysCtlDelay((g_ui32SysClock/3000000)*4);
  while(ROM_I2CMasterBusy(I2C0_BASE));
  //���ܴ��豸���͵�����
  ROM_I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, true);
  ROM_I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_RECEIVE );
  ROM_SysCtlDelay((g_ui32SysClock/3000000)*4);
  while(ROM_I2CMasterBusy(I2C0_BASE));
  value=ROM_I2CMasterDataGet(I2C0_BASE);
  return value;
}

uint8_t IICreadBytes(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp)
{
  uint8_t i,addr=RegAddr;
  for(i=0;i<ReadNum;i++)
  {
    *ReadTemp=I2C_ReadOneByte(DevAddr,addr);
    addr++;
    ReadTemp++;
  }
  return 0;
}

uint8_t IICwriteByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData)
{

  uint8_t rop=0;
  while(ROM_I2CMasterBusy(I2C0_BASE))
  {
  //wait until bus is not busy
  }
  //ָ�����豸��ַ  д
  ROM_I2CMasterSlaveAddrSet(I2C0_BASE, DevAddr, false);
  //��Ҫ���͵ĵ�ַ���͵�������
  ROM_I2CMasterDataPut(I2C0_BASE, RegAddr);
  // ��ʼ����豸���͵�ַ
  ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  ROM_SysCtlDelay((g_ui32SysClock/3000000)*4);
  //��ɴ���ǰ�ȴ�
  while(ROM_I2CMasterBusy(I2C0_BASE));
  //��Ҫ���͸����豸�����ݷ��͵�������
  ROM_I2CMasterDataPut(I2C0_BASE, WriteData);
  // ��ʼ����豸��������
  ROM_I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
  ROM_SysCtlDelay((g_ui32SysClock/3000000)*10);
  //��ɴ���ǰ�ȴ�
  while(ROM_I2CMasterBusy(I2C0_BASE));
  //���I2C�����Ƿ����
  rop = ROM_I2CMasterErr(I2C0_BASE);
  return rop;
}
