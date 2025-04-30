/*
 * ap.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */


#include "ap.h"




void apInit(void)
{
}

void apMain(void)
{
  uint32_t pre_time;

  pre_time = millis();

  while(1)
  {
    if(millis()-pre_time >= 100)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
      //debugPrint("debug printf %d\n", (int)pre_time);
      //logPrintf("printf Test %d\n", (int)pre_time);
      //strlen
      //uartWrite(_DEF_UART3,"printf Test %d\n", (int)pre_time);
    }

  }
}
