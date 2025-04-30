/*
 * hw_def.h
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_

//하드웨어 폴더에서 만드는 모듈들에서 공통으로 사용하는것들, 앞으로 하드웨어모듈을 작성할때 이 hw_def.h 만 include 하면 된다.
#include "def.h"
#include "bsp.h"


#define _USE_HW_RTC
#define _USE_HW_USB
#define _USE_HW_RESET
#define _USE_HW_CDC
#define _USE_HW_FLASH
#define _USE_DEBUG_STLINK
#define HW_DEBUG_BUFFER_SIZE    128

#define _USE_HW_LED
#define      HW_LED_MAX_CH           4

#define _USE_HW_UART
#define      HW_UART_MAX_CH          2

#define _USE_HW_CLI
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    32



#endif /* SRC_HW_HW_DEF_H_ */
