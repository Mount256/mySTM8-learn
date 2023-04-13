#include "led.h"

void LED_Init (void)
{
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_ALL_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  
  LED0_OFF;
  LED1_OFF;
  LED2_OFF;
  LED3_OFF;
}
