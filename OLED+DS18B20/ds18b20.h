#ifndef __DS18B20_H
#define __DS18B20_H

/***********DS18B20驱动***********/
/*****要用RESET判断*****/

#include "stm8s.h"

/***********Definition***********/
#define RESPONSE_MAX_TIME_1  200
#define RESPONSE_MAX_TIME_2  240
#define DS18B20_DQ_PORT   (GPIOE)
#define DS18B20_DQ_PIN    (GPIO_PIN_2) /* PE2 */
#define DS18B20_DQ_OUT    GPIO_Init(DS18B20_DQ_PORT, DS18B20_DQ_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW) 
#define DS18B20_DQ_IN     GPIO_Init(DS18B20_DQ_PORT, DS18B20_DQ_PIN, GPIO_MODE_IN_PU_NO_IT)
#define DS18B20_DQ_HIGH   GPIO_WriteHigh(DS18B20_DQ_PORT, DS18B20_DQ_PIN)
#define DS18B20_DQ_LOW    GPIO_WriteLow (DS18B20_DQ_PORT, DS18B20_DQ_PIN)
#define DS18B20_DQ_STATUS GPIO_ReadInputPin(DS18B20_DQ_PORT, DS18B20_DQ_PIN)

/***********Structure***********/
typedef struct 
{
  float temp;
  uint8_t sign;         /* 符号位，1表示负数，0表示非负数 */
  ErrorStatus flag;     /* 检测数据是否有效 */
}TemperatureTypeDef;

/***********Function***********/
static void DS18B20_DLY_ms(uint16_t nCount);
static void DS18B20_DLY_us(uint16_t nCount);

void DS18B20_Reset(void);               /* 向DS18B20发送复位信号 */
ErrorStatus DS18B20_Check(void);        /* 检测DS18B20存在脉冲 */
static BitStatus DS18B20_ReadBit(void);        /* 从DS18B20读一个位   */
static uint8_t DS18B20_ReadByte(void);         /* 从DS18B20读一个字节 */
static void DS18B20_WriteByte(uint8_t cmd);    /* 从DS18B20写一个字节 */
void DS18B20_GetTemperature(TemperatureTypeDef* Temperature);   /* 开始温度转换及获取温度数据 */

#endif /* __DS18B20_H */
