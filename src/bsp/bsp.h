/*
 * bsp.h
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */

#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_


#include "def.h"

#define _USE_LOG_PRINT 1


#if _USE_LOG_PRINT
#define logPrintf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define logPrintf(fmt, ...)
#endif
//void ITM_SendChar(uint8_t ch);
//void Debug_Print(const char *msg);
//void SWO_printf(const char *fmt, ...);
#include "stm32f4xx_hal.h"



void bspInit(void);
//void debugInit(void);
void delay(uint32_t ms);
uint32_t millis(void);

void Error_Handler(void);



#endif /* SRC_BSP_BSP_H_ */
