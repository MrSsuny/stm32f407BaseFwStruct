/*
 * bsp.c
 *
 *  Created on: Mar 30, 2025
 *      Author: 2005b
 */

#include "bsp.h"
//typedef struct
//{
//  __IOM uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
//  __OM  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
//  __IOM uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
//  __IOM uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
//} CoreDebug_Type;

#define ITM_ENA   (*(volatile uint32_t*)0xE0000E00) // ITM Enable
//#define ITM_TPR   (*(volatile uint32_t*)0xE0000E40) // Trace Privilege
//                                                        // Register
//#define ITM_TCR   (*(volatile uint32_t*)0xE0000E80) // ITM Trace Control Reg.
#define ITM_LSR   (*(volatile unsigned int*)0xE0000FB0)
//                                                        // Register
//#define DHCSR     (*(volatile uint32_t*)0xE000EDF0) // Debug register
//#define DEMCR     ((*(volatile uint32_t*)0xE000EDFC)) // Debug register
//#define TPIU_ACPR (*(volatile uint32_t*)0xE0040010) // Async Clock
//                                                        // prescaler register
//#define TPIU_SPPR (*(volatile uint32_t*)0xE00400F0) // Selected Pin Protocol
//                                                        // Register
//#define DWT_CTRL  (*(volatile uint32_t*)0xE0001000) // DWT Control Register
//#define FFCR      (*(volatile uint32_t*)0xE0040304) // Formatter and flush
//                                                        // Control Register
uint32_t _ITMPort  = 0; // The stimulus port from which SWO data is received
                   // and displayed.
uint32_t TargetDiv = 1; // Has to be calculated according to
                   // the CPU speed and the output baud rate
void SystemClock_Config(void);

void ITM_Config(void) {
//    // ITM 및 DWT 활성화
//    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
//
//    // 타임스탬프 카운터 초기화
//    DWT->CYCCNT = 0;
//
//    // ITM 제어 레지스터 설정
//    ITM->TCR = ITM_TCR_ITMENA_Msk |  // ITM 활성화
//               ITM_TCR_TSENA_Msk |   // 타임스탬프 활성화
//               ITM_TCR_SWOENA_Msk;   // SWO 출력 활성화
//
//    // 타임스탬프 프리스케일러 설정 (옵션)
//    ITM->TPR = (1U << ITM_TPR_PRIVMASK_Pos);  // 프리스케일러 설정 (옵션)
//
//    // 타임스탬프 카운터 클럭 소스를 SWV 클럭으로 설정
//    TPI->ACPR = (SystemCoreClock / SWV_BAUDRATE) - 1;  // SWV 클럭 설정
//    TPI->SPPR = 2;  // SWO 프로토콜을 NRZ (Non-Return-to-Zero)로 설정
//    TPI->FFCR = 0x100;  // 포맷터 및 플러시 제어 레지스터 설정
}
void _EnableSWO();
void SWO_Init(uint32_t cpuCoreFreqHz, uint32_t swoSpeedHz);
void CoreSight_Debug_Init(void)
{
  // 1. Enable trace system globally
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  // 2. Unlock ITM (and others possibly)
  *((volatile uint32_t*)0xE0000FB0) = 0xC5ACCE55; // ITM->LAR

  // 3. (Optional) DWT unlock if protected - 보통은 생략 가능
  // *((volatile uint32_t*)0xE0001FB0) = 0xC5ACCE55; // Hypothetical DWT->LAR

  // 4. (Optional) TPIU unlock - 일부 MCU에서는 필요할 수 있음
  // *((volatile uint32_t*)0xE0040FB0) = 0xC5ACCE55;
}

