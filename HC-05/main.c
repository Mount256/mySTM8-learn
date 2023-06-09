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
#include "uart.h"
#include "led.h"
#include "timer.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void SystemInit_CLK(void);

/* Private functions ---------------------------------------------------------*/

void main(void)
{
  SystemInit_CLK();
  TIM_Init();
  LED_Init();
  UART2_Config();
  
  buffer = 0x00;
  
  __enable_interrupt();
  
  /* Infinite loop */
  while (1)
  {
    switch (buffer)
    {
    case '0':
      LED0_REVERSE;
      LED1_OFF; LED2_OFF; LED3_OFF;
      printf("LED0 WORKING!");
      break;
    case '1':
      LED1_REVERSE;
      LED0_OFF; LED2_OFF; LED3_OFF;
      printf("LED1 WORKING!");
      break;
    case '2':
      LED2_REVERSE;
      LED0_OFF; LED1_OFF; LED3_OFF;
      printf("LED2 WORKING!");
      break;
    case '3':
      LED3_REVERSE;
      LED0_OFF; LED1_OFF; LED2_OFF; 
      printf("LED3 WORKING!");
      break;
    default:
      LED0_OFF; LED1_OFF; LED2_OFF; LED3_OFF;
      printf("Wrong!");
      break;
    }
    
    TIMDelay_Nms(500);
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
