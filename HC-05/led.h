#ifndef __LED_H
#define __LED_H

#include "stm8s.h"

#define LED_GPIO_PORT           (GPIOB)

#define LED0_PIN                (GPIO_PIN_0)
#define LED1_PIN                (GPIO_PIN_1)
#define LED2_PIN                (GPIO_PIN_2)
#define LED3_PIN                (GPIO_PIN_3)

#define LED_GPIO_ALL_PINS       (LED3_PIN | LED2_PIN | LED1_PIN | LED0_PIN)

#define LED0_ON                 GPIO_WriteLow (LED_GPIO_PORT, LED0_PIN)  
#define LED0_OFF                GPIO_WriteHigh(LED_GPIO_PORT, LED0_PIN)
#define LED0_REVERSE            GPIO_WriteReverse(LED_GPIO_PORT, LED0_PIN)

#define LED1_ON                 GPIO_WriteLow (LED_GPIO_PORT, LED1_PIN)  
#define LED1_OFF                GPIO_WriteHigh(LED_GPIO_PORT, LED1_PIN)
#define LED1_REVERSE            GPIO_WriteReverse(LED_GPIO_PORT, LED1_PIN)

#define LED2_ON                 GPIO_WriteLow (LED_GPIO_PORT, LED2_PIN)  
#define LED2_OFF                GPIO_WriteHigh(LED_GPIO_PORT, LED2_PIN)
#define LED2_REVERSE            GPIO_WriteReverse(LED_GPIO_PORT, LED2_PIN)

#define LED3_ON                 GPIO_WriteLow (LED_GPIO_PORT, LED3_PIN)  
#define LED3_OFF                GPIO_WriteHigh(LED_GPIO_PORT, LED3_PIN)
#define LED3_REVERSE            GPIO_WriteReverse(LED_GPIO_PORT, LED3_PIN)

void LED_Init (void);

#endif /* __LED_H*/

