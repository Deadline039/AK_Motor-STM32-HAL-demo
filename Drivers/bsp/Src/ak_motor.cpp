/**
 * @file    ak_motor.cpp
 * @author  Deadline--
 * @brief   AK80驱动代码
 * @version 0.2
 * @date    2023-11-27
 * @see     https://github.com/Yangwen-li13/CubeMars-AK60-6/
 **********************************************************************
 @verbatim
 ======================================================================
                       ##### 库使用说明 #####
 ======================================================================
 (#) 实例化一个`AK_Motor_Class`对象, 指定型号与CAN ID
 (#) 在构造函数内会将电机对象插入到链表中, 以便于回调给对应的电机参数赋值.
     构造一个对象时, 会查找链表中是否存在相同CAN ID的对象,
     如果存在, 则将`id_conflict`属性设为`true`. 因此使用时要关注`id_conflict`.
     当CAN接收中断回调时, 会遍历链表, 查找与CAN ID一致的对象,
     找到后给对象属性赋值.
 (#) 链表使用Linux内核链表, 以保证可靠性

 @endverbatim
 */

#include "ak_motor.hpp"

struct list_head* head_ptr = NULL; /* 头指针, 空代表没有初始化 */
struct list_head* pos_ptr;         /* 遍历时的链表位置指针 */

/**
 * @brief 将电机类与链表关联, 此结构体仅限本文件使用
 *
 */
typedef struct {
    struct list_head ak_motor_list;    /*!< 链表指针 */
    AK_Motor_Class* ak_motor_instance; /*!< 对象实例 */
} AK_Motor_Linklist_t;

/**
 * @brief Construct a new ak motor class::ak motor class object
 *
 * @param ID CAN ID
 * @param model AK电机型号
 */
AK_Motor_Class::AK_Motor_Class(uint32_t ID, AK_motor_model_t model) {
    id_conflict = false;

    controller_id = ID;
    motor_model = model;
    /* 将对象加入到链表中 */
    if (head_ptr == NULL) {
        head_ptr = (list_head*)malloc(sizeof(list_head));
        /* 链表为空, 说明是第一次实例化对象, 初始化链表 */
        INIT_LIST_HEAD(head_ptr);
    } else {
        /* 不为空, 遍历查找CAN ID是否冲突 */
        list_for_each(pos_ptr, head_ptr) {
            if (((AK_Motor_Linklist_t*)pos_ptr)
                    ->ak_motor_instance->controller_id == ID) {
                id_conflict = true; /* CAN ID冲突 */
                return;
            }
        }
    }
    AK_Motor_Linklist_t* new_node;
    new_node = (AK_Motor_Linklist_t*)malloc(sizeof(AK_Motor_Linklist_t));
    new_node->ak_motor_instance = this;
    list_add(&new_node->ak_motor_list, head_ptr);
}
/**
 * @brief Destroy the ak motor class::ak motor class object
 *
 */
AK_Motor_Class::~AK_Motor_Class() {
    if (id_conflict == true) {
        /* ID冲突, 链表中不存在, 不做处理 */
        return;
    }
    /* 对象被销毁, 从队列里释放 */
    list_for_each(pos_ptr, head_ptr) {
        if (((AK_Motor_Linklist_t*)pos_ptr)->ak_motor_instance->controller_id ==
            controller_id) {
            list_del(&((AK_Motor_Linklist_t*)pos_ptr)->ak_motor_list);
            break;
        }
    }
}

/**
 * @brief 获得电机状态参数, 运控模式和伺服模式是一样的, 只是帧格式不同
 *
 * @param can_id CAN ID
 * @param can_msg CAN消息
 * @param AK_mode 模式
 * @note 此函数可以被重写
 */
