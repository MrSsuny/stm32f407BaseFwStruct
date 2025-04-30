/*
 * debug.c
 *
 *  Created on: Apr 17, 2025
 *      Author: 2005b
 */

#include "debug.h"

#ifdef _USE_DEBUG_STLINK
static char buffer[DEBUG_BUFFER_SIZE];


bool debugInit(void)
{
  bool ret = true;

  return ret;
}

void debugPrint(const char *fmt, ...)
{
  //char buffer[SWO_PRINTF_BUFFER_SIZE];
  va_list args;
  va_start(args, fmt);
  int len = vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  for (size_t i = 0; i < len; i++)
  {
    ITM_SendChar(buffer[i]);
  }
}
#endif
