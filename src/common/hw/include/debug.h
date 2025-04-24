/*
 * debug.h
 *
 *  Created on: Apr 17, 2025
 *      Author: 2005b
 */

#ifndef SRC_COMMON_HW_INCLUDE_DEBUG_H_
#define SRC_COMMON_HW_INCLUDE_DEBUG_H_

#include "hw_def.h"

#ifdef _USE_DEBUG_STLINK

#define DEBUG_BUFFER_SIZE            HW_DEBUG_BUFFER_SIZE    //이렇게  해놓고 실제로 몇개의 LED를 사용할수 있는지를 hw_def.h 에서 HW_LED_MAX_CH에서 선언해주면 쉽다.


bool debugInit(void);  //초기화 함수
void debugPrint(const char *fmt, ...);





#endif

#endif /* SRC_COMMON_HW_INCLUDE_DEBUG_H_ */
