/**
 * @file    usart.c
 * @date    2023/7/24
 * @version 0.3
 * @note    此文件主要用于STM32F4串口(usart1->uart8)的初始化函数以及中断服务函数
 *          如果启用了串口1,printf函数将会被重定义为从串口1输出
 * @warning 要使用相关函数请预先在usart.h里定义
 */

#include "usart.h"

/* 如果使用os,则包括下面的头文件即可 */
#if SYS_SUPPORT_OS
#include "os.h" /* os 使用 */
#endif

uint8_t USART_Tx_Buf[TX_BUF_LEN]; /* 发送缓冲区 */

#ifdef EN_USART1
UART_HandleTypeDef USART1_Handler;
#if EN_USART1_RX
uint8_t USART1_RX_BUF[USART_REC_LEN];
uint16_t USART1_RX_STA = 0;
uint8_t aRxBuffer1[RXBUFFERSIZE];
/**
 * @brief 串口1中断服务函数
 */
void USART1_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&USART1_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&USART1_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&USART1_Handler, (uint8_t*)aRxBuffer1,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口1初始化
 * @param bound 波特率
 */
void USART1_Init(uint32_t bound) {
    USART1_Handler.Instance = USART1;
    USART1_Handler.Init.BaudRate = bound;
    USART1_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    USART1_Handler.Init.StopBits = UART_STOPBITS_1;
    USART1_Handler.Init.Parity = UART_PARITY_NONE;
    USART1_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    USART1_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&USART1_Handler);
#if EN_USART1_RX
    HAL_UART_Receive_IT(&USART1_Handler, (uint8_t*)aRxBuffer1, RXBUFFERSIZE);
#endif
}

#endif

#ifdef EN_USART2
UART_HandleTypeDef USART2_Handler;
#if EN_USART2_RX
uint8_t USART2_RX_BUF[USART_REC_LEN];
uint16_t USART2_RX_STA = 0;
uint8_t aRxBuffer2[RXBUFFERSIZE];
/**
 * @brief 串口2中断服务函数
 */
void USART2_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&USART2_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&USART2_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&USART2_Handler, (uint8_t*)aRxBuffer2,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口2初始化
 * @param bound 波特率
 */
void USART2_Init(uint32_t bound) {
    USART2_Handler.Instance = USART2;
    USART2_Handler.Init.BaudRate = bound;
    USART2_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    USART2_Handler.Init.StopBits = UART_STOPBITS_1;
    USART2_Handler.Init.Parity = UART_PARITY_NONE;
    USART2_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    USART2_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&USART2_Handler);
#if EN_USART2_RX
    HAL_UART_Receive_IT(&USART2_Handler, (uint8_t*)aRxBuffer2, RXBUFFERSIZE);
#endif
}
#endif

#ifdef EN_USART3
UART_HandleTypeDef USART3_Handler;
#if EN_USART3_RX
uint8_t USART3_RX_BUF[USART_REC_LEN];
uint16_t USART3_RX_STA = 0;
uint8_t aRxBuffer3[RXBUFFERSIZE];
/**
 * @brief 串口3中断服务函数
 */
void USART3_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&USART3_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&USART3_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&USART3_Handler, (uint8_t*)aRxBuffer3,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口3初始化
 * @param bound 波特率
 */
void USART3_Init(uint32_t bound) {
    USART3_Handler.Instance = USART3;
    USART3_Handler.Init.BaudRate = bound;
    USART3_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    USART3_Handler.Init.StopBits = UART_STOPBITS_1;
    USART3_Handler.Init.Parity = UART_PARITY_NONE;
    USART3_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    USART3_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&USART3_Handler);
#if EN_USART3_RX
    HAL_UART_Receive_IT(&USART3_Handler, (uint8_t*)aRxBuffer3, RXBUFFERSIZE);
#endif
}
#endif

#ifdef EN_UART4
UART_HandleTypeDef UART4_Handler;
#if EN_UART4_RX
UART_HandleTypeDef UART4_Handler;
uint8_t UART4_RX_BUF[USART_REC_LEN];
uint16_t UART4_RX_STA = 0;
uint8_t aRxBuffer4[RXBUFFERSIZE];
/**
 * @brief 串口4中断服务函数
 */
void UART4_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&UART4_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&UART4_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&UART4_Handler, (uint8_t*)aRxBuffer4,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口4初始化
 * @param bound 波特率
 */
void UART4_Init(uint32_t bound) {
    UART4_Handler.Instance = UART4;
    UART4_Handler.Init.BaudRate = bound;
    UART4_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    UART4_Handler.Init.StopBits = UART_STOPBITS_1;
    UART4_Handler.Init.Parity = UART_PARITY_NONE;
    UART4_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART4_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART4_Handler);
