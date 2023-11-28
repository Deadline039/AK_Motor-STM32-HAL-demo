/**
 * @file    ak80.h
 * @author  Deadline--
 * @brief
 * @version 0.1
 * @date    2023-11-27
 */

#ifndef __AK80_H
#define __AK80_H

#include "buffer_append.h"
#include "can.h"
#include "sys.h"

/**
 * @brief 电机阈值控制
 *
 */
#define MAX_PWM 100000.0F               /* 最大占空比 */
#define MAX_CURRENT 60000.0F            /* 最大电流 */
#define MAX_VELOCITY 100000.0F          /* 最大速率 */
#define MAX_POSITION 360000000.0F       /* 最大位置 */
#define MAX_POSITION_VELOCITY 32767.0F  /* 旋转最大速率 */
#define MIN_POSITION_VELOCITY -32768.0F /* 旋转最小速率 */
#define MAX_ACCELERATION 400000.0F      /* 最大加速度 */

/**
 * @brief 电机模式
 *
 */
typedef enum {
    AK_PWM = 0,
    AK_CURRENT,
    AK_CURRENT_BRAKE,
    AK_VELOCITY,
    AK_POSITION,
    AK_ORIGIN,
    AK_POSITION_VELOCITY,
} AKMode_t;

void comm_can_set_duty(uint8_t controller_id, float duty);
void comm_can_set_current(uint8_t controller_id, float current);
void comm_can_set_cb(uint8_t controller_id, float current);
void comm_can_set_rpm(uint8_t controller_id, float rpm);
void comm_can_set_pos(uint8_t controller_id, float pos);
void comm_can_set_origin(uint8_t controller_id, uint8_t set_origin_mode);
void comm_can_set_pos_spd(uint8_t controller_id,
                          float pos,
                          int16_t spd,
                          int16_t RPA);

#endif  // !__AK80_H

#ifnd
