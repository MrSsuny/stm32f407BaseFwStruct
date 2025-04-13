/*
 * ap.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */


#include "ap.h"


#define PID4 (*(volatile uint32_t*)0xE0000FD0)
#define PID5 (*(volatile uint32_t*)0xE0000FD4)
#define PID6 (*(volatile uint32_t*)0xE0000FD8)
#define PID7 (*(volatile uint32_t*)0xE0000FDC)
#define PID0 (*(volatile uint32_t*)0xE0000FE0)
#define PID1 (*(volatile uint32_t*)0xE0000FE4)
#define PID2 (*(volatile uint32_t*)0xE0000FE8)
#define PID3 (*(volatile uint32_t*)0xE0000FEC)
#define CID0 (*(volatile uint32_t*)0xE0000FF0)
#define CID1 (*(volatile uint32_t*)0xE0000FF4)
#define CID2 (*(volatile uint32_t*)0xE0000FF8)
#define CID3 (*(volatile uint32_t*)0xE0000FFC)

// DWT PID 레지스터
#define DWT_PID0 (*(volatile uint8_t*)0xE0001FE0)
#define DWT_PID1 (*(volatile uint8_t*)0xE0001FE4)
#define DWT_PID2 (*(volatile uint8_t*)0xE0001FE8)
#define DWT_PID3 (*(volatile uint8_t*)0xE0001FEC)

// TPIU PID 레지스터
#define TPIU_PID0 (*(volatile uint8_t*)0xE0040FE0)
#define TPIU_PID1 (*(volatile uint8_t*)0xE0040FE4)
#define TPIU_PID2 (*(volatile uint8_t*)0xE0040FE8)
#define TPIU_PID3 (*(volatile uint8_t*)0xE0040FEC)


void print_peripheral_id(void)
{
  uartPrintf(_DEF_UART2,"ITM PID0 = 0x%02X\n", *((volatile uint8_t*)0xE0000FE0)); // = 0x1B
  uartPrintf(_DEF_UART2,"ITM PID1 = 0x%02X\n", *((volatile uint8_t*)0xE0000FE4)); // = 0x90
  uartPrintf(_DEF_UART2,"ITM PID2 = 0x%02X\n", *((volatile uint8_t*)0xE0000FE8)); // = 0x3B
  uartPrintf(_DEF_UART2,"ITM PID3 = 0x%02X\n", *((volatile uint8_t*)0xE0000FEC)); // = 0x00

  // DWT PID 출력
  uartPrintf(_DEF_UART2,"DWT PID0 = 0x%02X\n", DWT_PID0); // 보통 0x0B
  uartPrintf(_DEF_UART2,"DWT PID1 = 0x%02X\n", DWT_PID1); // 보통 0x00
  uartPrintf(_DEF_UART2,"DWT PID2 = 0x%02X\n", DWT_PID2); // 보통 0x1B
  uartPrintf(_DEF_UART2,"DWT PID3 = 0x%02X\n", DWT_PID3); // 보통 0x00

  // TPIU PID 출력
  uartPrintf(_DEF_UART2,"TPIU PID0 = 0x%02X\n", TPIU_PID0); // 보통 0x03
  uartPrintf(_DEF_UART2,"TPIU PID1 = 0x%02X\n", TPIU_PID1); // 보통 0x90
  uartPrintf(_DEF_UART2,"TPIU PID2 = 0x%02X\n", TPIU_PID2); // 보통 0x27
  uartPrintf(_DEF_UART2,"TPIU PID3 = 0x%02X\n", TPIU_PID3); // 보통 0x00

//
//  uartPrintf(_DEF_UART2,"PID[0..7] = %02X %02X %02X %02X %02X %02X %02X %02X\r\n",
//         PID0 & 0xFF, PID1 & 0xFF, PID2 & 0xFF, PID3 & 0xFF,
//         PID4 & 0xFF, PID5 & 0xFF, PID6 & 0xFF, PID7 & 0xFF);
//
//  uartPrintf(_DEF_UART2,"CID[0..3] = %02X %02X %02X %02X\r\n",
//         CID0 & 0xFF, CID1 & 0xFF, CID2 & 0xFF, CID3 & 0xFF);
}


void apInit(void)
{
  uartOpen(_DEF_UART1,115200); //USB
  uartOpen(_DEF_UART2,115200); //UART
}
extern uint32_t sof_count;
//extern print_ITM_DWT_TPIU_PID();      // PID0~3 출력 확인
void apMain(void)
{
  uint32_t pre_time;
  uint8_t rx_buf[128];
  uint32_t rx_len;
  pre_time = millis();
  //uartPrintf(_DEF_UART3,"Debug Start\n");
  //print_peripheral_id();
  //print_ITM_DWT_TPIU_PID();
  while(1)
  {
    if(millis()-pre_time >= 2000)
    {
      pre_time = millis();
      ledToggle(0); //led channel은 0으로 가정
      //uartPrintf(_DEF_UART2,"sof_count:%d\n",sof_count);
      //printf("Debug:%d\n",sof_count);
      //uartPrintf(_DEF_UART3,"Debug:%d\n",pre_time);
    }

    if(uartGetBaud(_DEF_UART1) != uartGetBaud(_DEF_UART2))
    {
        uartOpen(_DEF_UART2, uartGetBaud(_DEF_UART1));
    }
    //USB -> UART
    rx_len = uartAvailable(_DEF_UART1);
    if(rx_len > 128)
    {
      rx_len = 128;
    }
    if(rx_len > 0)
    {
      //uartPrintf(_DEF_UART3,"1 %d\n",rx_len);
      for(int i = 0;i<rx_len;i++)
      {
        rx_buf[i] = uartRead(_DEF_UART1);
      }
      uartWrite(_DEF_UART2,rx_buf,rx_len);
    }
    //UART -> USB
    rx_len = uartAvailable(_DEF_UART2);
    if(rx_len > 128)
    {
      rx_len = 128;
    }
    if(rx_len > 0)
    {
      //uartPrintf(_DEF_UART3,"2 %d\n",rx_len);
      for(int i = 0;i<rx_len;i++)
      {
        rx_buf[i] = uartRead(_DEF_UART2);
      }
      uartWrite(_DEF_UART1,rx_buf,rx_len);
    }

  }
}
