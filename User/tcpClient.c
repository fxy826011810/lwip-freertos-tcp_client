#include "tcpClient.h"

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


#if 1
int ip4[10][4]={192,168,2,98,192,168,2,97,\
                192,168,2,96,192,168,2,95,\
                192,168,2,94,192,168,2,93,\
                192,168,2,92,192,168,2,91,\
                192,168,2,90,192,168,2,89};

u16_t ip4port[10]={6000,6000,6000,6000,6000,6000,6000,6000,6000,6000};
#else
int ip4[10][4]={192,168,2,98,192,168,2,98,\
                192,168,2,98,192,168,2,98,\
                192,168,2,98,192,168,2,98,\
                192,168,2,98,192,168,2,98,\
                192,168,2,98,192,168,2,98};
u16_t ip4port[10]={6000,6001,6002,6003,6004,6005,6006,6007,6008,6009};
#endif
u16_t ip4portLocal[10]={6000,6001,6002,6003,6004,6005,6006,6007,6008,6009};

void TcpClose(struct tcp_pcb *pcb);

serverInfo_t  serverInfo[10];

struct ip_addr ipaddr[10];

static err_t
TcpPoll(void *arg, struct tcp_pcb *pcb)
{
  serverInfo_t *info=(serverInfo_t*)arg;
  info->states=idle; 
  return(ERR_OK);    
}
err_t errTcp;
void TcpError(void *arg, err_t err)
{
  serverInfo_t *info=(serverInfo_t*)arg;
  info->err=err;
  if(err!=ERR_OK)
  {
    info->connect=connecting;
    info->states=start;
  }
}

err_t
TcpSent(void *pvArg, struct tcp_pcb *psPcb, u16_t ui16Len)
{
  
    return (ERR_OK);
}

static err_t tcp_client_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *tcp_recv_pbuf, err_t err)
{
  serverInfo_t *info=arg;
  struct pbuf *pbufs;
  info->err=err;
  if(tcp_recv_pbuf==0)
  {
    info->connect=connecting;
    info->states=start;
    return(ERR_OK);
  }
  else if(tcp_recv_pbuf!=0&&err == ERR_OK)
  {
    pbufs=tcp_recv_pbuf;
    while(pbufs->len!=0)
    {
      UARTprintf("rec len=:%d\r\n",pbufs->len);
      tcp_recved(pcb,pbufs->len);
      pbufs=pbufs->next;
       
      if(pbufs==0)
      {
        break;
      }
    }
    info->states=reced;
    pbuf_free(tcp_recv_pbuf);
  }
  
  return ERR_OK;
}




void TcpClose(struct tcp_pcb *pcb)
{
  tcp_close(pcb);
  tcp_arg(pcb, NULL);
  tcp_recv(pcb, NULL);
  tcp_err(pcb, NULL);
  
}

uint8_t conntectFlag=0;
err_t tcp_client_connected(void *arg, struct tcp_pcb *pcb, err_t err)
{
  serverInfo_t *info=arg;
    if(err!=ERR_OK)
  {
     info->states=start;
     info->connect=connecting;
  }

  tcp_err(info->pcb,TcpError);
//  tcp_poll(info->pcb,TcpPoll,(3000 / 500));
  tcp_recv(pcb, tcp_client_recv);
  tcp_sent(pcb, TcpSent);
  info->connect=connected;
  return ERR_OK;
}


void tcp_client_disconnect(serverInfo_t *info)
{
  tcp_close(info->pcb);
  tcp_arg(info->pcb, NULL);
  tcp_recv(info->pcb, NULL);
  tcp_err(info->pcb, NULL);
  info->pcb=NULL;
}


err_t tcp_client_connect(serverInfo_t *info)
{
  err_t err;
  if(info->pcb!=NULL)
  {
    tcp_client_disconnect(info);
  }
  info->pcb=tcp_new();
  tcp_arg(info->pcb,info);
  //tcp_bind(info->pcb,&info->ipaddr,info->ip4portLocal);
  err=tcp_connect(info->pcb,&info->ipaddr,info->ip4port,tcp_client_connected);
  return err;
}

void Tcp_Client_Init(void)
{ 
  int i;
  for(i=0;i<10;i++)
  {
    
    IP4_ADDR(&ipaddr[i], ip4[i][0], ip4[i][1], ip4[i][2], ip4[i][3]);
    serverInfo[i].pcb = NULL;
    serverInfo[i].err=ERR_OK;
    serverInfo[i].num=i;
    serverInfo[i].ip4port=ip4port[i];
    serverInfo[i].ip4portLocal=ip4portLocal[i];
    serverInfo[i].ipaddr=ipaddr[i];
    serverInfo[i].states=start;
    serverInfo[i].connect=connecting;
    serverInfo[i].outtime=50;
  }     
}



