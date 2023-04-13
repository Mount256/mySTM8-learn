#ifndef __TIMER_H
#define __TIMER_H

#include "stm8s.h"

void TIM_Init(void);
void TIMDelay_N10us(uint16_t Times);
void TIMDelay_Nms(uint32_t Times);

#endif /* __TIMER_H */
