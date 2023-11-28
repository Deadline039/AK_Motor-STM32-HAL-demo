/**
 * @file    led.h
 * @author  Deadline--
 * @brief   LED驱动代码
 * @version 0.1
 * @date    2023-10-20
 */

#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "stdarg.h"
#include "string.h"

#define LED0(x)                                   \
    x ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET) \
      : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET) /* LED0 */
#define LED1(x)                                   \
    x ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET) \
      : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET) /* LED1 */

#define LED0_TOGGLE() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0) /* 翻转LED0 */
#define LED1_TOGGLE() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1) /* 翻转LED1 */

void LED_Init(void);

#endif /* __LED_H */
