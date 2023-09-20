/**
 * @file efsm_node_0_A.c
 * @author 蒙蒙plus (chengmeng_2@outlook.com)
 * @brief 方向0 的第一步
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

efsm_node_t efsm_node_0_A = {
    .element = {.prev = NULL, .next = NULL},
    .event_cb_table = NULL,
    .event_cb_num = 0,
    .init = init,
    .tick = tick,
    .exit = exit,
    .action = action};
efsm_node_config_x1_t s_config_01 = {
    .gpio_o = {O_A_PORT, O_A_PIN},
    .gpio_i0 = {I_0A_PORT, I_0A_PIN},
    .gpio_i1 = {I_1A_PORT, I_1A_PIN},
};
void init()
{
    s_config_01.step = 0;
    s_config_01.step_last = 0;
}
void tick()
{
    uint32_t tick_curr = HAL_GetTick();
    if (s_config_01.step_last != s_config_01.step)
    {
        s_config_01.step_last = s_config_01.step;
        s_config_01.tick_last = tick_curr;
    }
    if ((s_config_01.step > 1) &&
        (1000 < tick_curr - s_config_01.tick_last))
    { // 超时
        EFSM_EVENT_T event = EFSM_EVENT_WARNING;
        efsm_action(&efsm_task_0, &event);
    }
    switch (s_config_01.step)
    {
    case 0x00: /*!< Waiting for start pin high*/
        if (HAL_GPIO_ReadPin(I_START_PORT, I_START_PIN))
        {
            s_config_01.step++;
        }
        break;
    case 0x01: /*!< wait start */
        if (!HAL_GPIO_ReadPin(I_START_PORT, I_START_PIN))
        {
            s_config_01.step++;
            HAL_GPIO_WritePin(s_config_01.gpio_o.port, s_config_01.gpio_o.pin, GPIO_PIN_RESET);
        }
        break;
    case 0x02:
        if (HAL_GPIO_ReadPin(s_config_01.gpio_i0.port, s_config_01.gpio_i0.pin))
        {
            s_config_01.step++;
        }
        break;
    case 0x03:
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_01.gpio_i1.port, s_config_01.gpio_i1.pin))
        {
            s_config_01.step++;
            s_config_01.delay_st = tick_curr;
        }
        break;
    case 0x04:
        if (50 < tick_curr - s_config_01.delay_st)
        {
            EFSM_EVENT_T event = EFSM_EVENT_NEXT;
            efsm_action(&efsm_task_0, &event);
        }
        break;
    default:
        break;
    }
}
void exit()
{
}
bool action(efsm_manage_ptr parent_ptr, void *event_ptr)
{
    return 0;
}
