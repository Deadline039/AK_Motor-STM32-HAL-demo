/**
 * @file    main.hpp
 * @author  Deadline--
 * @brief   main函数头文件
 * @version 0.1
 * @date    2023-10-19
 * @note    此文件放置一些外部变量的声明
 */
#if (__ARMCC_VERSION >= 6010050)
/* 声明main无参数 */
__asm(".global __ARM_use_no_argv \n\t");
#endif /* __ARMCC_VERSION */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ak_motor.hpp"
#include "can.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "stdlib.h"
#include "string.h"
#include "sys.h"
#include "usart.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

int main(void);
void bsp_init(void);
char* my_strtok_r(char* str, const char* delim, char** save);
void servo_demo(void);
void mit_demo(void);
