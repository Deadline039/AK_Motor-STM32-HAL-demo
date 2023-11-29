/**
 * @file    main.cpp
 * @author  Deadline--
 * @brief   AK80示例代码, 使用python脚本可以控制电机
 * @version 0.2
 * @date    2023-11-28
 */

#include "main.hpp"

/**
 * @brief 主函数
 *
 * @return int
 */
int main(void) {
    bsp_init();
    while (1) {
        mit_demo();
    }
}
/**
 * @brief 板驱动初始化
 *
 */
void bsp_init(void) {
    HAL_Init();
    sys_stm32_clock_init(360, 25, 2, 8);
    delay_init(180);
    USART1_Init(115200);
    LED_Init();
    KEY_Init();
    CAN1_Init(CAN_SJW_1TQ, CAN_BS2_8TQ, CAN_BS1_6TQ, 3, CAN_MODE_NORMAL);
}
/**
 * @brief 分割字符串
 *
 * @param[in] str 待分割的字符串
 * @param[in] delim 分割符
 * @param[out] save 保存剩下的字符串指针
 * @return char* 剩下的字符串指针
 */
char* my_strtok_r(char* str, const char* delim, char** save) {
    char *res, *last;

    if (!save)
        return strtok(str, delim);
    if (!str && !(str = *save))
        return NULL;
    last = str + strlen(str);
    if ((*save = res = strtok(str, delim))) {
        *save += strlen(res);
        if (*save < last)
            (*save)++;
        else
            *save = NULL;
    }
    return res;
}
/**
 * @brief 伺服模式demo程序
 *
 */
void servo_demo(void) {
    float moto_value[3] = {0.0f};
    /* 实例化AK电机对象 */
    AK_Motor_Class AK_Servo_Instance(104U, AK80_8);
    while (1) {
        if (USART1_RX_STA & 0x8000) {
            LED1_TOGGLE();
            delay_ms(100);
            LED1_TOGGLE();
            char* save_ptr;
            if (strcmp((const char*)USART1_RX_BUF, "origin") == 0) {
                AK_Servo_Instance.comm_can_set_origin(0);
            }
            moto_value[0] =
                atof(my_strtok_r((char*)USART1_RX_BUF, ",", &save_ptr));
            for (uint8_t i = 0; i < 2; i++) {
                moto_value[i + 1] = atof(my_strtok_r(NULL, ",", &save_ptr));
            }
            USART1_RX_STA = 0;
        }
        if (moto_value[0] != 0) {
            AK_Servo_Instance.comm_can_set_pos(moto_value[0]);
        } else if (moto_value[1] != 0) {
            AK_Servo_Instance.comm_can_set_rpm(moto_value[1]);
        } else if (moto_value[2] != 0) {
            AK_Servo_Instance.comm_can_set_current(moto_value[2]);
        }
        delay_ms(25);
    }
}

/**
 * @brief 运控模式demo程序
 *
 */
void mit_demo(void) {
    float moto_value[5] = {0.0f};

    /* 实例化AK电机对象 */
    AK_Motor_Class AK_MIT_Instance(01U, AK80_8);

    /* 等待KEY0按下, 进入控制 */
    while (KEY_Scan(0) != KEY0_PRES)
        ;
    LED0_TOGGLE();
    AK_MIT_Instance.mit_can_enter_motor();
    uint8_t key;
    while (1) {
        key = KEY_Scan(0);
        if (key == KEY1_PRES) {
            /* 按下KEY1退出控制 */
            LED0_TOGGLE();
            AK_MIT_Instance.mit_can_exit_motor();
            return;
        }
        if (USART1_RX_STA & 0x8000) {
            LED1_TOGGLE();
            delay_ms(100);
            LED1_TOGGLE();
            char* save_ptr;
            if (strcmp((const char*)USART1_RX_BUF, "origin") == 0) {
                AK_MIT_Instance.mit_can_set_origin();
            }
            moto_value[0] =
                atof(my_strtok_r((char*)USART1_RX_BUF, ",", &save_ptr));
            for (uint8_t i = 0; i < 4; i++) {
                moto_value[i + 1] = atof(my_strtok_r(NULL, ",", &save_ptr));
            }
            USART1_RX_STA = 0;
        }
        AK_MIT_Instance.mit_can_send_data(moto_value[0], moto_value[1],
                                          moto_value[2], moto_value[3],
                                          moto_value[4]);
        delay_ms(25);
    }
}
