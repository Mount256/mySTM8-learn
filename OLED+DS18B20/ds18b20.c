#include "ds18b20.h"

//ms������ʱ
static void DS18B20_DLY_ms(uint16_t nCount)
{
  while(nCount--)
  {
    DS18B20_DLY_us(1000);
  }
}

//us������ʱ
static void DS18B20_DLY_us(uint16_t nCount)
{
  nCount *= 2;
  while(--nCount);
}

/******���͸�λ�ź�******/
void DS18B20_Reset(void)
{
  DS18B20_DQ_OUT;
  DS18B20_DQ_LOW;
  DS18B20_DLY_us(750);
  DS18B20_DQ_HIGH;
  DS18B20_DLY_us(15);
}

/******����������******/
ErrorStatus DS18B20_Check(void)
{
  uint8_t cnt = 0;
  
  DS18B20_DQ_IN;        /* ����DQ�ܽ�Ϊ����ģʽ */
  /* �ȴ���λ�źŵ͵�ƽ */ 
  while((DS18B20_DQ_STATUS != RESET) && (cnt < RESPONSE_MAX_TIME_1))  
  {
    cnt++; 
    DS18B20_DLY_us(1);
  }
  
  if(cnt >= RESPONSE_MAX_TIME_1)
    return ERROR;
  else
    cnt = 0;
  
  /* �ٵȴ���λ�ź����ߣ���ʾ��λ���� */
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

/******��DS18B20��һ��λ******/
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

/******��DS18B20��һ���ֽ�******/
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

/******��DS18B20дһ���ֽ�******/
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
    cmd = cmd >> 1; /* д��һλ */
  }
}

/******�ɼ��¶�����******/
void DS18B20_GetTemperature(TemperatureTypeDef* Temperature)
{
  uint8_t data_L, data_H;
  uint16_t data;
  
  DS18B20_Reset();                      /* ���͸�λ���� */
  Temperature->flag = DS18B20_Check();  /* ���������� */
  if(Temperature->flag == ERROR)
    return;
  DS18B20_WriteByte(0xCC);    /* ����ROM��� */
  DS18B20_WriteByte(0x44);    /* ��ʼ�¶�ת�� */
    
  /* �ȴ��¶Ȳɼ���� */
  //while(DS18B20_ReadByte() != 0xFF);  
     
  DS18B20_Reset();                      /* ���͸�λ���� */
  Temperature->flag = DS18B20_Check();  /* ���������� */
  if(Temperature->flag == ERROR)
    return;
  DS18B20_WriteByte(0xCC);    /* ����ROM��� */
  DS18B20_WriteByte(0xBE);    /* ��ȡ�¶� */
		
  data_L = DS18B20_ReadByte(); /* ��ȡ���ݵ�8λ */
  data_H = DS18B20_ReadByte(); /* ��ȡ���ݸ�8λ */
    
  data = (data_H << 8) + data_L;
    
  if(data_H > 7)
  {
    Temperature->sign = 1;     /* ���� */
    data = (~data) + 1;
  }
  else     
    Temperature->sign = 0;     /* ���� */
    
  Temperature->temp = (float)data * 0.0625;
  
#ifdef __UART_H                /* ���ڵ��Ե�������� */
  printf("\n\rTEST DATA: %x %x %x\n\r", data_H, data_L, data);
#endif
}