#if EN_UART4_RX
    HAL_UART_Receive_IT(&UART4_Handler, (uint8_t*)aRxBuffer4, RXBUFFERSIZE);
#endif
}
#endif

#ifdef EN_UART5
UART_HandleTypeDef UART5_Handler;
#if EN_UART5_RX
uint8_t UART5_RX_BUF[USART_REC_LEN];
uint16_t UART5_RX_STA = 0;
uint8_t aRxBuffer5[RXBUFFERSIZE];
/**
 * @brief 串口5中断服务函数
 */
void UART5_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&UART5_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&UART5_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&UART5_Handler, (uint8_t*)aRxBuffer5,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口5初始化
 * @param bound 波特率
 */
void UART5_Init(uint32_t bound) {
    UART5_Handler.Instance = UART5;
    UART5_Handler.Init.BaudRate = bound;
    UART5_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    UART5_Handler.Init.StopBits = UART_STOPBITS_1;
    UART5_Handler.Init.Parity = UART_PARITY_NONE;
    UART5_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART5_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART5_Handler);
#if EN_UART5_RX
    HAL_UART_Receive_IT(&UART5_Handler, (uint8_t*)aRxBuffer5, RXBUFFERSIZE);
#endif
}
#endif

#ifdef EN_USART6
UART_HandleTypeDef USART6_Handler;
#if EN_USART6_RX
uint8_t USART6_RX_BUF[USART_REC_LEN];
uint16_t USART6_RX_STA = 0;
uint8_t aRxBuffer6[RXBUFFERSIZE];
/**
 * @brief 串口6中断服务函数
 */
void USART6_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&USART6_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&USART6_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&USART6_Handler, (uint8_t*)aRxBuffer6,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口6初始化
 * @param bound 波特率
 */
void USART6_Init(uint32_t bound) {
    USART6_Handler.Instance = USART6;
    USART6_Handler.Init.BaudRate = bound;
    USART6_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    USART6_Handler.Init.StopBits = UART_STOPBITS_1;
    USART6_Handler.Init.Parity = UART_PARITY_NONE;
    USART6_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    USART6_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&USART6_Handler);
#if EN_USART6_RX
    HAL_UART_Receive_IT(&USART6_Handler, (uint8_t*)aRxBuffer6, RXBUFFERSIZE);
#endif
}
#endif

#ifdef EN_UART7
UART_HandleTypeDef UART7_Handler;
#if EN_UART7_RX
uint8_t UART7_RX_BUF[USART_REC_LEN];
uint16_t UART7_RX_STA = 0;
uint8_t aRxBuffer7[RXBUFFERSIZE];
/**
 * @brief 串口7中断服务函数
 */
void UART7_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&UART7_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&UART7_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&UART7_Handler, (uint8_t*)aRxBuffer7,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口7初始化
 * @param bound 波特率
 */
void UART7_Init(uint32_t bound) {
    UART7_Handler.Instance = UART7;
    UART7_Handler.Init.BaudRate = bound;
    UART7_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    UART7_Handler.Init.StopBits = UART_STOPBITS_1;
    UART7_Handler.Init.Parity = UART_PARITY_NONE;
    UART7_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART7_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART7_Handler);
#if EN_UART7_RX
    HAL_UART_Receive_IT(&UART7_Handler, (uint8_t*)aRxBuffer7, RXBUFFERSIZE);
#endif
}
#endif

#ifdef EN_UART8
UART_HandleTypeDef UART8_Handler;
#if EN_UART8_RX
uint8_t UART8_RX_BUF[USART_REC_LEN];
uint16_t UART8_RX_STA = 0;
uint8_t aRxBuffer8[RXBUFFERSIZE];
/**
 * @brief 串口8中断服务函数
 */
void UART8_IRQHandler(void) {
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&UART8_Handler);

    timeout = 0;
    while (HAL_UART_GetState(&UART8_Handler) != HAL_UART_STATE_READY) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }

    timeout = 0;
    while (HAL_UART_Receive_IT(&UART8_Handler, (uint8_t*)aRxBuffer8,
                               RXBUFFERSIZE) != HAL_OK) {
        timeout++;
        if (timeout > maxDelay) {
            break;
        }
    }
}
#endif
/**
 * @brief 串口8初始化
 * @param bound 波特率
 */
void UART8_Init(uint32_t bound) {
    UART8_Handler.Instance = UART8;
    UART8_Handler.Init.BaudRate = bound;
    UART8_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    UART8_Handler.Init.StopBits = UART_STOPBITS_1;
    UART8_Handler.Init.Parity = UART_PARITY_NONE;
    UART8_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART8_Handler.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&UART8_Handler);
#if EN_UART8_RX
    HAL_UART_Receive_IT(&UART8_Handler, (uint8_t*)aRxBuffer8, RXBUFFERSIZE);
#endif
}
#endif

