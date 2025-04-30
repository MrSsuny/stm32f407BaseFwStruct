/*
 * reset.c
 *
 *  Created on: Apr 7, 2025
 *      Author: 2005b
 */


#include "reset.h"
#include "rtc.h"

static uint32_t reset_count = 0;


bool resetInit(void)
{
  bool ret = true;

  //if(RCC->CSR == (1<<26))
  if(RCC->CSR & (1<<26))
  {
    __HAL_RCC_CLEAR_RESET_FLAGS();
    rtcBackupRegWrite(0,rtcBackupRegRead(0)+1);
    delay(500);
    reset_count = rtcBackupRegRead(0);
  }

  rtcBackupRegWrite(0, 0);
  if(reset_count != 2)
  {
    void (**jump_func)() =  (void (**)())(0x8008000 + 4);

    if((uint32_t)(*jump_func) != 0xFFFFFFFF)
    {
      HAL_RCC_DeInit();
      HAL_DeInit();
      for(int i = 0;i<8;i++)
      {
        NVIC->ICER[i]  = 0xFFFFFFFF;
        __DSB();
        __ISB();
      }
      SysTick->CTRL = 0;

      (*jump_func)();
    }
  }
  else
  {

  }
  return ret;
}

uint32_t resetGetCount(void)
{
  return reset_count;
}
