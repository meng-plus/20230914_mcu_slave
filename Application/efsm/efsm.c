/**
 * @file efsm.c
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 事件驱动型有限状态机：Event Finite State Machine
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "efsm.h"

void efsm_init(efsm_manage_ptr efsm_ptr)
{
    EFSM_SAFE_RUN(efsm_ptr, init);
}

void efsm_action(efsm_manage_ptr efsm_ptr, void *event_ptr)
{
    EFSM_SAFE_RUN_ARGV(efsm_ptr, action,  event_ptr);
}
void efsm_transfer(efsm_node_ptr curr, efsm_node_ptr next)
{
    if (next && curr != next)
    {
        EFSM_SAFE_RUN(curr, exit);
        EFSM_SAFE_RUN(next, init);
    }
}
