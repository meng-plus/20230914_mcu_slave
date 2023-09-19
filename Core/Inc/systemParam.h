/**
 * @file systemParam.h
 * @author ����plus (chengmeng_2@outlook.com)
 * @brief ϵͳ���в���
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __SYSTEM_PARAM_H_
#define __SYSTEM_PARAM_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum __TASK_STATE
    {
        TASK_WAIT_START, /*!< �ȴ����� */
        TASK_STEP_1,
        TASK_STEP_2,
        TASK_STEP_3,
        TASK_STEP_4,
        TASK_STEP_COMP, /*!< ������� */
        TASK_STEP_ERR,  /*!< ���� */
    } task_state_e;

    typedef struct __RAM_DATA
    {
        uint16_t input_data; /*!< �����ź� */
        uint8_t out_step;    /*!< �������[0,3] 4��� */
    } systemParam_t;

    extern systemParam_t g_sysRam;

#ifdef __cplusplus
}
#endif
#endif //__SYSTEM_PARAM_H_
