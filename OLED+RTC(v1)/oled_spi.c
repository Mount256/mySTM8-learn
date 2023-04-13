#include "oled_spi.h"

uint8_t OLED_GRAM[128][8];

/*************************************************************************
                        OLED 专用软件延时函数
--------------------------------------------------------------------------
ms：软件延时长度
*************************************************************************/
static void OLED_DLY_ms (uint32_t ms)
{                         
  uint32_t a;
  
  while (ms)
  {    
    a = 200;
    while (a--);
    ms--;
  }
}

/*************************************************************************
                        往 OLED 中写入一字节数据
--------------------------------------------------------------------------
mode：传输模式  data：一字节数据
*************************************************************************/
static void OLED_SPI_WriteByte (uint8_t mode, uint8_t data)
{
  BitStatus bit;
  uint8_t i;
  
  if (mode == OLED_CMD)
  {
    OLED_DC_CMD();
  }
  else
  {
    OLED_DC_DATA();
  }
  
  OLED_SCK_LOW();
  
  for (i = 0; i < 8; i++)
  {
    OLED_SCK_LOW();
    bit = (BitStatus)(data & 0x80);
    
    if (bit == RESET)
    {
      OLED_SDA_LOW();
    }
    else
    {
      OLED_SDA_HIGH();
    }
    
    OLED_SCK_HIGH();
    data <<= 1;
  }
  
  OLED_SCK_HIGH();
  OLED_DC_DATA();
}

/*************************************************************************
                           往 OLED 写入命令字 
--------------------------------------------------------------------------
cmd：命令字
*************************************************************************/
void OLED_SPI_WriteCmd (uint8_t cmd)
{
  OLED_SPI_WriteByte(OLED_CMD, cmd);
}

/*************************************************************************
                          往 OLED 写入数据字  
--------------------------------------------------------------------------
data：数据字
*************************************************************************/
void OLED_SPI_WriteData (uint8_t data)
{
  OLED_SPI_WriteByte(OLED_DATA, data);
}

