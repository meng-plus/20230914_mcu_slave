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

efsm_node_t efsm_node_0_C = {
    .element = {.prev = NULL, .next = NULL},
    .init = init,
    .tick = tick,
    .exit = exit,
    .action = action};

efsm_node_config_x3_t s_config_03 = {
    .gpio_o = {O_C_PORT, O_C_PIN},
    .gpio_i0 = {I_0C_PORT, I_0C_PIN},
    .gpio_i1 = {I_1C_PORT, I_1C_PIN},
};
extern efsm_node_config_x1_t s_config_01;
extern efsm_node_config_x2_t s_config_02;
void init()
{
    s_config_03.step = 0;
    s_config_03.step_last = 0;
}
void tick()
{
    uint32_t tick_curr = HAL_GetTick();
    if (s_config_03.step_last != s_config_03.step)
    {
        s_config_03.step_last = s_config_03.step;
        s_config_03.tick_last = tick_curr;
    }
    if ((s_config_03.step > 1) &&
        (1000 < tick_curr - s_config_03.tick_last))
    { // 超时
        EFSM_EVENT_T event = EFSM_EVENT_WARNING;
        efsm_action(&efsm_task_0, &event);
    }

    switch (s_config_03.step)
    {
    case 0x00:
        s_config_03.step++;
        HAL_GPIO_WritePin(s_config_03.gpio_o.port, s_config_03.gpio_o.pin, GPIO_PIN_RESET);
        break;
    case 0x01:
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_03.gpio_i0.port, s_config_03.gpio_i0.pin))
        {
            s_config_01.step++;
            HAL_GPIO_WritePin(s_config_02.gpio_o1.port, s_config_02.gpio_o1.pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(s_config_02.gpio_o2.port, s_config_02.gpio_o2.pin, GPIO_PIN_SET);
            s_config_03.flag_io1 = 0x00;
            s_config_03.flag_io2 = 0x00;
        }
        break;
    case 0x02: // 检测到位
        switch (s_config_03.flag_io1)
        {
        case 0x00: // 检测低电平
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_02.gpio_i10.port, s_config_02.gpio_i10.pin))
            {
                s_config_03.flag_io1++;
            }
            break;
        case 0x01: // 检测恢复高电平
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_02.gpio_i10.port, s_config_02.gpio_i10.pin))
            {
                s_config_03.flag_io1++;
            }
            break;
        case 0x02:
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_02.gpio_i11.port, s_config_02.gpio_i11.pin))
            {
                s_config_03.flag_io1++;
            }
            break;
        default:
            break;
        }
        switch (s_config_03.flag_io2)
        {
        case 0x00: // 检测低电平
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_02.gpio_i20.port, s_config_02.gpio_i20.pin))
            {
                s_config_03.flag_io1++;
            }
            break;
        case 0x01: // 检测恢复高电平
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_02.gpio_i20.port, s_config_02.gpio_i20.pin))
            {
                s_config_03.flag_io1++;
            }
            break;
        case 0x02:
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_02.gpio_i21.port, s_config_02.gpio_i21.pin))
            {
                s_config_03.flag_io1++;
            }
            break;
        default:
            break;
        }
        if ((s_config_03.flag_io1 >= 3) && (s_config_03.flag_io2 >= 3))
        {
            s_config_01.step++;
        }
        break;
    case 0x03: // 确认其它I1口均为高电平
        if ((GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_01.gpio_i1.port, s_config_01.gpio_i1.pin)) &&
            (GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_02.gpio_i11.port, s_config_02.gpio_i11.pin)) &&
            (GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_02.gpio_i21.port, s_config_02.gpio_i21.pin)))
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
