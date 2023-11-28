/**
 * @file    main.h
 * @author  Deadline--
 * @brief   main函数头文件
 * @version 0.1
 * @date    2023-10-19
 * @note    此文件放置一些外部变量的声明
 */

/* 声明main无参数 */
__asm(".global __ARM_use_no_argv \n\t");

#include "ak80.h"
#include "can.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "stdlib.h"
#include "string.h"
#include "sys.h"
#include "usart.h"

int main(void);
