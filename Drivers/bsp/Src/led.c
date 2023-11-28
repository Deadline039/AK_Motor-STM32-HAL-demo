/**
 * @file    led.c
 * @author  Deadline--
 * @brief   LED驱动代码
 * @version 0.1
 * @date    2023-10-20
 */

#include "led.h"

/**
 * @brief LED初始化
 *
 */
void LED_Init(void) {
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE(); /* 开启GPIOB时钟 */

    GPIO_Initure.Pin = GPIO_PIN_0;             /* PB0 */
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;   /* 推挽输出 */
    GPIO_Initure.Pull = GPIO_PULLUP;           /* 上拉 */
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);

    GPIO_Initure.Pin = GPIO_PIN_1; /* PB1 */
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,
                      GPIO_PIN_SET); /* PB0置1, 默认初始化后灯灭 */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,
                      GPIO_PIN_SET); /* PB1置1, 默认初始化后灯灭 */
}
