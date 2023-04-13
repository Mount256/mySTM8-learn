#ifndef __UART_H
#define __UART_H

#include "stm8s.h"
#include "stdio.h"

#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int putchar (char c)
#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#endif /* _RAISONANCE_ */

void UART2_Config(void);
void UART2_SendByte(u8 data);
void UART2_SendStr(const unsigned char *p_str);

extern uint8_t buffer;

#endif /* __UART_H */

