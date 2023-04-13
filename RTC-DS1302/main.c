#include "stm8s.h"
#include "ds1302.h"
#include "uart.h"

void SystemInit_CLK(void);

void main(void)
{
  // 数据显示区（十进制）
  // 初始值：2022.02.25 Fri. 01:59:50
  TimeTypeDef TimeDisplay = {22, 02, 25, 5, 01, 59, 50};  
  uint8_t TimeSecPre;
  
  SystemInit_CLK();
  UART2_Config();
  DS1302_Init();
  
  printf("Init Success!\r\n");
  
#if RTC_RESET_TIME_EN > 0u
  DS1302_WriteTime(&TimeDisplay);
#endif
  
  while (1)
  {
    TimeDisplay = DS1302_ReadTime();
    if (TimeSecPre != TimeDisplay.second)
    {
      TimeSecPre = TimeDisplay.second;
      printf("20%d年%d月%d日 星期%d\r\n", TimeDisplay.year, TimeDisplay.month, TimeDisplay.day, 
             TimeDisplay.week);
      printf("%d时%d分%d秒\r\n", TimeDisplay.hour, TimeDisplay.minute, TimeDisplay.second);
      printf("\r\n");
    }
  }
}

void SystemInit_CLK(void)
{
  CLK_DeInit();
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  CLK_HSICmd(ENABLE);
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

