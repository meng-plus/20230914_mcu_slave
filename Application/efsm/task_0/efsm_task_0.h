/**
 * @file efsm_task1.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 任务1
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __EFSM_TASK_0_H_
#define __EFSM_TASK_0_H_

#include "efsm.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum __EVENT_TASK1
    {
        EFSM_EVENT_S1 = EFSM_EVENT_USER,
        EFSM_EVENT_S2,
    } EVENT_TASK1_T;

    extern efsm_manage_t efsm_task_0;
#ifdef __cplusplus
}
#endif
#endif
