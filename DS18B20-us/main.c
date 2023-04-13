#include "stm8s.h"
#include "UART.h"
#include "DS18b20.h"

void SystemInit_CLK(void);

void main(void)
{
  ErrorStatus flag_init;
  TemperatureTypeDef Temperature = {0, 0, 1, ERROR};
  
  SystemInit_CLK();
  UART2_Config();
  
  printf("\n\rUART2 Example: retarget the C library printf()/getchar() functions to the UART\n\r");
  printf("\n\rEnter Text\n\r");
  
  DS18B20_Reset();
  flag_init = DS18B20_Check();
  
  if(flag_init == ERROR)
  {
    printf("\n\rInit ERROR! Please Reset!\n\r");
    while(1);
  }
  else 
    printf("\n\rInit SUCCESS!\n\r");
  
  while(1)
  {
    DS18B20_GetTemperature(&Temperature); 
    if(Temperature.flag == SUCCESS)
    {
      if(Temperature.sign == 0)
        printf("\n\rTemp: +%d.%d C\n\r", Temperature.intT, Temperature.decT);
      else
        printf("\n\rTemp: -%d.%d C\n\r", Temperature.intT, Temperature.decT);
    }
    else
      printf("\n\rTemperature: --.-- C\n\r");
    Delay_ms(1000);
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
  while (1)
  {
  }
}
#endif

/****END OF FILE****/
