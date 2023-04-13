#include "oled_delay.h"

void OLED_DLY_ms (uint32_t ms)
{                         
  uint32_t a;
  
  while (ms)
  {    
    a = 200;
    while (a--);
    ms--;
  }
}