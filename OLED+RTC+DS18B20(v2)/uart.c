#include "UART.h"

uint8_t buffer;

void UART2_Config(void)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART2, ENABLE);
    UART2_DeInit();	
    UART2_Init((u32)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO , UART2_SYNCMODE_CLOCK_DISABLE , UART2_MODE_TXRX_ENABLE);
    UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);
    UART2_Cmd(ENABLE);
}

void UART2_SendByte(u8 data)
{
  UART2_SendData8((unsigned char)data);
  while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);
}

void UART2_SendStr(const unsigned char *p_str)
{
  while(*p_str != '\0')
  {
    UART2_SendByte(*p_str);
    p_str++;
  }
}

/**********************************printf*********************************************/

/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the UART2 */
  UART2_SendData8(c);
  /* Loop until the end of transmission */
  while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);
  return (c);
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
  char c = 0;
#else
  int c = 0;
#endif
  /* Loop until the Read data register flag is SET */
  while (UART2_GetFlagStatus(UART2_FLAG_RXNE) == RESET);
  c = UART2_ReceiveData8();
  return (c);
}

