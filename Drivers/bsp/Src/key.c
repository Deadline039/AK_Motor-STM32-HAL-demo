/**
 * @file    key.c
 * @author  Deadline--
 * @brief   按键检测及初始化
 * @version 0.1
 * @date    2023-10-20
 */

#include "key.h"
#include "delay.h"

/**
 * @brief 初始化按键
 * @note
 * KEY0->PH3, KEY1->PH2, KEY2->PC13, WKUP->PA0
 */
void KEY_Init(void) {
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE(); /* 开启GPIOA时钟 */
    __HAL_RCC_GPIOC_CLK_ENABLE(); /* 开启GPIOC时钟 */
    __HAL_RCC_GPIOH_CLK_ENABLE(); /* 开启GPIOH时钟 */

    GPIO_Initure.Pin = GPIO_PIN_0;        /* PA0 */
    GPIO_Initure.Mode = GPIO_MODE_INPUT;  /* 输入 */
    GPIO_Initure.Pull = GPIO_PULLDOWN;    /* 下拉 */
    GPIO_Initure.Speed = GPIO_SPEED_HIGH; /* 高速 */
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    GPIO_Initure.Pin = GPIO_PIN_13;       /* PC13 */
    GPIO_Initure.Mode = GPIO_MODE_INPUT;  /* 输入 */
    GPIO_Initure.Pull = GPIO_PULLUP;      /* 上拉 */
    GPIO_Initure.Speed = GPIO_SPEED_HIGH; /* 高速 */
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);

    GPIO_Initure.Pin = GPIO_PIN_2 | GPIO_PIN_3; /* PH2,3 */
    HAL_GPIO_Init(GPIOH, &GPIO_Initure);
}
/**
 * @brief 按键扫描
 * @param mode 是否支持连按
 *  @arg 0-不支持连按, 1-支持连按
 * @return 按下的按键
 *  @retval 按下:KEY0_PRES ~ WKUP_PRES
 *  @retval 未按下:0
 * @note 注意此函数有响应优先级,KEY0 > KEY1 > KEY2 > WK_UP
 */
uint8_t KEY_Scan(uint8_t mode) {
    static uint8_t key_up = 1; /* 按键松开标志 */
    if (mode == 1) {
        key_up = 1; /* 支持连按 */
    }
    if (key_up == 1 && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1)) {
        delay_ms(10);
        key_up = 0;
        if (KEY0 == 0) {
            return KEY0_PRES;
        } else if (KEY1 == 0) {
            return KEY1_PRES;
        } else if (KEY2 == 0) {
            return KEY2_PRES;
        } else if (WK_UP == 1) {
            return WKUP_PRES;
        }
    } else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0) {
        key_up = 1;
    }
    return 0; /* 无按键按下 */
}
