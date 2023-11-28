/**
 * @file    pid.hpp
 * @author  Deadline--
 * @brief   pid类封装
 * @version 0.1
 * @date    2023-10-27
 */
#ifndef __PID_H
#define __PID_H

#include "math.h"
#include "sys.h"

enum { LLAST = 0, LAST = 1, NOW = 2, POSITION_PID, DELTA_PID };

#ifdef __cplusplus
/**
 * @brief PID类, 可以为速度环, 也可以为角度环
 *
 */
class PID_Class {
   private:
    float kp, ki, kd; /* pid三参数 */

    float set[3]; /* 目标值, 包含本次, 上次, 上上次 */
    float get[3]; /* 测量值, 包含本次, 上次, 上上次 */
    float err[3]; /* 误差值, 包含本次, 上次, 上上次 */

    float pout, iout, dout; /* pid输出 */

    uint32_t pid_mode; /* PID模式 */

    /* 位置模式 */
    float pos_out;     /* 本次输出 */
    float pos_lastout; /* 上次输出 */

    /* 增量模式 */
    float delta_u;       /* 本次增量值 */
    float delta_out;     /* 本次增量输出 = delta_lastout + delta_u */
    float delta_lastout; /* 上次增量输出 */

    uint32_t maxOutput;     /* 输出限幅 */
    uint32_t integralLimit; /* 积分限幅 */
    float deadBand;         /* 死区(绝对值) */
    float maxErr;           /* 最大误差 */
   public:
    PID_Class(uint16_t maxout_p,
              uint16_t intergralLim_p,
              float deadband_p,
              uint16_t maxerr_p,
              uint32_t pid_mode_p,

              float kp_p,
              float ki_p,
              float kd_p);
    void pid_reset(float kp_p, float ki_p, float kd_p);
    float pid_calc(float target_p, float measure_p);
    void pid_clear(void);

    ~PID_Class();
};

#endif /* __cplusplus */

#endif /* __PID_H */
