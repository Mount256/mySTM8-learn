#include "stm8s.h"
#include "LCD1602.h"
#include "DS18B20.h"
//#include "UART.h"
#include "delay.h"

#define LED_GPIO_PORT  (GPIOD)
#define LED_GPIO_PIN  (GPIO_PIN_7)
#define ALART_TEMP 2437

void SystemInit_CLK(void);

void main(void)
{
  uint8_t intT[2], decT[2];
  uint16_t t;
  ErrorStatus flag_init;
  TemperatureTypeDef Temperature = {0, 1, ERROR};
  
  SystemInit_CLK();
  
#ifdef __UART_H 
  UART2_Config();
#endif
  
  GPIO_Init(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  
  LCD1602_Init();
  
  DS18B20_Reset();
  flag_init = DS18B20_Check();
  if(flag_init == ERROR)
  {
    LCD1602_PrintStr(0, 0, "Init ERROR! Please Reset!");
    while(1);
  }
  else 
  {
    LCD1602_PrintStr(0, 0, "Init SUCCESS!");
    Delay_ms(2000);
    LCD1602_Clr();
  }
  
  while (1)
  {
    DS18B20_GetTemperature(&Temperature); 
    if(Temperature.flag == SUCCESS)
    {
      GPIO_WriteReverse(LED_GPIO_PORT, LED_GPIO_PIN);
      if(Temperature.sign == 0)
        LCD1602_PrintStr(0, 0, "Temper:+");
      else
        LCD1602_PrintStr(0, 0, "Temper:-");
      
      t = (uint16_t)(Temperature.temp * 100);
      intT[0] = '0' + t / 1000 ;
      intT[1] = '0' + t / 100 % 10 ;
      LCD1602_PrintStr(8, 0, intT);
      LCD1602_PrintStr(10, 0, ".");
      decT[0] = '0' + t / 10 % 10 ;
      decT[1] = '0' + t % 10 ;
      LCD1602_PrintStr(11, 0, decT);
      LCD1602_PrintStr(13, 0, "C..");
    }
    else
      LCD1602_PrintStr(0, 0, "Temper:--.--C..");
#ifdef __UART_H                /* 用于调试的输出数据 */
    printf("\n\rDATA: %d\n\r",  t);
#endif 
    Delay_ms(3000);
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


/***********END OF FILE************/