__weak void ak_can_get_measure(uint8_t can_id,
                               uint8_t* can_msg,
                               AK_Ctrlmode_t AK_mode) {
    bool found = false;
    list_for_each(pos_ptr, head_ptr) {
        if (((AK_Motor_Linklist_t*)pos_ptr)->ak_motor_instance->controller_id ==
            can_id) {
            found = true;
            break;
        }
    }
    if (found == false) {
        /* ID不存在 */
        return;
    }
    float motor_pos, motor_spd, motor_cur_troq;
    int8_t temperature;
    uint8_t error;

    /* 电机对象指针 */
    AK_Motor_Class* ak_target =
        ((AK_Motor_Linklist_t*)pos_ptr)->ak_motor_instance;

    if (AK_mode == AK_Servo_Mode) {
        /* 整数整合, 转换成小数 */
        motor_pos = (float)((int16_t)(can_msg[0] << 8 | can_msg[1])) * 0.1f;
        motor_spd = (float)((int16_t)(can_msg[2] << 8 | can_msg[3])) * 10.0f;
        motor_cur_troq =
            (float)((int16_t)(can_msg[4] << 8 | can_msg[5])) * 0.01f;
        temperature = can_msg[6];
        error = can_msg[7];

        /* 对象属性赋值 */
        ak_target->motor_pos = motor_pos;
        ak_target->motor_spd = motor_spd;
        ak_target->motor_cur_troq = motor_cur_troq;
        ak_target->motor_temperature = temperature;
        ak_target->error_code = error;
        printf("%.2f,%.2f,%.2f,%d,%d\r\n", ak_target->motor_pos,
               ak_target->motor_spd, ak_target->motor_cur_troq,
               ak_target->motor_temperature, ak_target->error_code);
    } else if (AK_mode == AK_MIT_Mode) {
        /* 整数整合 */
        int16_t pos_int = (can_msg[1] << 8) | can_msg[2];
        int16_t spd_int = (can_msg[3] << 4) | (can_msg[4] >> 4);
        int16_t torq_int = ((can_msg[4] * 0xF) << 8) | can_msg[5];

        temperature = can_msg[6];
        error = can_msg[7];

        /* 转换成小数 */
        motor_pos = uint_to_float(pos_int, -AK_MIT_LIM_POS, AK_MIT_LIM_POS, 16);
        motor_spd = uint_to_float(
            spd_int,
            -AK_MIT_param_limit[ak_target->motor_model][AK_MIT_LIM_SPEED],
            AK_MIT_param_limit[ak_target->motor_model][AK_MIT_LIM_SPEED], 12);
        motor_cur_troq = uint_to_float(
            torq_int,
            -AK_MIT_param_limit[ak_target->motor_model][AK_MIT_LIM_TORQUE],
            AK_MIT_param_limit[ak_target->motor_model][AK_MIT_LIM_TORQUE], 12);
        /* 属性赋值 */
        ak_target->motor_pos = motor_pos;
        ak_target->motor_spd = motor_spd;
        ak_target->motor_cur_troq = motor_cur_troq;
        ak_target->motor_temperature = temperature;
        ak_target->error_code = error;
        printf("%.2f,%.2f,%.2f,%d,%d\r\n", ak_target->motor_pos,
               ak_target->motor_spd, ak_target->motor_cur_troq,
               ak_target->motor_temperature, ak_target->error_code);
    }
}

/**
 * @defgroup 伺服模式驱动
 * @{
 */

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
 * @param[in] min_value 最小值
 * @param[in] max_value 最大值
 */
static inline void param_limit(float* value, float min_value, float max_value) {
    if (*value > max_value) {
        *value = max_value;
    } else if (*value < min_value) {
        *value = min_value;
    }
}

/**
 * @brief 占空比模式设置电机转速
 *
 * @param duty 占空比, 范围`0 ~ 1.0`
 */
void AK_Motor_Class::comm_can_set_duty(float duty) {
    param_limit(duty, 0, MAX_PWM);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(duty * 100000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_PWM), buffer,
                           send_index);
}
/**
 * @brief 设置电机电流
 *
 * @param current 电流值(mA)
 * @note 由于电机`输出扭矩 = iq * KT`, 所以可以当作扭矩环使用
 */
void AK_Motor_Class::comm_can_set_current(float current) {
    param_limit(&current, -MAX_CURRENT, MAX_CURRENT);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_CURRENT), buffer,
                           send_index);
}
/**
 * @brief 设置电机刹车电流
 *
 * @param current 刹车电流
 */
void AK_Motor_Class::comm_can_set_cb(float current) {
    param_limit(&current, -MAX_CURRENT, MAX_CURRENT);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_CURRENT_BRAKE),
                           buffer, send_index);
}
/**
 * @brief 速度环模式设置速度
 *
 * @param rpm 速率, `erpm = rpm * 极对数`
 */
void AK_Motor_Class::comm_can_set_rpm(float rpm) {
    param_limit(&rpm, -MAX_VELOCITY, MAX_VELOCITY);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)rpm, &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_VELOCITY),
                           buffer, send_index);
}
/**
 * @brief 位置环模式设置位置
 *
 * @param pos 位置(角度, 范围`-36 000° ~ 36 000°`)
 * @note 默认速度12000erpm, 加速度40000erpm
 */
