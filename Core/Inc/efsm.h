/**
 * @file efsm.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 事件驱动型有限状态机：Event Finite State Machine
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __EVENT_FINITE_STATE_MACHINE_H_
#define __EVENT_FINITE_STATE_MACHINE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct __FSM_NODE
    {

        void (*init)();
        void (*tick)();
        void (*exit)();
        void (*action)(void *event_ptr);
    } stateBase_t;
    typedef enum _FSMC_EVENT
    {

    } FSMC_EVENT_T;
    typedef struct __STATE_MANAGE
    {
        stateBase_t *state_cur;
        stateBase_t *state_next;
        void (*init)();
        void (*tick)();
        void (*exit)();
        void (*action)(void *event_ptr);
    } fsmc_manage_t, *fsmc_manage_ptr;

    void fsmc_init(fsmc_manage_ptr fsmc_ptr);
    void fsmc_action(fsmc_manage_ptr fsmc_ptr, void *event_ptr);
#ifdef __cplusplus
}
#endif

#endif //__STATE_MACHINE_H_
