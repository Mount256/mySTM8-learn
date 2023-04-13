#ifndef __LCD1602_H
#define __LCD1602_H

/***********LCD1602 四线驱动***********/

#include "stm8s.h"
#include "delay.h"

/***********Definition***********/
#define LINE0   0x80
#define LINE1   0xC0

#define Rx_PORT (GPIOB)
#define RS_PIN (GPIO_PIN_4) /* PB4 */
#define RW_PIN (GPIO_PIN_3) /* PB3 */ /* NOT USE（RW接地） */
#define EN_PIN (GPIO_PIN_5) /* PB5 */
#define Rx_FOUR_PINS (RS_PIN | EN_PIN)
#define Rx_ALL_PINS (RS_PIN | RW_PIN | EN_PIN) /* NOT USE */

#define Dx_PORT (GPIOC)
#define D0_PIN (GPIO_PIN_0) /* PC0 */ /* NOT USE */
#define D1_PIN (GPIO_PIN_1) /* PC1 */ /* NOT USE */
#define D2_PIN (GPIO_PIN_2) /* PC2 */ /* NOT USE */
#define D3_PIN (GPIO_PIN_3) /* PC3 */ /* NOT USE */
#define D4_PIN (GPIO_PIN_4) /* PC4 */
#define D5_PIN (GPIO_PIN_5) /* PC5 */
#define D6_PIN (GPIO_PIN_6) /* PC6 */
#define D7_PIN (GPIO_PIN_7) /* PC7 */
#define Dx_FOUR_PINS (D4_PIN | D5_PIN | D6_PIN | D7_PIN)
#define Dx_ALL_PINS (D0_PIN | D1_PIN | D2_PIN | D3_PIN | D4_PIN | \
                     D5_PIN | D6_PIN | D7_PIN) /* NOT USE */

#define RS_LOW  GPIO_WriteLow (Rx_PORT, RS_PIN)
#define RS_HIGH GPIO_WriteHigh(Rx_PORT, RS_PIN)
#define EN_LOW  GPIO_WriteLow (Rx_PORT, EN_PIN)
#define EN_HIGH GPIO_WriteHigh(Rx_PORT, EN_PIN)
#define Dx_CLR  GPIO_Write(Dx_PORT, 0x00)

/***********Function***********/
static void LCD1602_Cmd(uint8_t cmd);
static void LCD1602_Data(uint8_t data);
void LCD1602_Init(void);
static void LCD1602_SetCursor(uint8_t x, uint8_t y);
void LCD1602_PrintStr(uint8_t x, uint8_t y, uint8_t *str);

#endif /* __LCD1602_H */
