/**
 * @file    ak80.c
 * @author  Deadline--
 * @brief   AK80驱动代码
 * @version 0.1
 * @date    2023-11-27
 * @see     https://github.com/Yangwen-li13/CubeMars-AK60-6/
 */

#include "ak80.h"

/**
 * @brief 模式和ID整合
 *
 * @param id CAN ID
 * @param Mode_set 电机模式
 * @return uint32_t
 */
static inline uint32_t canid_append_mode(uint8_t id, AKMode_t Mode_set) {
    uint32_t mode;
    mode = Mode_set;
    return (uint32_t)(id | mode << 8);
}
/**
 * @brief 输出参数限制
 *
 * @param[out] value 传入值和结果
 * @param[in] max_value 最大值
 */
static inline void param_limit(float* value, float max_value) {
    if (*value > max_value) {
        *value = max_value;
    } else if (*value < -max_value) {
        *value = -max_value;
    }
}

/**
 * @brief 占空比模式设置电机转速
 *
 * @param controller_id CAN ID
 * @param duty 占空比
 */
void comm_can_set_duty(uint8_t controller_id, float duty) {
    param_limit(&duty, MAX_PWM);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(duty * 100000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_PWM), buffer,
                           send_index);
}
/**
 * @brief 设置电机电流
 *
 * @param controller_id CAN ID
 * @param current 电流值(mA)
 * @note 由于电机`输出扭矩 = iq * KT`, 所以可以当作扭矩环使用
 */
void comm_can_set_current(uint8_t controller_id, float current) {
    param_limit(&current, MAX_CURRENT);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_CURRENT), buffer,
                           send_index);
}
/**
 * @brief 设置电机刹车电流
 *
 * @param controller_id CAN ID
 * @param current 刹车电流
 */
void comm_can_set_cb(uint8_t controller_id, float current) {
    param_limit(&current, MAX_CURRENT);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_CURRENT_BRAKE),
                           buffer, send_index);
}
/**
 * @brief 速度环模式设置速度
 *
 * @param controller_id CAN ID
 * @param rpm 速率, `erpm = rpm * 极对数`, AK80-8 KV60的极对数为21
 */
void comm_can_set_rpm(uint8_t controller_id, float rpm) {
    param_limit(&rpm, MAX_VELOCITY);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)rpm, &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_VELOCITY),
                           buffer, send_index);
}
/**
 * @brief 位置环模式设置位置
 *
 * @param controller_id CAN ID
 * @param pos 位置(角度, 范围`-36 000° ~ 36 000°`)
 * @note 默认速度12000erpm, 加速度40000erpm
 */
void comm_can_set_pos(uint8_t controller_id, float pos) {
    /* 转到最大位置, 从0开始 */
    if (pos > MAX_POSITION) {
        pos = MAX_POSITION;
    }
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(pos * 10000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_POSITION),
                           buffer, send_index);
}
/**
 * @brief 设置原点
 *
 * @param controller_id CAN ID
 * @param set_origin_mode 设置原点模式:
 *  @arg 0-设置临时原点(断电消除);
 *  @arg 1-代表设置永久零点(参数自动保存);
 *  @arg 2-代表恢复默认零点(参数自动保存)
 */
void comm_can_set_origin(uint8_t controller_id, uint8_t set_origin_mode) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_ORIGIN), buffer,
                           send_index);
}
/**
 * @brief 速度位置环模式
 *
 * @param controller_id CAN ID
 * @param pos 位置
 *  @arg 传入范围`-36 000° ~ 36 000°`
 * @param spd 速度
 *  @arg 传入范围`-32 768 ~ -32 767`, 对应转速`-327 680 ~ -327 670 erpm`
 * @param RPA 加速度
 *  @arg 传入范围`0 ~ 32 767`, 对应加速度`0 ~ -327 670 erpm/s^2`
 */
void comm_can_set_pos_spd(uint8_t controller_id,
                          float pos,
                          int16_t spd,
                          int16_t RPA) {
    param_limit(&pos, MAX_POSITION);
    if (RPA > 32767) {
        RPA = 32767;
    }

    int32_t send_index = 0;
    int32_t send_index1 = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(pos * 10000.0f), &send_index);
    buffer_append_int16(buffer, spd, &send_index1);
    buffer_append_int16(buffer, RPA, &send_index1);
    AKcmd_can_transmit_eid(
        canid_append_mode(controller_id, AK_POSITION_VELOCITY), buffer,
        send_index);
}
