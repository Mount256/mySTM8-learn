#include "ds1302.h"

/*************************************************************************
                                ��ʼ��
--------------------------------------------------------------------------
�޲���
--------------------------------------------------------------------------
�޷���ֵ
*************************************************************************/
void DS1302_Init (void)
{
  GPIO_Init(RTC_SCK_PORT, RTC_SCK_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(RTC_RST_PORT, RTC_RST_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(RTC_IO_PORT,  RTC_IO_PIN,  GPIO_MODE_OUT_PP_HIGH_SLOW);
  
  RTC_SCK_LOW();
  RTC_IO_LOW();
  RTC_RST_LOW();
}

/*************************************************************************
                              дһ�ֽ�����
--------------------------------------------------------------------------
byte��һ�ֽ�����
--------------------------------------------------------------------------
�޷���ֵ
*************************************************************************/
static void DS1302_WriteByte (uint8_t byte)
{
  uint8_t i;
  BitStatus bit;
  
  RTC_IO_OUT();         // IO ����Ϊ���ģʽ
  
  for (i = 0; i < 8; i++)
  {
    RTC_SCK_LOW();
    
    bit = (BitStatus)(byte & 0x01);
    if (bit != RESET)
      RTC_IO_HIGH();
    else
      RTC_IO_LOW();
    
    RTC_SCK_HIGH();
    byte >>= 1;
    
    //DS1302_DLY_ms(1);
  }
}

/*************************************************************************
                              ��һ�ֽ�����
--------------------------------------------------------------------------
addr����ַ
--------------------------------------------------------------------------
����ֵ��һ�ֽ�����
*************************************************************************/
static uint8_t DS1302_ReadByte (void)
{
  uint8_t i;
  uint8_t data = 0;
  BitStatus bit;
  
  RTC_IO_IN();          // IO ����Ϊ����ģʽ
  
  for (i = 0; i < 8; i++)
  {
    data >>= 1;
    RTC_SCK_LOW();
    
    bit = RTC_IO_STATUS();
    if (bit != RESET)
      data |= 0x80;
    else
      data &= 0x7F;
    
    RTC_SCK_HIGH();
    
    //DS1302_DLY_ms(1);
  }
  
  return data;
}

/*************************************************************************
                      ��ָ���Ĵ���д��һ�ֽ�����
--------------------------------------------------------------------------
addr����ַ  data��һ�ֽ�����
--------------------------------------------------------------------------
�޷���ֵ
*************************************************************************/
static void DS1302_WriteData (uint8_t addr, uint8_t data)
{
  // ���ݴ��俪ʼ
  RTC_RST_LOW();
  RTC_SCK_LOW();
  RTC_RST_HIGH();
  
  DS1302_WriteByte (addr);      // д��ĵ�ַ
  DS1302_WriteByte (data);      // д�������
  
  // ���ݴ������
  RTC_RST_LOW();
}

/*************************************************************************
                      ��ָ���Ĵ�������һ�ֽ�����
--------------------------------------------------------------------------
addr����ַ
--------------------------------------------------------------------------
����ֵ��һ�ֽ�����
*************************************************************************/
static uint8_t DS1302_ReadData (uint8_t addr)
{
  uint8_t data;
  
  // ���ݴ��俪ʼ
  RTC_RST_LOW();
  RTC_SCK_LOW();
  RTC_RST_HIGH();
  
  DS1302_WriteByte (addr);      // Ҫ���ĵ�ַ
  data = DS1302_ReadByte();     // Ҫ��������
  
  // ���ݴ������
  RTC_RST_LOW();
  
  return data;
}

/*************************************************************************
                                ��ʱ��
--------------------------------------------------------------------------
�޲���
--------------------------------------------------------------------------
����ֵ��ʱ������
*************************************************************************/
TimeTypeDef DS1302_ReadTime (void)
{
  TimeTypeDef TimeDisplay;
  
  // �������������� BCD ��
  TimeBuffer.year   = DS1302_ReadData (0x8D);  
  TimeBuffer.month  = DS1302_ReadData (0x89);  
  TimeBuffer.day    = DS1302_ReadData (0x87);  
  TimeBuffer.week   = DS1302_ReadData (0x8B);  
  TimeBuffer.hour   = DS1302_ReadData (0x85);  
  TimeBuffer.minute = DS1302_ReadData (0x83);  
  TimeBuffer.second = DS1302_ReadData (0x81);  // bit7 ����Ϊʱ����ͣ��־��CH��
  
  // BCD ��ת��Ϊʮ����
  TimeDisplay.year   = BCDtoDec (TimeBuffer.year);
  TimeDisplay.month  = BCDtoDec (TimeBuffer.month);
  TimeDisplay.day    = BCDtoDec (TimeBuffer.day);
  TimeDisplay.week   = BCDtoDec (TimeBuffer.week);
  TimeDisplay.hour   = BCDtoDec (TimeBuffer.hour);
  TimeDisplay.minute = BCDtoDec (TimeBuffer.minute);
  TimeDisplay.second = BCDtoDec (TimeBuffer.second);
  
  return TimeDisplay;
}

/*************************************************************************
                                �޸�ʱ��
--------------------------------------------------------------------------
*TimeDisplay��Ҫ��ʾ��ʱ�䣨ʮ���ƣ�
--------------------------------------------------------------------------
�޷���ֵ
*************************************************************************/
void DS1302_WriteTime (TimeTypeDef *TimeDisplay)
{ 
  // ʮ����ת��Ϊ BCD ��
  TimeBuffer.year   = DectoBCD (TimeDisplay->year);
  TimeBuffer.month  = DectoBCD (TimeDisplay->month);
  TimeBuffer.day    = DectoBCD (TimeDisplay->day);
  TimeBuffer.week   = DectoBCD (TimeDisplay->week);
  TimeBuffer.hour   = DectoBCD (TimeDisplay->hour);
  TimeBuffer.minute = DectoBCD (TimeDisplay->minute);
  TimeBuffer.second = DectoBCD (TimeDisplay->second);
  
  // �ر�д���������ƼĴ�����8FH��8EH  bit7������λ��
  DS1302_WriteData (0x8E, 0x00);        
  
  // д��������� BCD ��
  DS1302_WriteData (0x8C, TimeBuffer.year);   
  DS1302_WriteData (0x88, TimeBuffer.month); 
  DS1302_WriteData (0x86, TimeBuffer.day); 
  DS1302_WriteData (0x8A, TimeBuffer.week); 
  DS1302_WriteData (0x84, TimeBuffer.hour); 
  DS1302_WriteData (0x82, TimeBuffer.minute); 
  DS1302_WriteData (0x80, TimeBuffer.second); // bit7 ����Ϊʱ����ͣ��־��CH��
  
  // ����д���������ƼĴ�����8FH��8EH  bit7������λ��
  DS1302_WriteData (0x8E, 0x80);        
}

/*************************************************************************
                             ʮ����תBCD��
--------------------------------------------------------------------------
num��ʮ������
--------------------------------------------------------------------------
����ֵ��BCD��
*************************************************************************/
static uint8_t DectoBCD (uint8_t num)
{
  uint8_t result;
  uint8_t temp1, temp2;

  temp1  = (num / 10) << 4;          // ʮλ / 10 * 16
  temp2  =  num % 10;                // ��λ % 10
  result = temp1 + temp2;
  
  return result;
}

/*************************************************************************
                             BCD��תʮ����
--------------------------------------------------------------------------
num��BCD��
--------------------------------------------------------------------------
����ֵ��ʮ����
*************************************************************************/
static uint8_t BCDtoDec (uint8_t num)
{
  uint8_t result;
  uint8_t temp1, temp2;
  
  temp1 = (num >> 4) * 10;         // ʮλ / 16 * 10
  temp2 =  num & 0x0F;             // ��λ % 16
  result = temp1 + temp2;
  
  return result;
}

/*************************************************************************
                             �����ʱ��ms����
--------------------------------------------------------------------------
nCount����ʱ����
--------------------------------------------------------------------------
�޷���ֵ
*************************************************************************/
static void DS1302_DLY_ms(uint16_t nCount)
{
  while(nCount--)
  {
    DS1302_DLY_us(1000);
  }
}

/*************************************************************************
                             �����ʱ��us����
--------------------------------------------------------------------------
nCount����ʱ����
--------------------------------------------------------------------------
�޷���ֵ
*************************************************************************/
static void DS1302_DLY_us(uint16_t nCount)
{
  nCount *= 2;
  while(--nCount);
}



