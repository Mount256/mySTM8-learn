#include "timer.h"

void TIM_Init (void)
{                                             // 延时10us (2分频=8M  计数80个脉冲)
  TIM4_TimeBaseInit (TIM4_PRESCALER_2, 79);
  TIM4_ClearFlag (TIM4_FLAG_UPDATE);
}

void TIMDelay_N10us (uint16_t Times)
{
  TIM4_SetCounter (0);                        // 计数值归零
  TIM4_Cmd (ENABLE);                          // 启动定时器
  while (Times--)
  {
    while (RESET == TIM4_GetFlagStatus(TIM4_FLAG_UPDATE));
    TIM4_ClearFlag (TIM4_FLAG_UPDATE);
  }
  TIM4_Cmd (DISABLE);                        // 关闭定时器
}

void TIMDelay_Nms (uint32_t Times)
{
  while (Times--)
  {
    TIMDelay_N10us(100);                // 100*10us = 1ms
  }
}

void TIMDelay_Ns(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_Nms(1000);
  }
}