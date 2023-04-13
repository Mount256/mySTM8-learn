#include "lcd1602.h"

/******发送命令******/
static void LCD1602_Cmd(uint8_t cmd)
{ 
  //Delay_us(30);
  EN_LOW;
  RS_LOW; /* RS=0，写入命令 */
  
  GPIO_Write(Dx_PORT, cmd);     /* 接收高四位命令 */
  EN_HIGH; 
  Delay_ms(15);
  EN_LOW;
  
  GPIO_Write(Dx_PORT, cmd<<4); /* 接收低四位命令 */
  EN_HIGH;
  Delay_ms(15);
  EN_LOW;
}

/******发送数据******/
static void LCD1602_Data(uint8_t data)
{  
  //Delay_us(30);
  EN_LOW;
  RS_HIGH; /* RS=1，写入数据 */
  
  GPIO_Write(Dx_PORT, data);     /* 接收高四位数据 */
  EN_HIGH; 
  Delay_ms(15);
  EN_LOW;
  
  GPIO_Write(Dx_PORT, data<<4); /* 接收低四位数据 */
  EN_HIGH; 
  Delay_ms(15);
  EN_LOW;
}

/******LCD初始化******/
void LCD1602_Init(void)
{
  GPIO_Init(Dx_PORT, (GPIO_Pin_TypeDef)Dx_FOUR_PINS, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(Rx_PORT, (GPIO_Pin_TypeDef)Rx_FOUR_PINS, GPIO_MODE_OUT_PP_HIGH_FAST);
  
  /*LCD1602_Cmd(0x20); 
  LCD1602_Cmd(0x32); 
  Delay_ms(5);
  LCD1602_Cmd(0x28);  // 最后发0x28，进入4线模式，设置16*2显示，115*7点阵，4位数据接口 
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
  LCD1602_Cmd(0x01); /* 清屏 */
  LCD1602_Cmd(0x06); /* 写入数据光标右移，写入新数据显示屏不移动 */
  LCD1602_Cmd(0x0C); /* 开显示，有光标，光标闪烁 */
  //LCD1602_Cmd(0x80);
}

/* 0x80和0xC0分别是两行的开始地址，将字符的序号加上行的地
   址作为命令发送给LCD1602会让下一个字符输出在指定的位置  */
/******发送地址******/
static void LCD1602_SetCursor(uint8_t x, uint8_t y) // x:列坐标 y:行坐标
{
  LCD1602_Cmd(x + (y ? LINE1:LINE0));
}

/******连续发送数据******/
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