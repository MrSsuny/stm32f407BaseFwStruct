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
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();

  while(1)
  {
    if(millis()-pre_time >= 2000)
    {
      pre_time = millis();
      ledToggle(0);
      debugPrint("debug printf %d\n", (int)pre_time);
      //logPrintf("printf Test %d\n", (int)pre_time);
      //strlen
      //uartWrite(_DEF_UART3,"printf Test %d\n", (int)pre_time);
    }
    if(uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;
      rx_data = uartRead(_DEF_UART1);


      if(rx_data == '1')
      {
        uint8_t buf[32];
        flashRead(0x8010000,buf,32);
        for(int i=0; i<32;i++)
        {
          logPrintf("0x%X : 0x%X\n",0x8000000 + 1020*1024 + i, buf[i]);
        }
        //logPrintf("0x%X : 0x%X\n",0x8000000 + 1020*1024 + i, buf[i]);
      }
      if(rx_data == '2')
      {
        logPrintf("Erase...\n");
        if(flashErase(0x8010000, 32) == true)
        {
          logPrintf("Erase OK\n");
        }
        else
        {
          logPrintf("Erase Fail\n");
        }
      }
      if(rx_data == '3')
      {
        uint8_t buf[32];
        for(int i = 0;i<32;i++)
        {
          buf[i] = i;
        }
        logPrintf("Write...\n");
        if(flashWrite(0x8010000 , buf, 32) == true)
        {
          logPrintf("Write OK\n");
        }
        else
        {
          logPrintf("Write Fail\n");
        }
      }
    }
  }
}
