/**
 * @file    pid.cpp
 * @author  Deadline--
 * @brief   pid类实现
 * @version 0.1
 * @date    2023-10-27
 * @note    这个文件包含了pid类实现的代码, 将pid封装抽象成PID_Class类. 此类
 *          可以实例化为任意的PID, 无论是速度环还是角度环.
 *          创建PID对象时只需将参数传入, 构造函数自动设置参数, 不用像以前那样
 *          搞一堆Init函数.
 *          当然也可以用一个Init函数传指针实现, 但频繁的指针调用写代码很麻烦.
 *
 *          计算PID只需要调用pid_calc方法, 传入参数, 就可以返回PID的计算结果,
 *          不用传入指针, 不用关心内部如何计算, 只用调用对象方法就可以.
 *          为了防止乱改PID内部参数, 所有成员变量都为Private. 外部无法访问修改.
 *          而结构体设置私有变量比较麻烦, 所有成员变量都是公开的, 所有函数都可以
 *          修改. 万一那个地方改了内部参数, 输出结果不对, 很难排查.
 */

#include "pid.hpp"

/**
 * @brief 死区限制
 *
 * @param a 传入的值
 * @param abs_max 限制值
 */
static inline void abs_limit(float* a, float abs_max) {
    if (*a > abs_max) {
        *a = abs_max;
    }
    if (*a < -abs_max) {
        *a = -abs_max;
    }
}

/**
 * @brief Construct a new pid class::pid class object
 *
 * @param maxout_p 输出限幅
 * @param intergralLim_p 积分限幅
 * @param deadband_p 死区
 * @param maxerr_p 最大误差
 * @param pid_mode_p PID模式
 *  @arg POSITION_PID, 位置式PID
 *  @arg DELTA_PID, 增量式PID
 * @param kp_p P参数
 * @param ki_p I参数
 * @param kd_p D参数
 */
PID_Class::PID_Class(uint16_t maxout_p,
                     uint16_t intergralLim_p,
                     float deadband_p,
                     uint16_t maxerr_p,
                     uint32_t pid_mode_p,

                     float kp_p,
                     float ki_p,
                     float kd_p) {
    maxOutput = maxout_p;
    integralLimit = intergralLim_p;
    deadBand = deadband_p;
    maxErr = maxerr_p;
    pid_mode = pid_mode_p;

    kp = kp_p;
    ki = ki_p;
    kd = kd_p;
    pos_out = 0;
    delta_out = 0;
}
/**
 * @brief Destroy the pid class::pid class object
 *
 */
PID_Class::~PID_Class() {
    /* 对象销毁后调用 */
}
/**
 * @brief PID参数调整
 *
 * @param kp_p P参数
 * @param ki_p I参数
 * @param kd_p D参数
 */
void PID_Class::pid_reset(float kp_p, float ki_p, float kd_p) {
    kp = kp_p;
    ki = ki_p;
    kd = kd_p;
}
/**
 * @brief PID计算
 *
 * @param target_p 目标值
 * @param measure_p 电机测量值
 * @return float PID计算的结果
 */
float PID_Class::pid_calc(float target_p, float measure_p) {
    get[NOW] = measure_p;
    set[NOW] = target_p;
    err[NOW] = target_p - measure_p;

    if (maxErr != 0 && abs(err[NOW]) > maxErr) {
        return 0;
    }
    if (deadBand != 0 && abs(err[NOW]) < deadBand) {
        return 0;
    }
    if (pid_mode == POSITION_PID) {
        /* 位置式PID */
        pout = kp * err[NOW];
        iout += ki * err[NOW];
        dout = kd * (err[NOW] - err[LAST]);
        abs_limit(&iout, integralLimit);
        pos_out = pout + iout + dout;
        abs_limit(&pos_out, maxOutput);
        pos_lastout = pos_out;
    } else if (pid_mode == DELTA_PID) {
        /* 增量式PID */
        pout = kp * (err[NOW] - err[LAST]);
        iout = ki * err[NOW];
        dout = kd * (err[NOW] - 2 * err[LAST] + err[LLAST]);
        abs_limit(&iout, integralLimit);
        delta_u = pout + iout + dout;
        delta_out = delta_lastout + delta_u;
        abs_limit(&delta_out, maxOutput);
        delta_lastout = delta_out;
    }
    /* 状态转移 */
    err[LLAST] = err[LAST];
    err[LAST] = err[NOW];

    get[LLAST] = get[LAST];
    get[LAST] = get[NOW];

    set[LLAST] = set[LAST];
    set[LAST] = set[NOW];
    return pid_mode == POSITION_PID ? pos_out : delta_out;
}
/**
 * @brief 清空PID计算的数据, 不清空参数
 *
 */
void PID_Class::pid_clear(void) {
    set[LLAST] = set[LAST] = set[NOW] = 0;
    get[LLAST] = get[LAST] = get[NOW] = 0;
    err[LLAST] = err[LAST] = err[NOW] = 0;

    pout = iout = dout = 0;
    if (pid_mode == POSITION_PID) {
        pos_out = pos_lastout = 0;
    } else {
        delta_u = delta_out = delta_lastout = 0;
    }
}
