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
#include "key.h"
#include "oled_spi.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void SystemInit_CLK(void);

/* Private functions ---------------------------------------------------------*/

void main(void)
{
  uint8_t FlagKeyPre = 0;
  
  SystemInit_CLK();
  OLED_SPI_Init();
  KEY_Init();
  __enable_interrupt();
  
  FlagKey = 1;
  
  /* Infinite loop */
  while (1)
  {
    if (FlagKeyPre != FlagKey)
    {
      OLED_Clear();
      FlagKeyPre = FlagKey;
      switch (FlagKey)
      {
      case 1:  
        OLED_ShowPic (0, 0, &bmp1[0][0], 114, 64, OLED_CATHODE);
        break;
      case 2:  
        OLED_ShowPic (0, 0, &bmp2[0][0], 64, 64, OLED_CATHODE);
        break;
      case 3:  
        OLED_ShowPic (0, 0, &bmp3[0][0], 60, 64, OLED_CATHODE);
        break; 
      case 4:  
        OLED_ShowPic (0, 0, &bmp4[0][0], 64, 64, OLED_CATHODE);
        break;
      case 5:  
        OLED_ShowPic (0, 0, &bmp5[0][0], 85, 64, OLED_CATHODE);
        break;
      default:
        break;
      }
      OLED_Refresh_Gram ();
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
