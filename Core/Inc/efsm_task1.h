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
#ifndef __EFSM_TASK1_H_
#define __EFSM_TASK1_H_

#include "efsm.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        EFSM_EVENT_IDLE,
        EFSM_EVENT_TICK,
        EFSM_EVENT_START,
        EFSM_EVENT_STOP,
        EFSM_EVENT_PREV,
        EFSM_EVENT_NEXT,
    } task_EVENT_T;

#ifdef __cplusplus
}
#endif
#endif
