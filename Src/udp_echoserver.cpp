#include "udp_echoserver.h"
#include "ethernetif.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/udp.h"
//#include "ethernetif.h"


#define SERVER_PORT 5005

// Reference: https://lists.nongnu.org/archive/html/lwip-users/2007-06/msg00078.html

extern "C" struct netif *netif_default; // from Middlewares/Third_Party/LwIP/src/include/lwip/netif.h

namespace
{
  struct udp_pcb *pcb_;
  int i = 0;
  struct pbuf *p_;

  uint32_t current_pbuf_idx = 0;
  struct pbuf_custom rx_pbuf[ETH_RX_DESC_CNT];
  //struct pbuf_custom rx_pbuf;

  void udp_echo_recv(void *arg, struct udp_pcb *tpcb, struct pbuf *p,
                     const ip_addr_t *addr, uint16_t port)
  {
    if (p != NULL) {
      /* send received packet back to sender */

      p_ = pbuf_alloc(PBUF_TRANSPORT, sizeof(char) * p->len, PBUF_RAM);
      p_->payload = p->payload;
      udp_sendto(tpcb, p_, addr, port);
      pbuf_free(p_);       /* necessary: free the pbuf */

      p_ = pbuf_alloc(PBUF_TRANSPORT, sizeof(int), PBUF_RAM);
      i++;
      p_->payload = &i;
      udp_sendto(tpcb, p_, addr, port);
      pbuf_free(p_);  /* necessary: free the pbuf */

      pbuf_free(p);
    }
  }
};

extern "C" void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
#if 1
  err_t err;
  struct pbuf *p = NULL;
  ETH_BufferTypeDef RxBuff;
  uint32_t framelength = 0;

  /* Clean and Invalidate data cache */
  SCB_CleanInvalidateDCache();

  HAL_ETH_GetRxDataBuffer(heth, &RxBuff);
  HAL_ETH_GetRxDataLength(heth, &framelength);

  p = pbuf_alloced_custom(PBUF_RAW, framelength, PBUF_POOL, &rx_pbuf[current_pbuf_idx], RxBuff.buffer, framelength);

  if(current_pbuf_idx < (ETH_RX_DESC_CNT -1))
    {
      current_pbuf_idx++;
    }
  else
    {
      current_pbuf_idx = 0;
    }


  /* no packet could be read, silently ignore this */
   if (p == NULL) return;

   /* entry point to the LwIP stack */
   err = netif_default->input(p, netif_default);

   if (err != ERR_OK)
   {
     LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
     pbuf_free(p);
     p = NULL;
   }

  HAL_ETH_BuildRxDescriptors(heth);
#endif

  // Caution: the following command does not work!
  //ethernetif_input(netif_default);
}



void udp_echoserver_init(void)
{
  /* get new pcb */
  pcb_ = udp_new();
  if (pcb_ == NULL) return;

  /* bind to any IP address on port 7 */
  if (udp_bind(pcb_, IP_ADDR_ANY, SERVER_PORT) != ERR_OK)
    {
      memp_free(MEMP_UDP_PCB, pcb_);
      return;
    }

  /* set udp_echo_recv() as callback function
     for received packets */
  udp_recv(pcb_, udp_echo_recv, NULL);

  for(uint32_t idx = 0; idx < ETH_RX_DESC_CNT; idx ++)
   {
     /* Set Custom pbuf free function */
     rx_pbuf[idx].custom_free_function = pbuf_free_custom;
   }
  //rx_pbuf.custom_free_function = pbuf_free_custom;


}
