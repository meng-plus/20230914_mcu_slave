/**
 * @file motor.h
 * @author ����plus (chengmeng_2@outlook.com)
 * @brief ֱ�����������
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
        MOTOR_IDLE = 0x00, /*!< �������� */
        MOTOR_FORWARD,     /*!< ��ת */
        MOTOR_REVERSE,     /*!< ��ת */
        MOTOR_STOP,        /*!<��·ɲ�� */
        MOTOR_PER,         /*!< ����ģʽ */
    } MOTOR_CTRL_E;

    /**
     * @brief ֱ������豸��ʼ��
     *
     */
    void motor_init();

    void motor_ctrl(MOTOR_CTRL_E ctrl);
    MOTOR_CTRL_E motor_get_ctrl();
    /**
     * @brief ͨ���ٷֱȿ��Ƶ�� -100% ~100%
     *
     * @param per
     */
    void motor_set_speed(float per);
#ifdef __cplusplus
}
#endif
#endif //__MOTOR_H_
