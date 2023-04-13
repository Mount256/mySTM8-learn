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
#include "oled_spi.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  OLED_SPI_Init();
  
  OLED_ShowPic (0, 0, &bmp1[0][0], 114, 64, OLED_CATHODE);
  OLED_Refresh_Gram ();
  OLED_VerScroll (PAGE0, PAGE7, FRAME7, 1, OLED_SCROLL_LEFT);
    
  /* Infinite loop */
  while (1)
  {
    //OLED_ShowString (0, 0, "Welcome To", OLED_FONT_SIZE_16); 
    //OLED_ShowChinese (20, 20, &chinese1_1616[0][0], OLED_FONT_SIZE_16, 4);
    //OLED_ShowChinese (50, 40, &chinese2_1616[0][0], OLED_FONT_SIZE_16, 3);
    
  } 
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
