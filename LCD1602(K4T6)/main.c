#include "stm8s.h"
#include "lcd1602.h"

void SystemInit_CLK(void);

void main(void)
{
  SystemInit_CLK();
  LCD1602_Init();
  LCD1602_PrintStr(1, 0, "Hello World!"); // 第0行第1列
    
  while (1)
  {
    //LCD1602_PrintStr(0, 0, "Hello!");
    //Delay_us(0xFFF);
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

void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif

/****END OF FILE****/
