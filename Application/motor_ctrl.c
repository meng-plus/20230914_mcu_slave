/**
 * @file motor_ctrl.c
 * @author 蒙蒙plus (chengmeng_2@outlook.com)
 * @brief 电机控制模块
 * @version 0.1
 * @date 2023-09-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"

void motor_ctrl_task()
{
    switch (g_sysRam.motor_ctrl)
    {
    case 0X00://待机状态
        /* code */
        break;

    default:
        break;
    }
}
