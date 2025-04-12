/*
 * hw.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */


#include "hw.h"

void hwInit(void)
{
  bspInit();
  rtcInit();

  resetInit();
  ledInit();
  usbInit();
  uartInit();
}
