/**
 * @file efsm.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief �¼�����������״̬����Event Finite State Machine
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __EVENT_FINITE_STATE_MACHINE_H_
#define __EVENT_FINITE_STATE_MACHINE_H_

#include <stdint.h>
#include "list.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define EFSM_SAFE_RUN(ptr, fun) \
    if (ptr && (ptr->fun))      \
    {                           \
        ptr->fun();             \
    }
#define EFSM_SAFE_RUN_ARGV(ptr, fun, ...) \
    if (ptr && (ptr->fun))                \
    {                                     \
        ptr->fun(__VA_ARGS__);            \
    }
    typedef struct __EFSM_MANAGE *efsm_manage_ptr;
    typedef struct __FSM_NODE
    {
        struct list_element element;
        void (*init)();
        void (*tick)();
        void (*exit)();
        bool (*action)(efsm_manage_ptr parent_ptr, void *event_ptr);
    } efsm_node_t, *efsm_node_ptr;

    typedef enum __EFSM_EVENT
    {
        EFSM_EVENT_IDLE,
        EFSM_EVENT_TICK,
        EFSM_EVENT_START,
        EFSM_EVENT_STOP,
        EFSM_EVENT_PREV,
        EFSM_EVENT_NEXT,
        EFSM_EVENT_WARNING,
        EFSM_EVENT_ERROR,
        EFSM_EVENT_VALUE,
        EFSM_EVENT_USER = 0x80,
    } EFSM_EVENT_T;

    typedef struct __EFSM_MANAGE
    {
        struct list list;        /*!< ״̬������ */
        struct list_iterator it; /*!< ״̬����ǰ������ڵ� */
        void (*init)();
        void (*action)(void *event_ptr);
    } efsm_manage_t;

    void efsm_init(efsm_manage_ptr efsm_ptr);
    void efsm_action(efsm_manage_ptr efsm_ptr, void *event_ptr);

    void efsm_transfer(efsm_node_ptr curr, efsm_node_ptr next);
#ifdef __cplusplus
}
#endif

#endif //__STATE_MACHINE_H_