/* 此函数会被HAL_UART_Init调用 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    GPIO_InitTypeDef GPIO_Initure;
    if (huart->Instance == USART1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_9;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure); /* PA9 */
        GPIO_Initure.Pin = GPIO_PIN_10;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure); /* PA10 */
#if EN_USART1_RX
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn, 2, 2);
#endif
    } else if (huart->Instance == USART2) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART2_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_2;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure); /* PA2 */
        GPIO_Initure.Pin = GPIO_PIN_3;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure); /* PA3 */
#if EN_USART2_RX
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        HAL_NVIC_SetPriority(USART2_IRQn, 2, 2);
#endif
    } else if (huart->Instance == USART3) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_USART3_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_10;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF7_USART3;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure); /* PB10 */
        GPIO_Initure.Pin = GPIO_PIN_11;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure); /* PB11 */
#if EN_USART3_RX
        HAL_NVIC_EnableIRQ(USART3_IRQn);
        HAL_NVIC_SetPriority(USART3_IRQn, 2, 2);
#endif
    } else if (huart->Instance == UART4) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_UART4_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_10;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF8_UART4;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure); /* PC10 */
        GPIO_Initure.Pin = GPIO_PIN_11;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure); /* PC11 */
#if EN_UART4_RX
        HAL_NVIC_EnableIRQ(UART4_IRQn);
        HAL_NVIC_SetPriority(UART4_IRQn, 2, 2);
#endif
    } else if (huart->Instance == UART5) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_UART5_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_12;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure); /* PC12 */
        GPIO_Initure.Pin = GPIO_PIN_2;
        HAL_GPIO_Init(GPIOD, &GPIO_Initure); /* PD2 */
#if EN_UART5_RX
        HAL_NVIC_EnableIRQ(UART5_IRQn);
        HAL_NVIC_SetPriority(UART5_IRQn, 2, 2);
#endif
    } else if (huart->Instance == USART6) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_USART6_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_6;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF8_USART6;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure); /* PC6 */
        GPIO_Initure.Pin = GPIO_PIN_7;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure); /* PC7 */
#if EN_USART6_RX
        HAL_NVIC_EnableIRQ(USART6_IRQn);
        HAL_NVIC_SetPriority(USART6_IRQn, 2, 2);
#endif
    } else if (huart->Instance == UART7) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_UART7_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_8;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF8_UART7;
        HAL_GPIO_Init(GPIOE, &GPIO_Initure); /* PE8 */
        GPIO_Initure.Pin = GPIO_PIN_7;
        HAL_GPIO_Init(GPIOE, &GPIO_Initure); /* PE7 */
#if EN_UART7_RX
        HAL_NVIC_EnableIRQ(UART7_IRQn);
        HAL_NVIC_SetPriority(UART7_IRQn, 2, 2);
#endif
    } else if (huart->Instance == UART8) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_UART8_CLK_ENABLE();

        GPIO_Initure.Pin = GPIO_PIN_1;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FAST;
        GPIO_Initure.Alternate = GPIO_AF8_UART8;
        HAL_GPIO_Init(GPIOE, &GPIO_Initure); /* PE1 */
        GPIO_Initure.Pin = GPIO_PIN_0;
        HAL_GPIO_Init(GPIOE, &GPIO_Initure); /* PE0 */
#if EN_UART8_RX
        HAL_NVIC_EnableIRQ(UART8_IRQn);
        HAL_NVIC_SetPriority(UART8_IRQn, 2, 2);
#endif
    }
}