/*************************************************************************
                          初始化 OLED 引脚  
--------------------------------------------------------------------------
无参数
*************************************************************************/
static void OLED_SPI_GPIO_Init (void)
{
  GPIO_Init(OLED_SCK_PORT, OLED_SCK_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(OLED_RES_PORT, OLED_RES_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(OLED_DC_PORT,  OLED_DC_PIN,  GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(OLED_CS_PORT,  OLED_CS_PIN,  GPIO_MODE_OUT_PP_HIGH_FAST);
}

/*************************************************************************
                            初始化 OLED 
--------------------------------------------------------------------------
无参数
*************************************************************************/
void OLED_SPI_Init (void)
{
  OLED_SPI_GPIO_Init();
  OLED_CS_LOW();
  
  OLED_SCK_HIGH();
  OLED_RES_LOW();
  OLED_DLY_ms (100);
  OLED_RES_HIGH();
  
  OLED_SPI_WriteCmd(0xAE);         // Display Off (0x00)
  OLED_SPI_WriteCmd(0xD5);
  OLED_SPI_WriteCmd(0x80);         // Set Clock as 100 Frames/Sec
  OLED_SPI_WriteCmd(0xA8);
  OLED_SPI_WriteCmd(0x3F);         // 1/64 Duty (0x0F~0x3F)
  OLED_SPI_WriteCmd(0xD3);
  OLED_SPI_WriteCmd(0x00);         // Shift Mapping RAM Counter (0x00~0x3F)
  OLED_SPI_WriteCmd(0x40 | 0x00);  // Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_SPI_WriteCmd(0x8D);
  OLED_SPI_WriteCmd(0x10 | 0x04);  // Enable Embedded DC/DC Converter (0x00/0x04)
  OLED_SPI_WriteCmd(0x20);
  OLED_SPI_WriteCmd(0x02);         // Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_SPI_WriteCmd(0xA0 | 0x01);  // Set SEG/Column Mapping    
  OLED_SPI_WriteCmd(0xC0);         // Set COM/x Scan Direction   
  OLED_SPI_WriteCmd(0xDA);
  OLED_SPI_WriteCmd(0x02 | 0x10);  // Set Sequential Configuration (0x00/0x10)
  OLED_SPI_WriteCmd(0x81);
  OLED_SPI_WriteCmd(0xCF);         // Set SEG Output Current
  OLED_SPI_WriteCmd(0xD9);
  OLED_SPI_WriteCmd(0xF1);         // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_SPI_WriteCmd(0xDB);
  OLED_SPI_WriteCmd(0x40);         // Set VCOM Deselect Level
  OLED_SPI_WriteCmd(0xA4 | 0x00);  // Disable Entire Display On (0x00/0x01)
  OLED_SPI_WriteCmd(0xA6 | 0x00);  // Disable Inverse Display On (0x00/0x01)
  OLED_SPI_WriteCmd(0xAE | 0x01);  // Display On (0x01)
  
  OLED_Clear();         // 清屏
}

/*************************************************************************
                               唤醒 OLED
--------------------------------------------------------------------------
无参数
*************************************************************************/
void OLED_ON (void)
{
  OLED_SPI_WriteCmd(0X8D);  // 设置电荷泵
  OLED_SPI_WriteCmd(0X14);  // 开启电荷泵
  OLED_SPI_WriteCmd(0XAF);  // OLED唤醒
}

/*************************************************************************
                              休眠 OLED
--------------------------------------------------------------------------
无参数
*************************************************************************/
void OLED_OFF (void)
{
  OLED_SPI_WriteCmd(0X8D);  // 设置电荷泵
  OLED_SPI_WriteCmd(0X10);  // 关闭电荷泵
  OLED_SPI_WriteCmd(0XAE);  // OLED休眠
}

/*************************************************************************
                            OLED 刷新显示
--------------------------------------------------------------------------
无参数
*************************************************************************/
void OLED_Refresh_Gram (void)
{   
  uint8_t i, j;
  
  for(i = 0; i < 8; i++)  
  {  
    OLED_SPI_WriteCmd(0xB0 + i);        // 设置页地址（0~7）
    OLED_SPI_WriteCmd(0x00);            // 设置显示位置—列低地址
    OLED_SPI_WriteCmd(0x10);            // 设置显示位置—列高地址 
    
    for(j = 0; j < 128; j++)
    {
      OLED_SPI_WriteData(OLED_GRAM[j][i]);
    }
  }
  
}

/*************************************************************************
                              OLED 清屏
--------------------------------------------------------------------------
无参数
*************************************************************************/
void OLED_Clear (void)
{
  uint8_t i, j;  
    
  for(i = 0; i < 8; i++)
  {
    for(j = 0; j < 128; j++)
    {
      OLED_GRAM[j][i] = 0X00; 
    }
  }
  
  OLED_Refresh_Gram();  // 更新显示
}

/*************************************************************************
                               OLED 画点 
--------------------------------------------------------------------------
x，y：坐标  mode：阳码/阴码填充
*************************************************************************/
static void OLED_DrawPoint (uint8_t x, uint8_t y, uint8_t mode)
{    
  uint8_t pos, bx;
  uint8_t temp = 0;
  
  if (x > 127|| y > 63)         // 超出范围
  {
    return;       
  }
  
  pos = 7 - y / 8;
  bx  = y % 8;
  temp= 1 << (7 - bx);
  
  if (mode == OLED_ANODE)
  {
    OLED_GRAM[x][pos] |= temp;
  }
  else 
  {
    OLED_GRAM[x][pos] &= ~temp;
  }
}

/*************************************************************************
                            OLED 方块填充
--------------------------------------------------------------------------
x1，y1：左上角坐标  x2，y2：右下角坐标  mode：阳码/阴码填充
*************************************************************************/
static void OLED_Fill (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)  
{      
  uint8_t x, y;  
  
  for (x = x1; x <= x2; x++)
  {
     for (y = y1; y <= y2; y++)
     {
        OLED_DrawPoint (x, y, mode);
     }
  }   
  
  OLED_Refresh_Gram();          // 更新显示
}

/*************************************************************************
                            OLED 打印一个字符
--------------------------------------------------------------------------
x，y：坐标  ch：字符  size：字符大小  mode：阳码/阴码
*************************************************************************/
static void OLED_ShowChar (uint8_t x, uint8_t y, uint8_t ch, uint8_t size, uint8_t mode)
{
  uint8_t temp;
  uint8_t i, j;
  uint8_t y0;
  uint8_t csize;
  
  y0 = y;
  ch = ch - ' ';
  csize = (size / 8 + ((size % 8) ? 1 : 0) ) * (size / 2);      //得到字体一个字符对应点阵集所占的字节数
  
  for(i = 0; i < csize; i++)
  {
    switch (size)
    {
    case OLED_FONT_SIZE_12:
      temp = ascii_1206[ch][i];
      break;
    case OLED_FONT_SIZE_16:
      temp = ascii_1608[ch][i];
      break;
    default:
      return;
    }
    
    for(j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        OLED_DrawPoint (x, y, mode);
      }
      else 
      {
        OLED_DrawPoint (x, y, !mode);
      }
      
      temp <<= 1;
      y++;
      
      if ((y - y0) == size)
      {
        y = y0;
        x++;
        break;   // 退出循环
      }
      
    } 
  }
}

/*************************************************************************
                           OLED 打印一个字符串 
--------------------------------------------------------------------------
x，y：坐标  str：字符串  size：字符大小
*************************************************************************/
void OLED_ShowString (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size)
{       
  while( (*str <= '~') && (*str >= ' ') )           //判断是不是非法字符!
  {       
    if ( x > (128 - (size / 2)) )
    {
      x = 0;
      y += size;
    }
    
    if ( y > (64 - size) )
    {
      x = 0;
      y = 0;
      OLED_Clear();
    }
    
    OLED_ShowChar (x, y, *str, size, OLED_ANODE);  
    
    x += size / 2;
    str++;
  }  
}   

/*************************************************************************
                            OLED 打印一个中文字
--------------------------------------------------------------------------
x，y：坐标  *str：中文数组首地址  size：字符大小  mode：阳码/阴码
*************************************************************************/
static void OLED_ShowChar_CH (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size, uint8_t mode)
{
  uint8_t temp;
  uint8_t i, j;
  uint8_t y0;
  uint8_t csize;
  
  y0 = y;
  csize = (size / 8 + ((size % 8) ? 1 : 0) ) * (size / 2);      //得到字体一个字符对应点阵集所占的字节数
  
  for(i = 0; i < csize; i++)
  {
    temp = *(str + i);
    
    for(j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        OLED_DrawPoint (x, y, mode);
      }
      else 
      {
        OLED_DrawPoint (x, y, !mode);
      }
      
      temp <<= 1;
      y++;
      
      if ((y - y0) == size)
      {
        y = y0;
        x++;
        break;   // 退出循环
      }
      
    } 
  }
}

/*************************************************************************
                            OLED 打印一行中文字
--------------------------------------------------------------------------
x，y：坐标  *str：中文数组首地址  size：字符大小  num：多少字  mode：阳码/阴码
*************************************************************************/
void OLED_ShowChinese (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size, uint8_t num)
{
  uint16_t i;
  
  for (i = 0; i < num * 2; i++)
  {       
    if ( x > (128 - (size / 2)) )
    {
      x = 0;
      y += size;
    }
    
    if ( y > (64 - size) )
    {
      x = 0;
      y = 0;
      OLED_Clear();
    }
    
    OLED_ShowChar_CH (x, y, str, size, OLED_ANODE);  
    
    x += size / 2;
    str += size;
  }  
}

/*************************************************************************
                            OLED 打印 BMP 图片
--------------------------------------------------------------------------
x，y：左上角坐标  *bmp：BMP数组首地址  width，height：图片尺寸大小  
*************************************************************************/
void OLED_ShowPic (uint8_t x, uint8_t y, const uint8_t *pic, uint8_t width, uint8_t height, uint8_t mode)
{
  uint16_t i, j, size;
  uint8_t y0;
  uint8_t temp;
  
  if ((x + width > 128) || (y + height > 64))  
    return;    

  size = (uint16_t)( height / 8 + ((height % 8)? 1 : 0) ) * width;
  y0 = y;
  
  for (i = 0; i < size; i++)
  {
    temp = *(pic + i);
    
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        OLED_DrawPoint (x, y, mode);
      }
      else 
      {
        OLED_DrawPoint (x, y, !mode);
      }
      
      temp <<= 1;
      y++;
      
      if (y - y0 == height)
      {
        y = y0;
        x++;
        break;
      }
      
    }
  }
}

