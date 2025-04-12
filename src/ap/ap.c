/*
 * ap.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */


#include "ap.h"




void apInit(void)
{
  uartOpen(_DEF_UART1,115200);
  uartOpen(_DEF_UART2,115200);
}

void apMain(void)
{
  uint32_t pre_time;
//  uint32_t pre_baud;
//  uint32_t led_blink_time = 500;
//  uint8_t led_ch = 0;
//  uint8_t reset_count = resetGetCount();
//  if(reset_count >= 2)
//  {
//    led_blink_time = 100;
//  }
//  led_ch = reset_count % 4;
//  pre_baud = uartGetBaud(_DEF_UART1);
  //uartPrintf(_DEF_UART1,"USB\n");
  pre_time = millis();
  while(1)
  {
    if(millis()-pre_time >= 500)
    {
      pre_time = millis();
      //uartPrintf(_DEF_UART1,"USB\n");
      ledToggle(0); //led channel은 0으로 가정
      //uartPrintf(_DEF_UART1,"Uart1 %d\n",millis());
      //uartPrintf(_DEF_UART2,"Uart2 %d\n",millis());
    }
    if(uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;
      rx_data = uartRead(_DEF_UART1);
      uartPrintf(_DEF_UART1,"USB Rx %c %x\n",rx_data,rx_data);
    }
    if(uartAvailable(_DEF_UART2) > 0)
    {
      uint8_t rx_data;
      rx_data = uartRead(_DEF_UART2);
      uartPrintf(_DEF_UART2,"Uart1 Rx %c %x\n",rx_data,rx_data);
    }

//    if(millis()-pre_time >=led_blink_time)
//    {
//      pre_time = millis();
//      ledToggle(led_ch); //led channel은 0으로 가정
//     // uartPrintf(_DEF_UART1,"ResetCount : %d\n",reset_count);
//    }
   /* if(uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;
      rx_data = uartRead(_DEF_UART1);
      uartPrintf(_DEF_UART1,"RxData : %c 0x%X\n",rx_data,rx_data);
    }
    if(uartGetBaud(_DEF_UART1) != pre_baud)
    {
      pre_baud = uartGetBaud(_DEF_UART1);
      uartPrintf(_DEF_UART1, "ChangedBaud : %d\n", uartGetBaud(_DEF_UART1));

    }*/
  }
}
