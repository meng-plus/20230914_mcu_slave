/**
 * @file motor.h
 * @author 蒙蒙plus (chengmeng_2@outlook.com)
 * @brief 直流电机控制器
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MOTOR_H_
#define __MOTOR_H_
#ifdef __cplusplus

#include <stdint.h>
extern "C"
{
#endif

    typedef enum __MOTOR_CTRL
    {
        MOTOR_IDLE = 0x00, /*!< 自由悬空 */
        MOTOR_FORWARD,     /*!< 正转 */
        MOTOR_REVERSE,     /*!< 反转 */
        MOTOR_STOP,        /*!<短路刹车 */
    } MOTOR_CTRL_E;

    /**
     * @brief 直流电机设备初始化
     *
     */
    void motor_init();

    void motor_ctrl(MOTOR_CTRL_E ctrl);
    MOTOR_CTRL_E motor_get_ctrl();
#ifdef __cplusplus
}
#endif
#endif //__MOTOR_H_
