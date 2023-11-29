/**
 * @file    can.c
 * @author  Deadline--
 * @brief   CAN通信相关
 * @version 0.1
 * @date    2023-10-26
 */
#include "can.h"
CAN_HandleTypeDef CAN1_Handler;    /* CAN1句柄 */
CAN_TxHeaderTypeDef CAN1_TxHeader; /* 发送参数句柄 */
CAN_RxHeaderTypeDef CAN1_RxHeader; /* 接收参数句柄 */

/**
 * @brief CAN初始化
 * @param tsjw 重新同步跳跃时间单元.范围: 1 ~ 3;
 * @param tbs2 时间段2的时间单元.范围: 1 ~ 8;
 * @param tbs1 时间段1的时间单元.范围: 1 ~ 16;
 * @param brp 波特率分频器.范围: 1 ~ 1024;
 *   @note 以上4个参数, 在函数内部会减1, 所以, 任何一个参数都不能等于0
 *         CAN挂在APB1上面, 其输入时钟频率为 `Fpclk1 = PCLK1 = 45Mhz,
 *         tq = brp * tpclk1;
 *         波特率 = Fpclk1 / ((tbs1 + tbs2 + 1) * brp);`例如
 *         `45M / ((6 + 8 + 1) * 6) = 500Kbps`
 *
 * @param mode CAN_MODE_NORMAL,   普通模式;
               CAN_MODE_LOOPBACK, 回环模式
 * @retval 0,初始化成功; 其他, 初始化失败;
 */
uint8_t CAN1_Init(uint32_t tsjw,
                  uint32_t tbs2,
                  uint32_t tbs1,
                  uint16_t brp,
                  uint32_t mode) {
    CAN1_Handler.Instance = CAN1;
    CAN1_Handler.Init.Prescaler = brp; /* 分频系数(Fdiv)为brp+1 */
    CAN1_Handler.Init.Mode = mode;     /* 模式设置 */
    CAN1_Handler.Init.SyncJumpWidth =
        tsjw; /* 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位
                 CAN_SJW_1TQ~CAN_SJW_4TQ */
    CAN1_Handler.Init.TimeSeg1 = tbs1; /* tbs1范围CAN_BS1_1TQ~CAN_BS1_16TQ */
    CAN1_Handler.Init.TimeSeg2 = tbs2; /* tbs2范围CAN_BS2_1TQ~CAN_BS2_8TQ */
    CAN1_Handler.Init.TimeTriggeredMode = DISABLE; /* 非时间触发通信模式 */
    CAN1_Handler.Init.AutoBusOff = DISABLE; /* 软件自动离线管理 */
    CAN1_Handler.Init.AutoWakeUp =
        DISABLE; /* 睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位) */
    CAN1_Handler.Init.AutoRetransmission = ENABLE; /* 禁止报文自动传送 */
    CAN1_Handler.Init.ReceiveFifoLocked = DISABLE; /* 报文不锁定,新的覆盖旧的 */
    CAN1_Handler.Init.TransmitFifoPriority =
        DISABLE; /* 优先级由报文标识符决定 */
    if (HAL_CAN_Init(&CAN1_Handler) != HAL_OK) {
        return 1;
    }

#if CAN_RX0_INT_ENABLE
    /* 使用中断接收 */
    __HAL_CAN_ENABLE_IT(
        &CAN1_Handler, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0消息挂号中断允许 */
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);               /* 使能CAN中断 */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 0); /* 抢占优先级1，子优先级0 */
#endif

    CAN_FilterTypeDef CAN1_FilterConf;

    /* 配置CAN过滤器 */
    CAN1_FilterConf.FilterBank = 0; /* 过滤器0 */
    CAN1_FilterConf.FilterMode = CAN_FILTERMODE_IDMASK;
    CAN1_FilterConf.FilterScale = CAN_FILTERSCALE_32BIT;
    CAN1_FilterConf.FilterIdHigh = 0x0000; /* 32位ID */
    CAN1_FilterConf.FilterIdLow = 0x0000;
    CAN1_FilterConf.FilterMaskIdHigh = 0x0000; /* 32位MASK */
    CAN1_FilterConf.FilterMaskIdLow = 0x0000;
    CAN1_FilterConf.FilterFIFOAssignment =
        CAN_FILTER_FIFO0; /* 过滤器0关联到FIFO0 */
    CAN1_FilterConf.FilterActivation = CAN_FILTER_ENABLE; /* 激活滤波器0 */
    CAN1_FilterConf.SlaveStartFilterBank = 14;

    /* 过滤器配置 */
    if (HAL_CAN_ConfigFilter(&CAN1_Handler, &CAN1_FilterConf) != HAL_OK) {
        return 2;
    }

    /* 启动CAN外围设备 */
    if (HAL_CAN_Start(&CAN1_Handler) != HAL_OK) {
        return 3;
    }

    return 0;
}

#if CAN_RX0_INT_ENABLE
/**
 * @brief CAN1 RX0中断服务函数
 *
 */
