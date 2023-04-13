#ifndef __DHT11_H
#define __DHT11_H

/* Includes ------------------------------------------------------------------*/

#include "stm8s.h"
#include "uart.h"

/* Defines -------------------------------------------------------------------*/

#define DHT11_DQ_PORT  (GPIOE)
#define DHT11_DQ_PIN   (GPIO_PIN_2)

#define DHT11_DQ_IN()      GPIO_Init(DHT11_DQ_PORT, DHT11_DQ_PIN, GPIO_MODE_IN_PU_NO_IT) 
#define DHT11_DQ_STATUS()  GPIO_ReadInputPin(DHT11_DQ_PORT, DHT11_DQ_PIN)

#define DHT11_DQ_OUT()     GPIO_Init(DHT11_DQ_PORT, DHT11_DQ_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW)
#define DHT11_DQ_HIGH()    GPIO_WriteHigh(DHT11_DQ_PORT, DHT11_DQ_PIN)
#define DHT11_DQ_LOW()     GPIO_WriteLow (DHT11_DQ_PORT, DHT11_DQ_PIN)

#define RESPONSE_MAX_TIME_1     100
#define RESPONSE_MAX_TIME_2     100

#define READ_LOW_TIME           50
#define READ_HIGH_TIME          30

/* Values --------------------------------------------------------------------*/

typedef struct TempHumiData
{
  uint8_t HumiMSB;
  uint8_t HumiLSB;
  uint8_t TempMSB;
  uint8_t TempLSB;
  uint8_t Parity;
  ErrorStatus Flag;
}TempHumiDataTypeDef;

/* Functions -----------------------------------------------------------------*/

void DHT11_Init (void);
void DHT11_Reset (void);
ErrorStatus DHT11_Check (void);

static BitStatus DHT11_ReadBit (void);
static uint8_t DHT11_ReadByte (void);
TempHumiDataTypeDef DHT11_ReadData (void);

static void DHT11_DLY_ms (uint16_t nCount);
static void DHT11_DLY_us (uint16_t nCount);

#endif /* __DHT11_H */