/*************************************************************************
                            OLED 垂直+水平滚动显示
--------------------------------------------------------------------------
start_page，end_page：起始/终止页地址  frame：滚动步长时间间隔，帧为单位
scroll_offset：垂直滚动偏移（0-63）  dir：滚动方向
--------------------------------------------------------------------------
注意：该函数需要在 OLED_Refresh_Gram 后调用
*************************************************************************/
void OLED_VerHorScroll (enum page_num start_page, enum page_num end_page, enum roll_frame frame, uint8_t scroll_offset, uint8_t dir)
{
  OLED_SPI_WriteCmd (0x2E);             //关闭滚动
  OLED_SPI_WriteCmd (0x29 + dir);       //水平垂直和水平滚动左右 29/2a
  OLED_SPI_WriteCmd (0x00);             //虚拟字节
  OLED_SPI_WriteCmd (start_page);       //起始页  
  OLED_SPI_WriteCmd (frame);            //滚动时间间隔
  OLED_SPI_WriteCmd (end_page);         //终止页
  OLED_SPI_WriteCmd (scroll_offset);    //垂直滚动偏移量
  OLED_SPI_WriteCmd (0x2F);
}

/*************************************************************************
                            OLED 水平滚动显示
--------------------------------------------------------------------------
start_page，end_page：起始/终止页地址  frame：滚动步长时间间隔，帧为单位
dir：滚动方向
--------------------------------------------------------------------------
注意：该函数需要在 OLED_Refresh_Gram 后调用
*************************************************************************/
void OLED_HorScroll (enum page_num start_page, enum page_num end_page, enum roll_frame frame, uint8_t dir)
{
  OLED_SPI_WriteCmd (0x2E);             //关闭滚动
  OLED_SPI_WriteCmd (0x26 + dir);       //水平向左或者右滚动 26/27
  OLED_SPI_WriteCmd (0x00);             //虚拟字节
  OLED_SPI_WriteCmd (start_page);       //起始页
  OLED_SPI_WriteCmd (frame);            //滚动时间间隔
  OLED_SPI_WriteCmd (end_page);         //终止页
  OLED_SPI_WriteCmd (0x00);             //虚拟字节（必须加上）
  OLED_SPI_WriteCmd (0xFF);             //虚拟字节（必须加上）
  OLED_SPI_WriteCmd (0x2F);             //开启滚动
}

