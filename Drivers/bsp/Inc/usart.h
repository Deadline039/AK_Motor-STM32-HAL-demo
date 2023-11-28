/**
 * @file    usart.h
 * @date    2023/7/24
 * @version 0.3
 * @note    此文件主要用于STM32F4串口(usart1->uart8)的初始化函数以及中断服务函数
 *          如果启用了串口1,printf函数将会被重定义为从串口1输出
 * @warning 要使用相关函数请预先在此文件里定义
 */

#ifndef __USART_H
#define __USART_H


#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "sys.h"

/* 长度定义 */
#define USART_REC_LEN 200 /* 定义USART最大接收字节数 200 */
#define TX_BUF_LEN 256    /* 定义发送字节数 256 */
#define RXBUFFERSIZE 1    /* 定义接收缓冲区大小 */

/**
 * 是否使用串口,启用就在此处define
 * @warning 未定义的串口,相关函数将无法使用,编译不通过!
 */
#define EN_USART1
// #define EN_USART2
// #define EN_USART3
// #define EN_UART4
// #define EN_UART5
// #define EN_USART6
// #define EN_UART7
// #define EN_UART8

/**
 * 是否启用串口接收,不启用就将1改为0或者直接注释
 * @warning 未定义为1的串口,串口接收的变量无法使用!
 * @warning 如果串口未定义不能启用对应的串口中断!!!!!
 */
#define EN_USART1_RX 1
// #define EN_USART2_RX 1
// #define EN_USART3_RX 1
// #define EN_UART4_RX 1
// #define EN_UART5_RX 1
// #define EN_USART6_RX 1
// #define EN_UART7_RX 1
// #define EN_UART8_RX 1

#ifdef EN_USART1
/* 句柄 */
extern UART_HandleTypeDef USART1_Handler;
/* 接受buf */
#if EN_USART1_RX
extern uint8_t USART1_RX_BUF[USART_REC_LEN];
extern uint16_t USART1_RX_STA;
extern uint8_t aRxBuffer1[RXBUFFERSIZE];
#endif

void USART1_Init(uint32_t bound);
#endif

#ifdef EN_USART2
/* 句柄 */
extern UART_HandleTypeDef USART2_Handler;
/* 接受buf */
#if EN_USART2_RX
extern uint8_t USART2_RX_BUF[USART_REC_LEN];
extern uint16_t USART2_RX_STA;
extern uint8_t aRxBuffer2[RXBUFFERSIZE];
#endif

void USART2_Init(uint32_t bound);
#endif

#ifdef EN_USART3
/* 句柄 */
extern UART_HandleTypeDef USART3_Handler;
/* 接受buf */
#if EN_USART3_RX
extern uint8_t USART3_RX_BUF[USART_REC_LEN];
extern uint16_t USART3_RX_STA;
extern uint8_t aRxBuffer3[RXBUFFERSIZE];
#endif
void USART3_Init(uint32_t bound);
#endif

#ifdef EN_UART4
/* 句柄 */
extern UART_HandleTypeDef UART4_Handler;
/* 接受buf */
#if EN_UART4_RX
extern uint8_t UART4_RX_BUF[USART_REC_LEN];
extern uint16_t UART4_RX_STA;
extern uint8_t aRxBuffer4[RXBUFFERSIZE];
#endif

void UART4_Init(uint32_t bound);
#endif

#ifdef EN_UART5
/* 句柄 */
extern UART_HandleTypeDef UART5_Handler;
/* 接受buf */
#if EN_UART5_RX
extern uint8_t UART5_RX_BUF[USART_REC_LEN];
extern uint16_t UART5_RX_STA;
extern uint8_t aRxBuffer5[RXBUFFERSIZE];
#endif

void UART5_Init(uint32_t bound);
#endif

#ifdef EN_USART6
/* 句柄 */
extern UART_HandleTypeDef USART6_Handler;
/* 接受buf */
#if EN_USART6_RX
extern uint8_t USART6_RX_BUF[USART_REC_LEN];
extern uint16_t USART6_RX_STA;
extern uint8_t aRxBuffer6[RXBUFFERSIZE];
#endif

void USART6_Init(uint32_t bound);
#endif

#ifdef EN_UART7
/* 句柄 */
extern UART_HandleTypeDef UART7_Handler;
/* 接受buf */
#if EN_UART7_RX
extern uint8_t UART7_RX_BUF[USART_REC_LEN];
extern uint16_t UART7_RX_STA;
extern uint8_t aRxBuffer7[RXBUFFERSIZE];
#endif

void UART7_Init(uint32_t bound);
#endif

#ifdef EN_UART8
/* 句柄 */
extern UART_HandleTypeDef UART8_Handler;
/* 接受buf */
#if EN_UART8_RX
extern uint8_t UART8_RX_BUF[USART_REC_LEN];
extern uint16_t UART8_RX_STA;
extern uint8_t aRxBuffer8[RXBUFFERSIZE];
#endif

void UART8_Init(uint32_t bound);
#endif

void uart_print(UART_HandleTypeDef* uart, const char* __format, ...);

#endif /* __USART_H */
