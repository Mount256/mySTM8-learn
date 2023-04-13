#include "lcd1602.h"

/******��������******/
static void LCD1602_Cmd(uint8_t cmd)
{ 
  //Delay_us(30);
  EN_LOW;
  RS_LOW; /* RS=0��д������ */
  
  GPIO_Write(Dx_PORT, cmd);     /* ���ո���λ���� */
  EN_HIGH; 
  Delay_ms(15);
  EN_LOW;
  
  GPIO_Write(Dx_PORT, cmd<<4); /* ���յ���λ���� */
  EN_HIGH;
  Delay_ms(15);
  EN_LOW;
}

/******��������******/
static void LCD1602_Data(uint8_t data)
{  
  //Delay_us(30);
  EN_LOW;
  RS_HIGH; /* RS=1��д������ */
  
  GPIO_Write(Dx_PORT, data);     /* ���ո���λ���� */
  EN_HIGH; 
  Delay_ms(15);
  EN_LOW;
  
  GPIO_Write(Dx_PORT, data<<4); /* ���յ���λ���� */
  EN_HIGH; 
  Delay_ms(15);
  EN_LOW;
}

/******LCD��ʼ��******/
void LCD1602_Init(void)
{
  GPIO_Init(Dx_PORT, (GPIO_Pin_TypeDef)Dx_FOUR_PINS, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(Rx_PORT, (GPIO_Pin_TypeDef)Rx_FOUR_PINS, GPIO_MODE_OUT_PP_HIGH_FAST);
  
  /*LCD1602_Cmd(0x20); 
  LCD1602_Cmd(0x32); 
  Delay_ms(5);
  LCD1602_Cmd(0x28);  // ���0x28������4��ģʽ������16*2��ʾ��115*7����4λ���ݽӿ� 
  Delay_ms(5);
  LCD1602_Cmd(0x28);
  Delay_ms(5);
  EN_HIGH;
  LCD1602_Cmd(0x28);
  EN_LOW;*/
  
  LCD1602_Cmd(0x20);
  Delay_ms(20);
  LCD1602_Cmd(0x28);
  Delay_ms(20);
  LCD1602_Cmd(0x01); /* ���� */
  LCD1602_Cmd(0x06); /* д�����ݹ�����ƣ�д����������ʾ�����ƶ� */
  LCD1602_Cmd(0x0C); /* ����ʾ���й�꣬�����˸ */
  //LCD1602_Cmd(0x80);
}

/* 0x80��0xC0�ֱ������еĿ�ʼ��ַ�����ַ�����ż����еĵ�
   ַ��Ϊ����͸�LCD1602������һ���ַ������ָ����λ��  */
/******���͵�ַ******/
static void LCD1602_SetCursor(uint8_t x, uint8_t y) // x:������ y:������
{
  LCD1602_Cmd(x + (y ? LINE1:LINE0));
}

/******������������******/
void LCD1602_PrintStr(uint8_t x, uint8_t y, uint8_t *str)
{
  LCD1602_SetCursor(x, y);
  while(*str != '\0')
  {
    LCD1602_Data(*str++);
  }
}

void LCD1602_Clr(void)
{
  LCD1602_Cmd(0x01);
}