/*************************************************************************
                            OLED 垂直滚动显示
--------------------------------------------------------------------------
start_page，end_page：起始/终止页地址  frame：滚动步长时间间隔，帧为单位
scroll_offset：垂直滚动偏移（0-63）  dir：滚动方向
--------------------------------------------------------------------------
注意：该函数需要在 OLED_Refresh_Gram 后调用
*************************************************************************/
void OLED_VerScroll (enum page_num start_page, enum page_num end_page, enum roll_frame frame, uint8_t scroll_offset, uint8_t dir)
{
  OLED_SPI_WriteCmd (0x2E);             //关闭滚动
  OLED_SPI_WriteCmd (0x29 + dir);       //水平垂直和水平滚动左右 29/2a
  OLED_SPI_WriteCmd (0x00);             //虚拟字节
  OLED_SPI_WriteCmd (start_page);       //起始页  
  OLED_SPI_WriteCmd (frame);            //滚动时间间隔
  OLED_SPI_WriteCmd (end_page);         //终止页
  OLED_SPI_WriteCmd (scroll_offset);    //垂直滚动偏移量
  OLED_SPI_WriteCmd (0xA3);        //开启滚动
  OLED_SPI_WriteCmd (0);        //开启滚动
  OLED_SPI_WriteCmd (16);        //开启滚动
  OLED_SPI_WriteCmd (0x2F);             //开启滚动
}





