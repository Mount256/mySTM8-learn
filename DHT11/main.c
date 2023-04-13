#include "stm8s.h"
#include "dht11.h"
#include "timer.h"
#include "uart.h"

void SystemInit_CLK(void);
uint8_t bit_reverse (uint8_t x);

void main(void)
{
  TempHumiDataTypeDef TempHumi = {0, 0, 0, 0, 0, ERROR};
  uint8_t HumiInt, HumiDec, TempInt, TempDec;
  
  SystemInit_CLK();
  UART2_Config();
  TIM_Init(80);
  DHT11_Init();
  
  printf("Init Success!\r\n");
  
  while (1)
  {
    TempHumi = DHT11_ReadData();
    
    if (TempHumi.Flag != ERROR)
    {
      printf("Humi=%d.%d%% Temp=%d.%d%d¡ãC Parity=%d\r\n", TempHumi.HumiMSB, TempHumi.HumiLSB, 
             TempHumi.TempMSB, TempHumi.TempLSB/10, TempHumi.TempLSB%10, TempHumi.Parity);
      
      HumiInt = bit_reverse (TempHumi.HumiMSB);
      HumiDec = bit_reverse (TempHumi.HumiLSB);
      TempInt = bit_reverse (TempHumi.TempMSB);
      TempDec = bit_reverse (TempHumi.TempLSB);
      
      printf("Humi=%d.%d%% Temp=%d.%d%d¡ãC Parity=%d\r\n", HumiInt, HumiDec, 
             TempInt, TempDec/10, TempDec%10, TempHumi.Parity);
    }
    else
    {
      printf("Humi=--.--%% Temp=--.--¡ãC\r\n");
    }
    
    printf("\r\n");
    TIMDelay_Nms(2000);
  }
}

uint8_t bit_reverse (uint8_t x)
{
    x = (((x & 0xf0) >> 4) | ((x & 0x0f) << 4));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1)); 
    return x;
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