void CAN1_RX0_IRQHandler(void) {
    HAL_CAN_IRQHandler(&CAN1_Handler);
}
/**
 * @brief CAN RX FIFO0挂起中断回调
 *
 * @param hcan
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    if (hcan->Instance == CAN1) {
        uint8_t msg[8];
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_RxHeader, msg);
        if (CAN1_RxHeader.IDE == CAN_ID_STD) {
            /* 标准帧数据, 运控模式 */
            ak_can_get_measure(msg[0], msg, AK_MIT_Mode);
        } else if (CAN1_RxHeader.IDE == CAN_ID_EXT) {
            /* 扩展帧数据, 伺服模式 */
            ak_can_get_measure((uint8_t)(CAN1_RxHeader.ExtId & 0xFF), msg,
                               AK_Servo_Mode);
        }
    }
}
#endif /* CAN_RX0_INT_ENABLE */

/**
 * @brief CAN底层驱动
 *
 * @param hcan CAN句柄
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan) {
    if (hcan->Instance == CAN1) {
        __HAL_RCC_GPIOA_CLK_ENABLE(); /* CAN引脚使能 */
        __HAL_RCC_CAN1_CLK_ENABLE();  /* 使能CAN1时钟 */

        GPIO_InitTypeDef GPIO_Initure;

        GPIO_Initure.Pin = GPIO_PIN_12;
        GPIO_Initure.Mode = GPIO_MODE_AF_PP;
        GPIO_Initure.Pull = GPIO_PULLUP;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_Initure.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure); /* CAN_TX脚 模式设置 */

        GPIO_Initure.Pin = GPIO_PIN_11;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure); /* CAN_RX脚 必须设置成输入模式 */
    }
}
/**
 * @brief 伺服模式给AK电机发送消息, 扩展帧
 *
 * @param id 发送ID
 * @param msg 数据
 * @param len 数据长度
 * @return uint8_t 0-成功; 1-添加发送邮箱失败; 2-发送超时
 */
uint8_t AKcmd_can_transmit_eid(uint32_t id, uint8_t* msg, uint8_t len) {
    if (len > 8) {
        /* 长度限制8 */
        len = 8;
    }
    uint16_t t = 0;
    uint32_t TxMailbox = CAN_TX_MAILBOX0;

    CAN1_TxHeader.IDE = CAN_ID_EXT; /* 使用扩展帧 */
    CAN1_TxHeader.StdId = 0;        /* 标准标识符 */
    CAN1_TxHeader.ExtId = id;       /* 扩展标识符(29位) */

    CAN1_TxHeader.RTR = CAN_RTR_DATA; /* 数据帧 */
    CAN1_TxHeader.DLC = len;

    if (HAL_CAN_AddTxMessage(&CAN1_Handler, &CAN1_TxHeader, msg, &TxMailbox) !=
        HAL_OK) {
        /* 发送消息 */
        return 1;
    }

    while (HAL_CAN_GetTxMailboxesFreeLevel(&CAN1_Handler) != 3) {
        /* 等待发送完成,所有邮箱为空 */
        t++;
        if (t > 0xFFF) {
            HAL_CAN_AbortTxRequest(&CAN1_Handler, TxMailbox);
            /* 超时，直接中止邮箱的发送请求 */
            return 1;
        }
    }

    return 0;
}

/**
 * @brief 运控模式给AK电机发送消息, 标准帧
 *
 * @param id 发送ID
 * @param msg 数据
 * @param len 数据长度
 * @return uint8_t 0-成功; 1-添加发送邮箱失败; 2-发送超时
 */
uint8_t AKcmd_can_transmit_mit(uint32_t id, uint8_t* msg, uint8_t len) {
    if (len > 8) {
        /* 长度限制8 */
        len = 8;
    }
    uint16_t t = 0;
    uint32_t TxMailbox = CAN_TX_MAILBOX0;

    CAN1_TxHeader.IDE = CAN_ID_STD; /* 使用标准帧 */
    CAN1_TxHeader.StdId = id;       /* 标准标识符 */
    CAN1_TxHeader.ExtId = id;       /* 扩展标识符(29位) */

    CAN1_TxHeader.RTR = CAN_RTR_DATA; /* 数据帧 */
    CAN1_TxHeader.DLC = len;

    if (HAL_CAN_AddTxMessage(&CAN1_Handler, &CAN1_TxHeader, msg, &TxMailbox) !=
        HAL_OK) {
        /* 发送消息 */
        return 1;
    }

    while (HAL_CAN_GetTxMailboxesFreeLevel(&CAN1_Handler) != 3) {
        /* 等待发送完成,所有邮箱为空 */
        t++;
        if (t > 0xFFF) {
            HAL_CAN_AbortTxRequest(&CAN1_Handler, TxMailbox);
            /* 超时，直接中止邮箱的发送请求 */
            return 1;
        }
    }

    return 0;
}
