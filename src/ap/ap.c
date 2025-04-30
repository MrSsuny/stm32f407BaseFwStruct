/*
 * ap.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */


#include "ap.h"




void apInit(void)
{
  uartOpen(_DEF_UART1,115200); //USB
  uartOpen(_DEF_UART2,115200); //UART

  cliOpen(_DEF_UART1, 115200);
  cliOpenLog(_DEF_UART2, 115200);

}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();

  while(1)
  {
    if(millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(0);
      debugPrint("debug printf %d\n", (int)pre_time);
      //logPrintf("printf Test %d\n", (int)pre_time);
      //strlen
      //uartWrite(_DEF_UART3,"printf Test %d\n", (int)pre_time);
    }
    if (uartAvailable(_DEF_UART2) > 0)
    {
      uint8_t rx_data;
      rx_data = uartRead(_DEF_UART2);

      uartPrintf(_DEF_UART2, "Rx : 0x%X\n", rx_data);
    }

    cliMain();
  }
}