void bspInit(void)
{
  HAL_Init();
  SystemClock_Config();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  //debugInit();
  //_EnableSWO();
  //CoreSight_Debug_Init();        // 위 함수 호출
  //print_ITM_DWT_TPIU_PID();      // PID0~3 출력 확인
  //SWO_Init(SystemCoreClock, 2000000); // 2Mbps SWO 속도 설정
  //ITM_Config();

}
//int _write(int file, char *ptr, int len)
//{
//  for(int i = 0; i < len; i++)
//  {
//    //HAL_UART_Transmit(&huart3, (uint8_t*)ptr, len, HAL_MAX_DELAY);
//    ITM_SendChar(*ptr++);
//  }
//  return len;
//}
void _EnableSWO() {
  uint32_t swoSpeedHz = 2000000; //2Mhz
  uint32_t StimulusRegs;
  //
  // Enable access to SWO registers
  //
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  ITM->LAR = 0xC5ACCE55;
  // Initially disable ITM and stimulus port
  // To make sure that nothing is transferred via SWO
  // when changing the SWO prescaler etc.
  StimulusRegs = ITM_ENA;              // 현재 활성 포트 읽음
  StimulusRegs &= ~(1 << _ITMPort);    // 포트 0 비활성화
  // 포트 0 활성화
  ITM->TER = StimulusRegs;              // 적용
  ITM->TCR = 0;                         // ITM 비활성화
  //참고
  //ITM->TCR = ITM_TCR_ITMENA_Msk     // [0]    : ITM 기능 전체 Enable
  //         | ITM_TCR_SWOENA_Msk     // [4]    : SWO 출력 Enable
  //         | ITM_TCR_DWTENA_Msk     // [3]    : DWT 이벤트 Enable
  //         | ITM_TCR_SYNCENA_Msk;   // [2]    : SYNC 패킷 출력 Enable
  //
  // Initialize SWO (prescaler, etc.)
  //
  TPI->SPPR = 0x00000002; // Select NRZ mode
  TPI->ACPR = (SystemCoreClock / swoSpeedHz) - 1; // Set SWO clock
  //DWT, Formatter 설정
  ITM->TPR = 0x00000000;         // Trace Privilege 설정 (권한 제한 없음)
  DWT->CTRL = 0x400003FE;        // DWT 기능 활성화 (Cycle counter 등)

  TPI->FFCR = 0x00000100;            // 포맷터 설정 (SYNC 포함)// 비연속 모드 설정 (SYNC 포함 → 디버거 호환 ↑)
  //ITM 및 포트 재활성화
  //
  // Enable ITM and stimulus port
  //
  //ITM->TCR = 0x1000D;                   // ITM 활성화 (SWOENA, ITMENA, DWTENA 등)
  //ITM->TCR |= ITM_TCR_SYNCENA_Msk; //동기 패킷(Sync Packet) 출력을 활성화,// 디버깅 도구를 위한 동기화 패킷 전송 허용

  ITM->TCR = ITM_TCR_ITMENA_Msk
           | ITM_TCR_SYNCENA_Msk
           | ITM_TCR_DWTENA_Msk
           | ITM_TCR_SWOENA_Msk;
  ITM->TER = StimulusRegs | (1 << _ITMPort); // 포트 0 활성화 Enable ITM stimulus port
}
void SWO_Init(uint32_t cpuCoreFreqHz, uint32_t swoSpeedHz)
{
  // 1. Enable TRC (Trace) in DEMCR
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  // 2. Set SWO speed via TPIU Asynchronous Clock Prescaler Register (ACPR)
  TPI->ACPR = (cpuCoreFreqHz / swoSpeedHz) - 1;

  // 3. Set SWO protocol to NRZ (UART, async mode)
  TPI->SPPR = 0x00000002;

  // 4. Set Formatter and Flush Control Register
  TPI->FFCR = 0x00000100;  // Disable continuous formatting (enable sync packets)

  // 5. Unlock ITM (write key to LAR)
  ITM->LAR = 0xC5ACCE55;

  // 6. Enable ITM with DWT and Sync
  ITM->TCR = ITM_TCR_ITMENA_Msk
           | ITM_TCR_SYNCENA_Msk
           | ITM_TCR_DWTENA_Msk
           | ITM_TCR_SWOENA_Msk;

  // 7. Enable stimulus port 0
  ITM->TER = (1UL << 0);
}
void debugInit(void)
{
//  //CoreDebug 및 TPIU 설정
//  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // TRCENA 활성화
//  TPI->ACPR = (SystemCoreClock / 2000000) - 1; // SWO 클록 설정 (2Mbps)
//  TPI->SPPR = 2; // 프로토콜 설정 (NRZ/UART)
//  TPI->FFCR = 0x100; // ITM 포맷팅 활성화
//  //ITM 설정
//
//  ITM->LAR = 0xC5ACCE55; // ITM 잠금 해제
//  ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_DWTENA_Msk | ITM_TCR_SYNCENA_Msk;
//  ITM->TER = 0x1; // 스티뮬러스 포트 0 활성화
  //트레이스 클럭 설정:

  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // Enable TRCENA
  TPI->ACPR = (SystemCoreClock / 2000000) - 1; // Set SWO clock
  //TPI->ACPR = (SystemCoreClock / 4000) - 1; // Set SWO clock
  //ITM 설정:

  ITM->LAR = 0xC5ACCE55; // Unlock ITM
  //ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SWOENA_Msk;
  ITM->TCR = ITM_TCR_ITMENA_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_DWTENA_Msk | ITM_TCR_SYNCENA_Msk;
  ITM->TER = 0x1; // Enable stimulus port 0
  //SWO 설정:

  TPI->SPPR = 2; // Protocol: Manchester encoding, 프로토콜 설정 (NRZ/UART)
  TPI->FFCR = TPI_FFCR_EnFCont_Msk; // Continuous formatting, ITM 포맷팅 활성화
}

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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
/*void assert_failed(uint8_t *file,uint32_t line)
{
  printf("Wron %s %d \r\n",file, line);
}*/
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
