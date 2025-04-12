/*
 * reset.h
 *
 *  Created on: Apr 7, 2025
 *      Author: 2005b
 */

#ifndef SRC_COMMON_HW_INCLUDE_RESET_H_
#define SRC_COMMON_HW_INCLUDE_RESET_H_

#include "hw_def.h" //하드웨어 관련된 정의가 들어있는 헤더 추가

#ifdef _USE_HW_RESET

bool resetInit(void);

uint32_t resetGetCount(void);

#endif

#endif /* SRC_COMMON_HW_INCLUDE_RESET_H_ */
