/*
 * flash.h
 *
 *  Created on: Apr 14, 2025
 *      Author: 2005b
 */

#ifndef SRC_COMMON_HW_INCLUDE_FLASH_H_
#define SRC_COMMON_HW_INCLUDE_FLASH_H_

#include "hw_def.h"

#ifdef _USE_HW_FLASH


bool flashInit(void);
bool flashErase(uint32_t addr, uint32_t length);
bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length);
bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length);
uint32_t GetSector(uint32_t Address);
#endif


#endif /* SRC_COMMON_HW_INCLUDE_FLASH_H_ */
