#ifndef __OLED_SPI_H
#define __OLED_SPI_H

/*******************模拟四线 SPI 驱动 0.96寸OLED（128x64）**********************/

/* Includes ------------------------------------------------------------------*/

#include "stm8s.h"
#include "oled_delay.h"
#include "oled_font.h"

/* Defines -------------------------------------------------------------------*/

#define OLED_CMD            0u          /* 命令模式 */
#define OLED_DATA           1u          /* 数据模式 */

#define OLED_CATHODE        0u          /* 阴码 */
#define OLED_ANODE          1u          /* 阳码 */

#define OLED_FONT_SIZE_12       12
#define OLED_FONT_SIZE_16       16

#define OLED_SCK_PORT           (GPIOB) 
#define OLED_SCK_PIN            (GPIO_PIN_5) /* PB5 (OLED_D0)  */

#define OLED_SDA_PORT           (GPIOB) 
#define OLED_SDA_PIN            (GPIO_PIN_4) /* PB4 (OLED_D1)  */

#define OLED_RES_PORT           (GPIOD) 
#define OLED_RES_PIN            (GPIO_PIN_0) /* PD0 (OLED_RES) */

#define OLED_DC_PORT            (GPIOG) 
#define OLED_DC_PIN             (GPIO_PIN_1) /* PG1 (OLED_DC)  */

#define OLED_CS_PORT            (GPIOC) 
#define OLED_CS_PIN             (GPIO_PIN_6) /* PC6 (OLED_CS)  */

#define OLED_SCK_LOW()         GPIO_WriteLow (OLED_SCK_PORT, OLED_SCK_PIN)
#define OLED_SCK_HIGH()        GPIO_WriteHigh(OLED_SCK_PORT, OLED_SCK_PIN)

#define OLED_SDA_LOW()         GPIO_WriteLow (OLED_SDA_PORT, OLED_SDA_PIN)
#define OLED_SDA_HIGH()        GPIO_WriteHigh(OLED_SDA_PORT, OLED_SDA_PIN)

#define OLED_RES_LOW()         GPIO_WriteLow (OLED_RES_PORT, OLED_RES_PIN)
#define OLED_RES_HIGH()        GPIO_WriteHigh(OLED_RES_PORT, OLED_RES_PIN)

#define OLED_DC_CMD()          GPIO_WriteLow (OLED_DC_PORT, OLED_DC_PIN)
#define OLED_DC_DATA()         GPIO_WriteHigh(OLED_DC_PORT, OLED_DC_PIN)

#define OLED_CS_LOW()          GPIO_WriteLow (OLED_CS_PORT, OLED_CS_PIN)
#define OLED_CS_HIGH()         GPIO_WriteHigh(OLED_CS_PORT, OLED_CS_PIN)

/* Functions -----------------------------------------------------------------*/

static void OLED_SPI_WriteByte (uint8_t mode, uint8_t data);
void OLED_SPI_WriteCmd (uint8_t cmd);
void OLED_SPI_WriteData (uint8_t data);
static void OLED_SPI_GPIO_Init (void);
void OLED_SPI_Init (void);

void OLED_ON (void);
void OLED_OFF (void);

void OLED_Refresh_Gram (void);
void OLED_Clear (void);

static void OLED_ShowChar (uint8_t x, uint8_t y, uint8_t ch, uint8_t size, uint8_t mode);
void OLED_ShowString (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size);

static void OLED_ShowChar_CH (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size, uint8_t mode);
void OLED_ShowChinese (uint8_t x, uint8_t y, const uint8_t *str, uint8_t size, uint8_t num);

void OLED_ShowPic (uint8_t x, uint8_t y, const uint8_t *pic, uint8_t width, uint8_t height, uint8_t mode);

#endif /* __OLED_SPI_H */
