#ifndef __HC05_H
#define __HC05_H

#include "stm8s.h"

#define HC05_STATE_PORT (GPIOC)
#define HC05_STATE_PIN  (GPIO_PIN_5)      /* PC5 */

#define HC05_RX_PORT    (GPIOD)
#define HC05_RX_PIN     (GPIO_PIN_5)      /* PD5 */

#define HC05_TX_PORT    (GPIOD)
#define HC05_TX_PIN     (GPIO_PIN_6)      /* PD6 */

#define HC05_BT_EN_PORT (GPIOC)
#define HC05_BT_EN_PIN  (GPIO_PIN_7)      /* PC7 */

#endif /* __HC05_H */
