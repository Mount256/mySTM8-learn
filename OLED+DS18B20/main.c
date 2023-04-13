/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
    
#include "stm8s.h"
#include "ds18b20.h"
#include "oled_spi.h"
#include "timer.h"
#include "uart.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void SystemInit_CLK(void);

// 软件延时
void Delay_ms(uint16_t nCount);
void Delay_us(uint16_t nCount);

/* Private functions ---------------------------------------------------------*/

void main(void)
{
  uint8_t intT[3], decT[3];
  uint16_t t;
  ErrorStatus flag_init;
  TemperatureTypeDef Temperature = {0, 1, ERROR};
  
  SystemInit_CLK();
  OLED_SPI_Init();
  TIM_Init();
#ifdef __UART_H
  UART2_Config();
#endif
  
  DS18B20_Reset();
  flag_init = DS18B20_Check();
  
  if (flag_init == ERROR)
  {
    OLED_ShowString(0, 40, "Init ERROR! Please Reset!", OLED_FONT_SIZE_16);
#ifdef __UART_H
    printf("Init ERROR! Please Reset!");
#endif
    OLED_Refresh_Gram ();
    while(1);
  }
  else 
  {
    OLED_ShowString(0, 40, "Init SUCCESS!", OLED_FONT_SIZE_16);
#ifdef __UART_H
    printf("Init SUCCESS!");
#endif
    OLED_Refresh_Gram ();
  }
  
  /* Infinite loop */
  while (1)
  {
    OLED_Clear();
    DS18B20_GetTemperature(&Temperature); 
    
    OLED_ShowChinese(0, 0, &chinese1_1616[0][0], OLED_FONT_SIZE_16, 4);
    
    if (Temperature.flag == SUCCESS)
    { 
      if(Temperature.sign == 0)
        OLED_ShowString(64, 0, ":+", OLED_FONT_SIZE_12);
      else
        OLED_ShowString(64, 0, ":-", OLED_FONT_SIZE_12);
      
      t = (uint16_t)(Temperature.temp * 100);
      intT[0] = '0' + t / 1000 ;
      intT[1] = '0' + t / 100 % 10 ;
      intT[2] = '\0';
      OLED_ShowString(76, 0, intT, OLED_FONT_SIZE_12);
      OLED_ShowString(88, 0, ".", OLED_FONT_SIZE_12);
      decT[0] = '0' + t / 10 % 10 ;
      decT[1] = '0' + t % 10 ;
      decT[2] = '\0';
      OLED_ShowString(94, 0, decT, OLED_FONT_SIZE_12);
      OLED_ShowString(108, 0, "C", OLED_FONT_SIZE_12);
#ifdef __UART_H
      if(Temperature.sign == 0)
        printf("Temper: +%c%c.%c%c", intT[0], intT[1], decT[0], decT[1]);
      else
        printf("Temper: -%c%c.%c%c", intT[0], intT[1], decT[0], decT[1]);
#endif
    }
    else
    {
      OLED_ShowString(64, 0, ":--.--C", OLED_FONT_SIZE_12);
#ifdef __UART_H
      printf("Temper: --.--C");
#endif
    }

    OLED_Refresh_Gram ();
    TIMDelay_Nms(1000);
  }
  
}

void SystemInit_CLK(void)
{
  CLK_DeInit();
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  CLK_HSICmd(ENABLE);
}

//ms级别延时
void Delay_ms(uint16_t nCount)
{
  while(nCount--)
  {
    Delay_us(1000);
  }
}

//us级别延时
void Delay_us(uint16_t nCount)
{
  nCount *= 1;
  while(--nCount);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
