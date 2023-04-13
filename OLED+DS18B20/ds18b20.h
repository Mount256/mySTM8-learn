#ifndef __DS18B20_H
#define __DS18B20_H

/***********DS18B20����***********/
/*****Ҫ��RESET�ж�*****/

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
  uint8_t sign;         /* ����λ��1��ʾ������0��ʾ�Ǹ��� */
  ErrorStatus flag;     /* ��������Ƿ���Ч */
}TemperatureTypeDef;

/***********Function***********/
static void DS18B20_DLY_ms(uint16_t nCount);
static void DS18B20_DLY_us(uint16_t nCount);

void DS18B20_Reset(void);               /* ��DS18B20���͸�λ�ź� */
ErrorStatus DS18B20_Check(void);        /* ���DS18B20�������� */
static BitStatus DS18B20_ReadBit(void);        /* ��DS18B20��һ��λ   */
static uint8_t DS18B20_ReadByte(void);         /* ��DS18B20��һ���ֽ� */
static void DS18B20_WriteByte(uint8_t cmd);    /* ��DS18B20дһ���ֽ� */
void DS18B20_GetTemperature(TemperatureTypeDef* Temperature);   /* ��ʼ�¶�ת������ȡ�¶����� */

#endif /* __DS18B20_H */