/* 串口中断回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    /* 如果要使用某个串口的接收中断,请在头文件定义 */
    if (huart->Instance == USART1) {
#if EN_USART1_RX
        /* 以下用于测试中断回调是否有问题,根据实际情况修改
         * 也可以将接收写在中断服务函数中
         */
        if ((USART1_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (USART1_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer1[0] != 0x0a) {
                    USART1_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    USART1_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer1[0] == 0x0d) {
                    USART1_RX_STA |= 0x4000;
                } else {
                    USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = aRxBuffer1[0];
                    USART1_RX_STA++;
                    if (USART1_RX_STA > (USART_REC_LEN - 1)) {
                        USART1_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == USART2) {
#if EN_USART2_RX
        if ((USART2_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (USART2_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer2[0] != 0x0a) {
                    USART2_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    USART2_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer2[0] == 0x0d) {
                    USART2_RX_STA |= 0x4000;
                } else {
                    USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = aRxBuffer2[0];
                    USART2_RX_STA++;
                    if (USART2_RX_STA > (USART_REC_LEN - 1)) {
                        USART2_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == USART3) {
#if EN_USART3_RX
        if ((USART3_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (USART3_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer3[0] != 0x0a) {
                    USART3_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    USART3_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer3[0] == 0x0d) {
                    USART3_RX_STA |= 0x4000;
                } else {
                    USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = aRxBuffer3[0];
                    USART3_RX_STA++;
                    if (USART3_RX_STA > (USART_REC_LEN - 1)) {
                        USART3_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == UART4) {
#if EN_UART4_RX
        if ((UART4_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (UART4_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer4[0] != 0x0a) {
                    UART4_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    UART4_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer4[0] == 0x0d) {
                    UART4_RX_STA |= 0x4000;
                } else {
                    UART4_RX_BUF[UART4_RX_STA & 0X3FFF] = aRxBuffer4[0];
                    UART4_RX_STA++;
                    if (UART4_RX_STA > (USART_REC_LEN - 1)) {
                        UART4_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == UART5) {
#if EN_UART5_RX
        if ((UART5_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (UART5_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer5[0] != 0x0a) {
                    UART5_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    UART5_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer5[0] == 0x0d) {
                    UART5_RX_STA |= 0x4000;
                } else {
                    UART5_RX_BUF[UART5_RX_STA & 0X3FFF] = aRxBuffer5[0];
                    UART5_RX_STA++;
                    if (UART5_RX_STA > (USART_REC_LEN - 1)) {
                        UART5_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == USART6) {
#if EN_USART6_RX
        if ((USART6_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (USART6_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer6[0] != 0x0a) {
                    USART6_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    USART6_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer6[0] == 0x0d) {
                    USART6_RX_STA |= 0x4000;
                } else {
                    USART6_RX_BUF[USART6_RX_STA & 0X3FFF] = aRxBuffer6[0];
                    USART6_RX_STA++;
                    if (USART6_RX_STA > (USART_REC_LEN - 1)) {
                        USART6_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == UART7) {
#if EN_UART7_RX
        if ((UART7_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (UART7_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer7[0] != 0x0a) {
                    UART7_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    UART7_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer7[0] == 0x0d) {
                    UART7_RX_STA |= 0x4000;
                } else {
                    UART7_RX_BUF[UART7_RX_STA & 0X3FFF] = aRxBuffer7[0];
                    UART7_RX_STA++;
                    if (UART7_RX_STA > (USART_REC_LEN - 1)) {
                        UART7_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    } else if (huart->Instance == UART8) {
#if EN_UART8_RX
        if ((UART8_RX_STA & 0x8000) == 0) {
            /* 接收未完成 */
            if (UART8_RX_STA & 0x4000) {
                /* 接收到了0x0d */
                if (aRxBuffer8[0] != 0x0a) {
                    UART8_RX_STA = 0; /* 接收错误,重新开始 */
                } else {
                    UART8_RX_STA |= 0x8000; /* 接收完成了 */
                }
            } else {
                /* 还没收到0X0D */
                if (aRxBuffer8[0] == 0x0d) {
                    UART8_RX_STA |= 0x4000;
                } else {
                    UART8_RX_BUF[UART8_RX_STA & 0X3FFF] = aRxBuffer8[0];
                    UART8_RX_STA++;
                    if (UART8_RX_STA > (USART_REC_LEN - 1)) {
                        UART8_RX_STA = 0; /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
#endif
    }
}

/**
 * @brief 指定串口输出
 * @param uart 串口句柄指针
 * @param __format 欲输出的内容,类似于printf格式
 */
void uart_print(UART_HandleTypeDef* uart, const char* __format, ...) {
    int len;
    va_list ap;
    va_start(ap, __format);

    /* 清空发送缓冲区 */
    memset(USART_Tx_Buf, 0x0, TX_BUF_LEN);

    /* 填充发送缓冲区 */
    vsnprintf((char*)USART_Tx_Buf, TX_BUF_LEN, (const char*)__format, ap);
    va_end(ap);
    len = strlen((const char*)USART_Tx_Buf);

    /* 往串口发送数据 */
    HAL_UART_Transmit(uart, (uint8_t*)&USART_Tx_Buf, len, 0xFFFF);
}

/* 如果启用了串口1,重定义printf */
#ifdef EN_USART1
#if (__ARMCC_VERSION >= 6010050)           /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t"); /* 声明不使用半主机模式 */
__asm(
    ".global __ARM_use_no_argv \n\t"); /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式
                                        */

#else /* __ARMCC_VERSION */
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */

/* 关闭多字节警告 */
#pragma diag_suppress 870
#pragma import(__use_no_semihosting)

struct __FILE {
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif /* __ARMCC_VERSION */

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式
 */
int _ttywrch(int ch) {
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x) {
    x = x;
}

char* _sys_command_string(char* cmd, int len) {
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE* f) {
    while ((USART1->SR & 0X40) == 0)
        ; /* 等待上一个字符发送完成 */

    USART1->DR = (uint8_t)ch; /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}
#endif /* EN_USART1 */
