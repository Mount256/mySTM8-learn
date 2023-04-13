#include "key.h"

/*********Varible*********/
uint8_t FlagKey;

void KEY_Init(void)
{
  GPIO_Init(KEYx_PORT, (GPIO_Pin_TypeDef)KEY_ALL_PINS, GPIO_MODE_IN_PU_IT);
  EXTI_SetExtIntSensitivity(KEYx_EXTI_PORT, EXTI_SENSITIVITY_FALL_ONLY);
  FlagKey = UNDEFINED;
}
