/*
 * bsp.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */

#include "bsp.h"
#include "uart.h"
void SystemClock_Config(void);

//#define SWO_PRINTF_BUFFER_SIZE 256  // 출력 버퍼 크기 설정


void bspInit(void)
{
  HAL_Init();
  SystemClock_Config();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  //debugInit();

}
///* 단일 문자 전송 */
//static inline void SWO_PrintChar(char ch)
//{
//  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&
//      ((ITM->TER & (1UL << 0)) != 0UL))
//  {
//    while (ITM->PORT[0].u32 == 0);
//        ITM->PORT[0].u8 = ch;
////    while ((ITM->TIM[0] & 1UL) == 0UL);
////    ITM->TIM[0] = ch;
//  }
//}
//
///* 문자열 전송 */
//void SWO_PrintString(const char *s)
//{
//  while (*s)
//    SWO_PrintChar(*s++);
//}
//
///* printf 스타일 출력 지원 */
//void SWO_printf(const char *fmt, ...)
//{
//  char buffer[SWO_PRINTF_BUFFER_SIZE];
//
//  va_list args;
//  va_start(args, fmt);
//  vsnprintf(buffer, sizeof(buffer), fmt, args);
//  va_end(args);
//
//  SWO_PrintString(buffer);
//}
//char buffer[SWO_PRINTF_BUFFER_SIZE];
//void log_printf(const char *fmt, ...)
//{
//  //char buffer[SWO_PRINTF_BUFFER_SIZE];
//  va_list args;
//  va_start(args, fmt);
//  int len = vsnprintf(buffer, sizeof(buffer), fmt, args);
//  va_end(args);
//
//  for (size_t i = 0; i < len; i++)
//  {
//    ITM_SendChar(buffer[i]);
//
//  }
//}
//void SWO_SendString_len(const char *s, size_t len)
//{
//  for (size_t i = 0; i < len; i++)
//  {
//    if (s[i] == '\n')
//      SWO_SendChar('\r');
//    SWO_SendChar(s[i]);
//  }
//}
int __io_putchar(int ch)
{
  //USB 로 printf 전송
#ifdef _USE_DEBUG_STLINK
  //ITM_SendChar(ch);
#endif
  uartWrite(_DEF_UART1,(uint8_t *)&ch,1);
  return 1;

}
//uint32_t ITM_SendChar (uint32_t ch) {
//    while (ITM->PORT[0].u32 == 0);
//    ITM->PORT[0].u8 = ch;
//}

//void Debug_Print(const char *msg) {
//  SWO_printf(msg);
////    while (*msg) {
////        ITM_SendChar(*msg++);
////    }
//}
//void debugInit()
//{
//  //CoreDebug 및 TPIU 설정
//
//  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // TRCENA 활성화
//  //TPI->ACPR = (SystemCoreClock / 2000000) - 1; // SWO 클록 설정 (2Mbps)
//  //TPI->SPPR = 2; // 프로토콜 설정 (NRZ/UART)
//  //TPI->FFCR = 0x100; // ITM 포맷팅 활성화
//  //ITM 설정
//
//  ITM->LAR = 0xC5ACCE55; // ITM 잠금 해제
//  ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_DWTENA_Msk | ITM_TCR_SYNCENA_Msk;
//  ITM->TER = 0x1; // 스티뮬러스 포트 0 활성화
//}

void delay(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  printf("Wrong parameters value: file %s on line %d\r\n", file, (int)line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
