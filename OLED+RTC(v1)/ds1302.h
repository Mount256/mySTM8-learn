#ifndef __DS1302_H
#define __DS1302_H

/****************************驱动 RTC 芯片 DS1302******************************/

/* Includes ------------------------------------------------------------------*/

#include "stm8s.h"

/* Defines -------------------------------------------------------------------*/

#define RTC_RESET_TIME_EN       0u

#define RTC_SCK_PORT            (GPIOD)         
#define RTC_SCK_PIN             (GPIO_PIN_2)            // PD2
#define RTC_SCK_HIGH()          GPIO_WriteHigh(RTC_SCK_PORT, RTC_SCK_PIN)
#define RTC_SCK_LOW()           GPIO_WriteLow (RTC_SCK_PORT, RTC_SCK_PIN)

#define RTC_IO_PORT             (GPIOD)
#define RTC_IO_PIN              (GPIO_PIN_3)            // PD3

#define RTC_IO_IN()             GPIO_Init(RTC_IO_PORT, RTC_IO_PIN, GPIO_MODE_IN_PU_NO_IT)
#define RTC_IO_STATUS()         GPIO_ReadInputPin(RTC_IO_PORT, RTC_IO_PIN)

#define RTC_IO_OUT()            GPIO_Init(RTC_IO_PORT, RTC_IO_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW) 
#define RTC_IO_HIGH()           GPIO_WriteHigh(RTC_IO_PORT, RTC_IO_PIN)
#define RTC_IO_LOW()            GPIO_WriteLow (RTC_IO_PORT, RTC_IO_PIN)

#define RTC_RST_PORT            (GPIOD)
#define RTC_RST_PIN             (GPIO_PIN_7)            // PD7
#define RTC_RST_HIGH()          GPIO_WriteHigh(RTC_RST_PORT, RTC_RST_PIN)
#define RTC_RST_LOW()           GPIO_WriteLow (RTC_RST_PORT, RTC_RST_PIN)

/* Values --------------------------------------------------------------------*/

typedef struct Time
{
  uint8_t year;         // year       0-99 
  uint8_t month;        // month      01-12
  uint8_t day;          // day        01-28,29,30,31
  uint8_t week;         // week       01-07
  uint8_t hour;         // hour       01-12 or 00-23
  uint8_t minute;       // minute     00-59
  uint8_t second;       // second     00-59
}TimeTypeDef;

static TimeTypeDef TimeBuffer;   // 数据缓冲区（8421-BCD码）

/* Functions -----------------------------------------------------------------*/

void DS1302_Init (void);

static void    DS1302_WriteByte (uint8_t byte);
static uint8_t DS1302_ReadByte  (void);
static void    DS1302_WriteData (uint8_t addr, uint8_t data);
static uint8_t DS1302_ReadData  (uint8_t addr);

TimeTypeDef DS1302_ReadTime  (void);
void        DS1302_WriteTime (TimeTypeDef *TimeDisplay);

static uint8_t DectoBCD (uint8_t num);
static uint8_t BCDtoDec (uint8_t num);

static void DS1302_DLY_ms(uint16_t nCount);
static void DS1302_DLY_us(uint16_t nCount);

#endif /* __DS1302_H */
