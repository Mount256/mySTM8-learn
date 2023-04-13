#include "DS18B20.h"
#include "UART.h"

/******发送复位信号******/
void DS18B20_Reset(void)
{
  DS18B20_DQ_OUT;
  DS18B20_DQ_LOW;
  Delay_us(750);
  DS18B20_DQ_HIGH;
  Delay_us(15);
}

/******检测存在脉冲******/
ErrorStatus DS18B20_Check(void)
{
  uint8_t cnt = 0;
  
  DS18B20_DQ_IN;        /* 设置DQ管脚为输入模式 */
  /* 等待复位信号低电平 */ 
  while((DS18B20_DQ_STATUS != RESET) && (cnt < RESPONSE_MAX_TIME_1))  
  {
    cnt++; 
    Delay_us(1);
  }
  
  if(cnt >= RESPONSE_MAX_TIME_1)
    return ERROR;
  else
    cnt = 0;
  
  /* 再等待复位信号拉高，表示复位结束 */
  while((DS18B20_DQ_STATUS == RESET) && (cnt < RESPONSE_MAX_TIME_2))  
  {
    cnt++; 
    Delay_us(1);
  }
  
  if(cnt >= RESPONSE_MAX_TIME_2)
    return ERROR;
  else
    return SUCCESS;
}

/******从DS18B20读一个位******/
static BitStatus DS18B20_ReadBit(void)
{
  BitStatus data;
  
  DS18B20_DQ_OUT;
  DS18B20_DQ_LOW;
  Delay_us(2);
  DS18B20_DQ_HIGH;
  
  DS18B20_DQ_IN;
  Delay_us(12);       
  
  if(DS18B20_DQ_STATUS != RESET)   
    data = SET;              
  else 
    data = RESET;	   
  
  Delay_us(50);         
  return data;       
}

/******从DS18B20读一个字节******/
static uint8_t DS18B20_ReadByte(void)
{
  uint8_t t, data;
  uint8_t i;
  
  for(i = 0; i < 8; i++)
  {
    t = DS18B20_ReadBit();
    data = (t << 7) | (data >> 1);
  }
  return data;
}

/******从DS18B20写一个字节******/
void DS18B20_WriteByte(uint8_t cmd)
{
  uint8_t bit;
  uint8_t i;
  
  DS18B20_DQ_OUT;
  
  for(i = 0; i < 8; i++)
  {
    bit = cmd & 0x01;
    if (bit == 1) 
    {
      DS18B20_DQ_LOW;
      Delay_us(2);
      DS18B20_DQ_HIGH;
      Delay_us(60); 
    }
    else   
    {
       DS18B20_DQ_LOW;
       Delay_us(60);   
       DS18B20_DQ_HIGH;
       Delay_us(2);    
    }  
    cmd = cmd >> 1; /* 写下一位 */
  }
}

/******采集温度数据******/
void DS18B20_GetTemperature(TemperatureTypeDef* Temperature)
{
  uint8_t data_L, data_H;
  uint16_t data;
  
  DS18B20_Reset();                      /* 发送复位脉冲 */
  Temperature->flag = DS18B20_Check();  /* 检测存在脉冲 */
  if(Temperature->flag == ERROR)
    return;
  DS18B20_WriteByte(0xCC);    /* 跳过ROM检测 */
  DS18B20_WriteByte(0x44);    /* 开始温度转换 */
    
  /* 等待温度采集完成 */
  //while(DS18B20_ReadByte() != 0xFF);  
     
  DS18B20_Reset();                      /* 发送复位脉冲 */
  Temperature->flag = DS18B20_Check();  /* 检测存在脉冲 */
  if(Temperature->flag == ERROR)
    return;
  DS18B20_WriteByte(0xCC);    /* 跳过ROM检测 */
  DS18B20_WriteByte(0xBE);    /* 读取温度 */
		
  data_L = DS18B20_ReadByte(); /* 读取数据低8位 */
  data_H = DS18B20_ReadByte(); /* 读取数据高8位 */
    
#ifdef __UART_H                /* 用于调试的输出数据 */
  printf("\n\rTEST DATA: %d %d\n\r", data_L, data_H);
#endif
    
  if(data_H > 7)
    Temperature->sign = 1;     /* 负数 */
  else     
    Temperature->sign = 0;     /* 正数 */
    
  data = data_L | (data_H<<8); 
  data = data & 0x07FF;       /* 清除高五位的符号位 0000 0111 1111 1111 */
      
  Temperature->intT = data >> 4;       /* 整数部分（中间七位） */        
  Temperature->decT = data & 0x0F;     /* 小数部分（低四位） */
}


