#include "main.h"



void bsp_init(void)
{
  bsp_nvicInit();
  bsp_sysctlInit();
  bsp_gpioInit();
  bsp_i2cInit();
  bsp_spiInit();
  bsp_uartInit();
  bsp_timerInit();
  bsp_intEnable();
}


void system_init(void)
{
  bsp_init();
  lwipTask_init();
}
xTaskHandle test1;
xTaskHandle test;
extern uint8_t conntectFlag;
uint8_t buf[]={0xAA,0x7E,0x00,0x00,0x09,0x00,0x00,0x00,0x88,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0xFE,0x00,0x00};
extern serverInfo_t  serverInfo[10];
void test_task(void * pvParameters)
{
  uint32_t LastCount;
  int a=0;u8_t num;
  LastCount=xTaskGetTickCount ();
  Tcp_Client_Init();
  err_t err;
  while(1)
  {
   
    
    if(serverInfo[a].states==start)
      {
        err=tcp_client_connect(&serverInfo[a]);
        serverInfo[a].outtime=200;
        serverInfo[a].states=idle;
      }
      else if(serverInfo[a].states==idle)
      {
        if(serverInfo[a].connect==connected)
        {
          serverInfo[a].states=send;
        }
        else
        {
            if(serverInfo[a].outtime==0)
          {
            serverInfo[a].states=start;
          }
        }
      }
    
      if(serverInfo[a].states==send)
      {
        err=tcp_write(serverInfo[a].pcb, buf,56,1);
        if(err!=ERR_OK)
        {
          serverInfo[a].connect=connecting;
          serverInfo[a].states=start;
        }
        err=tcp_output(serverInfo[a].pcb);
        if(err!=ERR_OK)
        {
          serverInfo[a].connect=connecting;
          serverInfo[a].states=start;
        }
        else
        {
          serverInfo[a].states=recwait;
          serverInfo[a].outtime=200;
        }
      }
      else if(serverInfo[a].states==recwait)
      {
        
        if(serverInfo[a].outtime==0)
        {
          serverInfo[a].states=idle;
        }
        else 
        {
          serverInfo[a].states=reced;
        }
      }
      else if(serverInfo[a].states==reced)
      {
        serverInfo[a].states=idle;
      }
    
    a++;
    if(a==10)
    {
      a=0;
    }
     for(num=0;num<10;num++)
    {
      if(serverInfo[num].outtime!=0)
      serverInfo[num].outtime--;
    }
    vTaskDelayUntil(&LastCount,10/portTICK_RATE_MS);
  }
}

void test1_task(void * pvParameters)
{
  uint32_t LastCount; u8_t num;
  LastCount=xTaskGetTickCount ();
  while(1)
  {
    for(num=0;num<10;num++)
    {
      if(serverInfo[num].outtime!=0)
      serverInfo[num].outtime--;
    }
    vTaskDelayUntil(&LastCount,10/portTICK_RATE_MS);
  }
}




int main()
{
  
  system_init();

  UARTprintf("Lwip Test!!\r\n");
  xTaskCreate(test_task,"test",128,NULL,(UBaseType_t)2,&test);
 // xTaskCreate(test1_task,"test1",128,NULL,(UBaseType_t)3,&test1);
  vTaskStartScheduler();
  while(1)
  {

  }
}