void AK_Motor_Class::comm_can_set_pos(float pos) {
    param_limit(pos, -MAX_POSITION, MAX_POSITION);
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(pos * 10000.0f), &send_index);
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_POSITION),
                           buffer, send_index);
}
/**
 * @brief 设置原点
 *
 * @param set_origin_mode 设置原点模式:
 *  @arg 0-设置临时原点(断电消除);
 *  @arg 1-代表设置永久零点(参数自动保存);
 *  @arg 2-代表恢复默认零点(参数自动保存)
 */
void AK_Motor_Class::comm_can_set_origin(uint8_t set_origin_mode) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    AKcmd_can_transmit_eid(canid_append_mode(controller_id, AK_ORIGIN), buffer,
                           send_index);
}
/**
 * @brief 速度位置环模式
 *
 * @param pos 位置
 *  @arg 传入范围`-36 000° ~ 36 000°`
 * @param spd 速度
 *  @arg 传入范围`-32 768 ~ -32 767`, 对应转速`-327 680 ~ -327 670 erpm`
 * @param RPA 加速度
 *  @arg 传入范围`0 ~ 32 767`, 对应加速度`0 ~ 327 670 erpm/s^2`
 */
void AK_Motor_Class::comm_can_set_pos_spd(float pos, float spd, float RPA) {
    param_limit(&pos, -MAX_POSITION, MAX_POSITION);
    param_limit(&RPA, 0.0f, MAX_ACCELERATION);
    param_limit(&spd, MIN_POSITION_VELOCITY, MAX_POSITION);

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

/**
 * @}
 */

/**
 * @defgroup 运控模式驱动
 * @{
 */

/**
 * @brief 运控模式进入电机控制
 *
 * @attention 必须先进入控制模式才可以控制电机!
 */
void AK_Motor_Class::mit_can_enter_motor(void) {
    uint8_t data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0XFC};
    AKcmd_can_transmit_mit(controller_id, data, 8);
}
/**
 * @brief 运控模式设置电机原点
 *
 */
void AK_Motor_Class::mit_can_set_origin(void) {
    uint8_t data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0XFE};
    AKcmd_can_transmit_mit(controller_id, data, 8);
}
/**
 * @brief 让电机进入控制
 *
 * @param pos 电机位置
 * @param spd 电机速度
 * @param kp 运动比例系数
 * @param kd 运动阻尼系数
 * @param torque 扭矩
 * @attention 必须先进入控制模式才可以控制电机!
 */
void AK_Motor_Class::mit_can_send_data(float pos,
                                       float spd,
                                       float kp,
                                       float kd,
                                       float torque) {
    /* 转换成整数 */
    int16_t pos_int = float_to_uint(pos, -AK_MIT_LIM_POS, AK_MIT_LIM_POS, 16);
    int16_t spd_int =
        float_to_uint(spd, -AK_MIT_param_limit[motor_model][AK_MIT_LIM_SPEED],
                      AK_MIT_param_limit[motor_model][AK_MIT_LIM_SPEED], 12);
    int16_t kp_int = float_to_uint(kp, 0, AK_MIT_MAX_KP, 12);
    int16_t kd_int = float_to_uint(kd, 0, AK_MIT_MAX_KD, 12);
    int16_t torque_int = float_to_uint(
        torque, -AK_MIT_param_limit[motor_model][AK_MIT_LIM_TORQUE],
        AK_MIT_param_limit[motor_model][AK_MIT_LIM_TORQUE], 12);

    /* 填充缓冲区 */
    uint8_t data[8];
    data[0] = pos_int >> 8;                           /* 位置高8位 */
    data[1] = pos_int & 0xFF;                         /* 位置低8位 */
    data[2] = spd_int >> 4;                           /* 速度高8位 */
    data[3] = ((spd_int & 0xF) << 4) | (kp_int >> 8); /* 速度低4位, kp高4位 */
    data[4] = kp_int & 0xFF;                          /* kp低8位 */
    data[5] = kd_int >> 4;                            /* kd高8位 */
    data[6] =
        ((kd_int & 0xF) << 4) | (torque_int >> 8); /* kp低4位, 扭矩高4位 */
    data[7] = torque_int & 0xFF;                   /* 扭矩低8位 */
    AKcmd_can_transmit_mit(controller_id, data, 8);
}
/**
 * @brief 让电机退出控制
 *
 */
void AK_Motor_Class::mit_can_exit_motor(void) {
    uint8_t data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0XFD};
    AKcmd_can_transmit_mit(controller_id, data, 8);
}

/**
 * @}
 */
