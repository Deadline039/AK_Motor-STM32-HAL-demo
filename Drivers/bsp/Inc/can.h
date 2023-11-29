/**
 * @file    can.h
 * @author  Deadline--
 * @brief   CAN通信相关
 * @version 0.1
 * @date    2023-10-26
 */
#ifndef __CAN_H
#define __CAN_H

#include "ak_motor.hpp"
#include "sys.h"
#include "usart.h"

/* 启用CAN接收RX0中断, 0禁用; 1启用 */
#define CAN_RX0_INT_ENABLE 1

uint8_t CAN1_Init(uint32_t tsjw,
                  uint32_t tbs2,
                  uint32_t tbs1,
                  uint16_t brp,
                  uint32_t mode);
uint8_t AKcmd_can_transmit_eid(uint32_t id, uint8_t* msg, uint8_t len);
uint8_t AKcmd_can_transmit_mit(uint32_t id, uint8_t* msg, uint8_t len);

#endif  // !__CAN_H
