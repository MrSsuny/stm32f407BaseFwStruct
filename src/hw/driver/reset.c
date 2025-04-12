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

  if(RCC->CSR & (1<<26))
  {
    __HAL_RCC_CLEAR_RESET_FLAGS();
    rtcBackupRegWrite(0,rtcBackupRegRead(0)+1);
    delay(15);
    reset_count = rtcBackupRegRead(0);
  }

  rtcBackupRegWrite(0, 0);
  return ret;
}

uint32_t resetGetCount(void)
{
  return reset_count;
}
