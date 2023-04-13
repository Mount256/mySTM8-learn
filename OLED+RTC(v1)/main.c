#include "stm8s.h"
#include "oled_spi.h"
#include "ds1302.h"
#include "uart.h"

typedef struct TimeStr{
  uint8_t year[5];
  uint8_t month[3];
  uint8_t day[3];
  uint8_t hour[3];
  uint8_t minute[3];
  uint8_t second[3];
}TimeStrTypeDef;

void SystemInit_CLK(void);

void main(void)
{
  // 数据显示区（十进制）
  // 初始值：2022.02.25 Fri. 01:59:50
  TimeTypeDef TimeDisplay = {22, 02, 25, 5, 01, 59, 50};  
  TimeStrTypeDef TimeString = {"2000\0", "01\0", "01\0", "00\0", "00\0", "00\0"};
  uint8_t TimeSecPre;
  
  SystemInit_CLK();
  //UART2_Config();
  OLED_SPI_Init();
  DS1302_Init();
  
  OLED_ShowString(0, 0, "Init Success!", OLED_FONT_SIZE_16);
  OLED_Refresh_Gram();
  
#if RTC_RESET_TIME_EN > 0u
  DS1302_WriteTime(&TimeDisplay);
#endif
  
  while (1)
  {
    
    TimeDisplay = DS1302_ReadTime();
    if (TimeSecPre != TimeDisplay.second)
    {
      TimeSecPre = TimeDisplay.second;
      
      TimeString.year[2] = TimeDisplay.year / 10 + '0';
      TimeString.year[3] = TimeDisplay.year % 10 + '0';
      OLED_ShowString(0, 0, TimeString.year, OLED_FONT_SIZE_16);
      OLED_ShowChinese(8*4, 0, &chinese2_1616[0][0], OLED_FONT_SIZE_16, 1); //“年”
      
      TimeString.month[0] = TimeDisplay.month / 10 + '0';
      TimeString.month[1] = TimeDisplay.month % 10 + '0';
      OLED_ShowString(8*4+16, 0, TimeString.month, OLED_FONT_SIZE_16);
      OLED_ShowChinese(8*4+16+8*2, 0, &chinese2_1616[2][0], OLED_FONT_SIZE_16, 1); //“月”
      
      TimeString.day[0] = TimeDisplay.day / 10 + '0';
      TimeString.day[1] = TimeDisplay.day % 10 + '0';
      OLED_ShowString(8*4+16+8*2+16, 0, TimeString.day, OLED_FONT_SIZE_16);
      OLED_ShowChinese(8*4+16+8*2+16+8*2, 0, &chinese2_1616[4][0], OLED_FONT_SIZE_16, 1); //“日”
      
      TimeString.hour[0] = TimeDisplay.hour / 10 + '0';
      TimeString.hour[1] = TimeDisplay.hour % 10 + '0';
      OLED_ShowString(0, 16, TimeString.hour, OLED_FONT_SIZE_16);
      OLED_ShowChinese(8*2, 16, &chinese2_1616[10][0], OLED_FONT_SIZE_16, 2); //“时”
      
      TimeString.minute[0] = TimeDisplay.minute / 10 + '0';
      TimeString.minute[1] = TimeDisplay.minute % 10 + '0';
      OLED_ShowString(8*2+16, 16, TimeString.minute, OLED_FONT_SIZE_16);
      OLED_ShowChinese(8*2+16+8*2, 16, &chinese2_1616[12][0], OLED_FONT_SIZE_16, 2); //“分”
      
      TimeString.second[0] = TimeDisplay.second / 10 + '0';
      TimeString.second[1] = TimeDisplay.second % 10 + '0';
      OLED_ShowString(8*2+16+8*2+16, 16, TimeString.second, OLED_FONT_SIZE_16);
      OLED_ShowChinese(8*2+16+8*2+16+8*2, 16, &chinese2_1616[14][0], OLED_FONT_SIZE_16, 1); //“秒”
      
      OLED_Refresh_Gram();
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

