#ifndef __KEY_H
#define __KEY_H

#include "stm8s.h"

/*********Definition*********/
#define KEYx_PORT       (GPIOA)
#define KEYx_EXTI_PORT  (EXTI_PORT_GPIOA)
#define KEY0_PIN        (GPIO_PIN_3)
#define KEY1_PIN        (GPIO_PIN_4)
#define KEY2_PIN        (GPIO_PIN_5)
#define KEY3_PIN        (GPIO_PIN_6)
#define KEY_ALL_PINS    (KEY0_PIN | KEY1_PIN | KEY2_PIN | KEY3_PIN)

#define KEY0_IN         GPIO_ReadInputPin(KEYx_PORT, KEY0_PIN)
#define KEY1_IN         GPIO_ReadInputPin(KEYx_PORT, KEY1_PIN)
#define KEY2_IN         GPIO_ReadInputPin(KEYx_PORT, KEY2_PIN)
#define KEY3_IN         GPIO_ReadInputPin(KEYx_PORT, KEY3_PIN)

#define KEY_PRESS       RESET
#define KEY_RELEASE     SET

#define UNDEFINED       255

/*********Function*********/
void KEY_Init(void);

/*********Varible*********/
extern uint8_t FlagKey;

#endif /* __KEY_H */