/*
 * cdc.h
 *
 *  Created on: Apr 7, 2025
 *      Author: 2005b
 */

#ifndef SRC_COMMON_HW_INCLUDE_CDC_H_
#define SRC_COMMON_HW_INCLUDE_CDC_H_



#include "hw_def.h"


#ifdef _USE_HW_CDC

bool     cdcInit(void);
uint32_t cdcAvailable(void);
uint8_t  cdcRead(void);
void     cdcDatatIn(uint8_t rx_data);
uint32_t cdcWrite(uint8_t *p_data, uint32_t length);
uint32_t cdcGetBaud(void);


#endif


#endif /* SRC_COMMON_HW_INCLUDE_CDC_H_ */
