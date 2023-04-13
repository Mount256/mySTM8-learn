#include "ds18b20.h"

//ms级别延时
static void DS18B20_DLY_ms(uint16_t nCount)
{
  while(nCount--)
  {
    DS18B20_DLY_us(1000);
  }
}

//us级别延时
static void DS18B20_DLY_us(uint16_t nCount)
{
  nCount *= 2;
  while(--nCount);
}

/******发送复位信号******/
void DS18B20_Reset(void)
{
  DS18B20_DQ_OUT;
  DS18B20_DQ_LOW;
  DS18B20_DLY_us(750);
  DS18B20_DQ_HIGH;
  DS18B20_DLY_us(15);
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
    DS18B20_DLY_us(1);
  }
  
  if(cnt >= RESPONSE_MAX_TIME_1)
    return ERROR;
  else
    cnt = 0;
  
  /* 再等待复位信号拉高，表示复位结束 */
  while((DS18B20_DQ_STATUS == RESET) && (cnt < RESPONSE_MAX_TIME_2))  
  {
    cnt++; 
    DS18B20_DLY_us(1);
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
  DS18B20_DLY_us(2);
  DS18B20_DQ_HIGH;
  
  DS18B20_DQ_IN;
  DS18B20_DLY_us(12);       
  
  if(DS18B20_DQ_STATUS != RESET)   
    data = SET;              
  else 
    data = RESET;	   
  
  DS18B20_DLY_us(50);         
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
      DS18B20_DLY_us(2);
      DS18B20_DQ_HIGH;
      DS18B20_DLY_us(60); 
    }
    else   
    {
     DS18B20_DQ_LOW;
     DS18B20_DLY_us(60);   
     DS18B20_DQ_HIGH;
     DS18B20_DLY_us(2);    
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
    
  data = (data_H << 8) + data_L;
    
  if(data_H > 7)
  {
    Temperature->sign = 1;     /* 负数 */
    data = (~data) + 1;
  }
  else     
    Temperature->sign = 0;     /* 正数 */
    
  Temperature->temp = (float)data * 0.0625;
  
#ifdef __UART_H                /* 用于调试的输出数据 */
  printf("\n\rTEST DATA: %x %x %x\n\r", data_H, data_L, data);
#endif
}


