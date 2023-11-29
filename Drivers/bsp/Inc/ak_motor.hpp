/**
 * @file    ak_motor.hpp
 * @author  Deadline--
 * @brief   AK80驱动代码
 * @version 0.2
 * @date    2023-11-27
 */

#ifndef __AK80_H
#define __AK80_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "buffer_append.h"
#include "can.h"
#include "mylist.h"
#include "stdbool.h"
#include "stdlib.h"
#include "sys.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
 * @brief 控制模式定义
 *
 */
typedef enum {
    AK_Servo_Mode = 0, /*!< 伺服模式 */
    AK_MIT_Mode,       /*!< 运控模式 */
} AK_Ctrlmode_t;

/**
 * @defgroup 伺服模式驱动
 * @{
 */

/**
 * @brief 伺服模式阈值控制
 *
 */
#define MAX_PWM               1.0F      /*!< 最大占空比 */
#define MAX_CURRENT           60000.0F  /*!< 最大电流 */
#define MAX_VELOCITY          100000.0F /*!< 最大速率 */
#define MAX_POSITION          36000.0F  /*!< 最大位置 */
#define MAX_POSITION_VELOCITY 32767.0F  /*!< 旋转最大速率 */
#define MIN_POSITION_VELOCITY -32768.0F /*!< 旋转最小速率 */
#define MAX_ACCELERATION      32767.0F  /*!< 最大加速度 */
/**
 * @brief 电机模式, 作为CAN ID封装
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
/**
 * @}
 */

/**
 * @defgroup 运控模式驱动
 * @{
 */

/**
 * @brief 运控模式阈值控制
 */
#define AK_MIT_LIM_POS 12.5F  /*!< 最大位置 */
#define AK_MIT_MAX_KP  500.0F /*!< 最大KP */
#define AK_MIT_MAX_KD  5.0F   /*!< 最大KD */

/**
 * @brief 型号定义, 不同型号对于不同的参数
 *
 */
typedef enum {
    AK10_9 = 0,
    AK60_6,
    AK70_10,
    AK80_6,
    AK80_9,
    AK80_80_64,
    AK80_8
} AK_motor_model_t;
/**
 * @brief AK_MIT_param_limit数组二维下标
 * @note 不同型号电机只有速度和扭矩不同, 其他都是一样的
 */
enum {
    AK_MIT_LIM_SPEED = 0, /*!< 最大速度, 下标定义非实际值! */
    AK_MIT_LIM_TORQUE     /*!< 最大扭矩, 下标定义非实际值! */
};
/* 电机阈值, 第一维是型号, 第二维是参数(速度, 扭矩) */
static const float AK_MIT_param_limit[7][2] = {
    {50.0f, 65.0f}, {45.0f, 15.0f}, {50.0f, 25.0f}, {76.0f, 12.0f},
    {50.0f, 18.0f}, {8.0f, 144.0f}, {37.5f, 32.0f}};

/**
 * @}
 */

#ifdef __cplusplus
class AK_Motor_Class {
   public:
    uint32_t controller_id;         /*!< CAN ID */
    AK_motor_model_t motor_model;   /*!< 电机型号 */
    bool id_conflict;               /*!< CAN ID是否冲突 */
    float motor_pos;                /*!< 电机位置 */
    float motor_spd;                /*!< 电机速度 */
    float motor_cur_troq;           /*!< 电机电流, 运控模式为扭矩 */
    int8_t motor_temperature;       /*!< 电机温度 */
    uint8_t error_code;             /*!< 电机错误码 */

    AK_Motor_Class(uint32_t ID, AK_motor_model_t model);

    /* 伺服模式方法 */
    void comm_can_set_duty(float duty);
    void comm_can_set_current(float current);
    void comm_can_set_cb(float current);
    void comm_can_set_rpm(float rpm);
    void comm_can_set_pos(float pos);
    void comm_can_set_origin(uint8_t set_origin_mode);
    void comm_can_set_pos_spd(float pos, float spd, float RPA);

    /* 运控模式方法 */
    void mit_can_enter_motor(void);
    void mit_can_set_origin(void);
    void mit_can_send_data(float pos,
                           float spd,
                           float kp,
                           float kd,
                           float torque);
    void mit_can_exit_motor(void);

    ~AK_Motor_Class();
};

extern "C" {
void ak_can_get_measure(uint8_t can_id,
                        uint8_t* can_msg,
                        AK_Ctrlmode_t AK_mode);
}
#else /* __cplusplus */

void ak_can_get_measure(uint8_t can_id,
                        uint8_t* can_msg,
                        AK_Ctrlmode_t AK_mode);

#endif /* __cplusplus */

#endif /* __AK80_H */
