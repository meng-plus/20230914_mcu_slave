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

efsm_node_t efsm_node_0_BD = {
    .element = {.prev = NULL, .next = NULL},
    .init = init,
    .tick = tick,
    .exit = exit,
    .action = action};

efsm_node_config_x2_t s_config_02 = {
    .gpio_o1 = {O_B_PORT, O_B_PIN},
    .gpio_o2 = {O_D_PORT, O_D_PIN},
    .gpio_i10 = {I_0B_PORT, I_0B_PIN},
    .gpio_i11 = {I_1B_PORT, I_1B_PIN},
    .gpio_i20 = {I_0D_PORT, I_0D_PIN},
    .gpio_i21 = {I_1D_PORT, I_1D_PIN},
};
// ��һ��������
extern efsm_node_config_x1_t s_config_01;
void init()
{
    s_config_02.step = 0;
    s_config_02.step_last = 0;
}
void tick()
{
    uint32_t tick_curr = HAL_GetTick();
    if (s_config_02.step_last != s_config_02.step)
    {
        s_config_02.step_last = s_config_02.step;
        s_config_02.tick_last = tick_curr;
    }
    if ((s_config_02.step > 1) &&
        (1000 < tick_curr - s_config_02.tick_last))
    { // ��ʱ
        EFSM_EVENT_T event = EFSM_EVENT_WARNING;
        efsm_action(&efsm_task_0, &event);
    }

    switch (s_config_02.step)
    {
    case 0x00: // �������������
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_01.gpio_i1.port, s_config_01.gpio_i1.pin))
        {
            s_config_02.step++;
            HAL_GPIO_WritePin(s_config_02.gpio_o1.port, s_config_02.gpio_o1.pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(s_config_02.gpio_o2.port, s_config_02.gpio_o2.pin, GPIO_PIN_RESET);
        }
        break;
    case 0x01: // �ر��ϲ������
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_02.gpio_i10.port, s_config_02.gpio_i10.pin) ||
            GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_02.gpio_i20.port, s_config_02.gpio_i20.pin))
        {
            s_config_02.step++;
            HAL_GPIO_WritePin(s_config_01.gpio_o.port, s_config_01.gpio_o.pin, GPIO_PIN_SET);
        }
        break;
    case 0x02: // ����ϲ���ִ�е�λ
        if ((GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_01.gpio_i0.port, s_config_01.gpio_i0.pin)) &&
            (GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_01.gpio_i1.port, s_config_01.gpio_i1.pin)))
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
