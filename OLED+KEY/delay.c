#include "delay.h"

//ms������ʱ
void Delay_ms(uint16_t nCount)
{
  while(nCount--)
  {
    Delay_us(1000);
  }
}

//us������ʱ
void Delay_us(uint16_t nCount)
{
  while(--nCount);
}

