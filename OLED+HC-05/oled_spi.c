#include "oled_spi.h"

uint8_t OLED_GRAM[128][8];

/*************************************************************************
                        �� OLED ��д��һ�ֽ�����
--------------------------------------------------------------------------
mode������ģʽ  data��һ�ֽ�����
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
                           �� OLED д�������� 
--------------------------------------------------------------------------
cmd��������
*************************************************************************/
void OLED_SPI_WriteCmd (uint8_t cmd)
{
  OLED_CS_LOW();
  OLED_SPI_WriteByte(OLED_CMD, cmd);
  OLED_CS_HIGH();
}

/*************************************************************************
                          �� OLED д��������  
--------------------------------------------------------------------------
data��������
*************************************************************************/
void OLED_SPI_WriteData (uint8_t data)
{
  OLED_CS_LOW();
  OLED_SPI_WriteByte(OLED_DATA, data);
  OLED_CS_HIGH();
}

/*************************************************************************
                          ��ʼ�� OLED ����  
--------------------------------------------------------------------------
�޲���
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
                            ��ʼ�� OLED 
--------------------------------------------------------------------------
�޲���
*************************************************************************/
void OLED_SPI_Init (void)
{
  OLED_SPI_GPIO_Init();
  
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
  
  OLED_Clear();         // ����
}

/*************************************************************************
                               ���� OLED
--------------------------------------------------------------------------
�޲���
*************************************************************************/
void OLED_ON (void)
{
  OLED_SPI_WriteCmd(0X8D);  // ���õ�ɱ�
  OLED_SPI_WriteCmd(0X14);  // ������ɱ�
  OLED_SPI_WriteCmd(0XAF);  // OLED����
}

/*************************************************************************
                              ���� OLED
--------------------------------------------------------------------------
�޲���
*************************************************************************/
void OLED_OFF (void)
{
  OLED_SPI_WriteCmd(0X8D);  // ���õ�ɱ�
  OLED_SPI_WriteCmd(0X10);  // �رյ�ɱ�
  OLED_SPI_WriteCmd(0XAE);  // OLED����
}

/*************************************************************************
                            OLED ˢ����ʾ
--------------------------------------------------------------------------
�޲���
*************************************************************************/
void OLED_Refresh_Gram (void)
{   
  uint8_t i, j;
  
  for(i = 0; i < 8; i++)  
  {  
    OLED_SPI_WriteCmd(0xB0 + i);        // ����ҳ��ַ��0~7��
    OLED_SPI_WriteCmd(0x00);            // ������ʾλ�á��е͵�ַ
    OLED_SPI_WriteCmd(0x10);            // ������ʾλ�á��иߵ�ַ 
    
    for(j = 0; j < 128; j++)
    {
      OLED_SPI_WriteData(OLED_GRAM[j][i]);
    }
  }
  
}

/*************************************************************************
                            OLED ˢ����ʾ 
--------------------------------------------------------------------------
�޲���
*************************************************************************/
static void OLED_Clear (void)
{
  uint8_t i, j;  
    
  for(i = 0; i < 8; i++)
  {
    for(j = 0; j < 128; j++)
    {
      OLED_GRAM[j][i] = 0X00; 
    }
  }
  
  OLED_Refresh_Gram();  // ������ʾ
}

/*************************************************************************
                               OLED ���� 
--------------------------------------------------------------------------
x��y������  mode������/�������
*************************************************************************/
void OLED_DrawPoint (uint8_t x, uint8_t y, uint8_t mode)
{    
  uint8_t pos, bx;
  uint8_t temp = 0;
  
  if (x > 127|| y > 63)         // ������Χ
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
                            OLED �������
--------------------------------------------------------------------------
x1��y1�����Ͻ�����  x2��y2�����½�����  mode������/�������
*************************************************************************/
void OLED_Fill (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)  
{      
  uint8_t x, y;  
  
  for (x = x1; x <= x2; x++)
  {
     for (y = y1; y <= y2; y++)
     {
        OLED_DrawPoint (x, y, mode);
     }
  }   
  
  OLED_Refresh_Gram();          // ������ʾ
}

/*************************************************************************
                            OLED ��ӡһ���ַ�
--------------------------------------------------------------------------
x��y������  ch���ַ�  size���ַ���С  mode������/����
*************************************************************************/
static void OLED_ShowChar (uint8_t x, uint8_t y, uint8_t ch, uint8_t size, uint8_t mode)
{
  uint8_t temp;
  uint8_t i, j;
  uint8_t y0;
  uint8_t csize;
  
  y0 = y;
  ch = ch - ' ';
  csize = (size / 8 + ((size % 8) ? 1 : 0) ) * (size / 2);      //�õ�����һ���ַ���Ӧ������ռ���ֽ���
  
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
        break;   // �˳�ѭ��
      }
      
    } 
  }
}

/*************************************************************************
                           OLED ��ӡһ���ַ��� 
--------------------------------------------------------------------------
x��y������  str���ַ���  size���ַ���С
*************************************************************************/
void OLED_ShowString (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size)
{       
  while( (*str <= '~') && (*str >= ' ') )           //�ж��ǲ��ǷǷ��ַ�!
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



