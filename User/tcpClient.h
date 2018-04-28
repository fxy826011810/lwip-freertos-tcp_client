#ifndef __TCPCLIENT_H
#define __TCPCLIENT_H

#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#define  MAX_NAME_SIZE       32

struct name
{
        int     length;
        char    bytes[MAX_NAME_SIZE];
};

typedef struct {
  struct tcp_pcb *pcb;
  u8_t num;
  u16_t ip4port;
  u16_t ip4portLocal;
  u16_t outtime;
  err_t err;
  struct ip_addr ipaddr;
  enum{
    start,
    idle,
    wait,
    send,
    recwait,
    reced,
  }states;
  enum{
    connected,
    connecting,
  }connect;
}serverInfo_t;

void Tcp_Client_Init(void);
err_t tcp_client_connected(void *arg, struct tcp_pcb *pcb, err_t err);
err_t tcp_client_connect(serverInfo_t *info);

#endif //__BSP__H
