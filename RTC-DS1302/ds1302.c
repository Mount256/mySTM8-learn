#include "ds1302.h"

/*************************************************************************
                                初始化
--------------------------------------------------------------------------
无参数
--------------------------------------------------------------------------
无返回值
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
                              写一字节数据
--------------------------------------------------------------------------
byte：一字节数据
--------------------------------------------------------------------------
无返回值
*************************************************************************/
static void DS1302_WriteByte (uint8_t byte)
{
  uint8_t i;
  BitStatus bit;
  
  RTC_IO_OUT();         // IO 配置为输出模式
  
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
                              读一字节数据
--------------------------------------------------------------------------
addr：地址
--------------------------------------------------------------------------
返回值：一字节数据
*************************************************************************/
static uint8_t DS1302_ReadByte (void)
{
  uint8_t i;
  uint8_t data = 0;
  BitStatus bit;
  
  RTC_IO_IN();          // IO 配置为输入模式
  
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
                      往指定寄存器写入一字节数据
--------------------------------------------------------------------------
addr：地址  data：一字节数据
--------------------------------------------------------------------------
无返回值
*************************************************************************/
static void DS1302_WriteData (uint8_t addr, uint8_t data)
{
  // 数据传输开始
  RTC_RST_LOW();
  RTC_SCK_LOW();
  RTC_RST_HIGH();
  
  DS1302_WriteByte (addr);      // 写入的地址
  DS1302_WriteByte (data);      // 写入的数据
  
  // 数据传输结束
  RTC_RST_LOW();
}

/*************************************************************************
                      在指定寄存器读出一字节数据
--------------------------------------------------------------------------
addr：地址
--------------------------------------------------------------------------
返回值：一字节数据
*************************************************************************/
static uint8_t DS1302_ReadData (uint8_t addr)
{
  uint8_t data;
  
  // 数据传输开始
  RTC_RST_LOW();
  RTC_SCK_LOW();
  RTC_RST_HIGH();
  
  DS1302_WriteByte (addr);      // 要读的地址
  data = DS1302_ReadByte();     // 要读的数据
  
  // 数据传输结束
  RTC_RST_LOW();
  
  return data;
}

/*************************************************************************
                                读时间
--------------------------------------------------------------------------
无参数
--------------------------------------------------------------------------
返回值：时间数据
*************************************************************************/
TimeTypeDef DS1302_ReadTime (void)
{
  TimeTypeDef TimeDisplay;
  
  // 读出来的数据是 BCD 码
  TimeBuffer.year   = DS1302_ReadData (0x8D);  
  TimeBuffer.month  = DS1302_ReadData (0x89);  
  TimeBuffer.day    = DS1302_ReadData (0x87);  
  TimeBuffer.week   = DS1302_ReadData (0x8B);  
  TimeBuffer.hour   = DS1302_ReadData (0x85);  
  TimeBuffer.minute = DS1302_ReadData (0x83);  
  TimeBuffer.second = DS1302_ReadData (0x81);  // bit7 定义为时钟暂停标志（CH）
  
  // BCD 码转换为十进制
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
                                修改时间
--------------------------------------------------------------------------
*TimeDisplay：要显示的时间（十进制）
--------------------------------------------------------------------------
无返回值
*************************************************************************/
void DS1302_WriteTime (TimeTypeDef *TimeDisplay)
{ 
  // 十进制转换为 BCD 码
  TimeBuffer.year   = DectoBCD (TimeDisplay->year);
  TimeBuffer.month  = DectoBCD (TimeDisplay->month);
  TimeBuffer.day    = DectoBCD (TimeDisplay->day);
  TimeBuffer.week   = DectoBCD (TimeDisplay->week);
  TimeBuffer.hour   = DectoBCD (TimeDisplay->hour);
  TimeBuffer.minute = DectoBCD (TimeDisplay->minute);
  TimeBuffer.second = DectoBCD (TimeDisplay->second);
  
  // 关闭写保护（控制寄存器：8FH、8EH  bit7：保护位）
  DS1302_WriteData (0x8E, 0x00);        
  
  // 写入的数据是 BCD 码
  DS1302_WriteData (0x8C, TimeBuffer.year);   
  DS1302_WriteData (0x88, TimeBuffer.month); 
  DS1302_WriteData (0x86, TimeBuffer.day); 
  DS1302_WriteData (0x8A, TimeBuffer.week); 
  DS1302_WriteData (0x84, TimeBuffer.hour); 
  DS1302_WriteData (0x82, TimeBuffer.minute); 
  DS1302_WriteData (0x80, TimeBuffer.second); // bit7 定义为时钟暂停标志（CH）
  
  // 开启写保护（控制寄存器：8FH、8EH  bit7：保护位）
  DS1302_WriteData (0x8E, 0x80);        
}

/*************************************************************************
                             十进制转BCD码
--------------------------------------------------------------------------
num：十进制数
--------------------------------------------------------------------------
返回值：BCD码
*************************************************************************/
static uint8_t DectoBCD (uint8_t num)
{
  uint8_t result;
  uint8_t temp1, temp2;

  temp1  = (num / 10) << 4;          // 十位 / 10 * 16
  temp2  =  num % 10;                // 个位 % 10
  result = temp1 + temp2;
  
  return result;
}

/*************************************************************************
                             BCD码转十进制
--------------------------------------------------------------------------
num：BCD码
--------------------------------------------------------------------------
返回值：十进制
*************************************************************************/
static uint8_t BCDtoDec (uint8_t num)
{
  uint8_t result;
  uint8_t temp1, temp2;
  
  temp1 = (num >> 4) * 10;         // 十位 / 16 * 10
  temp2 =  num & 0x0F;             // 个位 % 16
  result = temp1 + temp2;
  
  return result;
}

/*************************************************************************
                             软件延时（ms级别）
--------------------------------------------------------------------------
nCount：延时长度
--------------------------------------------------------------------------
无返回值
*************************************************************************/
static void DS1302_DLY_ms(uint16_t nCount)
{
  while(nCount--)
  {
    DS1302_DLY_us(1000);
  }
}

/*************************************************************************
                             软件延时（us级别）
--------------------------------------------------------------------------
nCount：延时长度
--------------------------------------------------------------------------
无返回值
*************************************************************************/
static void DS1302_DLY_us(uint16_t nCount)
{
  nCount *= 2;
  while(--nCount);
}



