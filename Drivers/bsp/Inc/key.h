/**
 * @file    key.h
 * @author  Deadline--
 * @brief   按键检测及初始化
 * @version 0.1
 * @date    2023-10-20
 */

#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0 HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_3)
#define KEY1 HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_2)
#define KEY2 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)
#define WK_UP HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

#define KEY0_PRES 1
#define KEY1_PRES 2
#define KEY2_PRES 3
#define WKUP_PRES 4

void KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);

#endif /* __KEY_H */
