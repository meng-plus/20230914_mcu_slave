/**
 * @file efsm_node_0_A.c
 * @author ����plus (chengmeng_2@outlook.com)
 * @brief ����0 �ĵ�һ��
 * @version 0.1
 * @date 2023-09-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "efsm_task_0.h"

static void init();
static void tick();
static void exit();
static bool action(efsm_manage_ptr parent_ptr, void *event_ptr);

efsm_node_t efsm_node_warning = {
    .element = {.prev = NULL, .next = NULL},
    .init = init,
    .tick = tick,
    .exit = exit,
    .action = action};
void init()
{
    HAL_GPIO_WritePin(O_G_PORT, O_G_PIN, GPIO_PIN_RESET);
}
void tick()
{
}
void exit()
{
    HAL_GPIO_WritePin(O_G_PORT, O_G_PIN, GPIO_PIN_SET);
}
bool action(efsm_manage_ptr parent_ptr, void *event_ptr)
{
    return 0;
}
