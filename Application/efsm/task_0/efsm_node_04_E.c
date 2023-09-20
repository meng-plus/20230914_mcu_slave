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

efsm_node_t efsm_node_0_E = {
    .element = {.prev = NULL, .next = NULL},
    .init = init,
    .tick = tick,
    .exit = exit,
    .action = action};

typedef struct EFSM_NODE_CONFIG_X4
{
    uint8_t step;        /*!< ���� */
    uint8_t step_last;   /*!< ��ʷ���裬���ڼ��㳬ʱ */
    uint32_t tick_last;  /*!< ms �ϴ��źŴ���ʱ�� ,��ʱ������ */
    uint32_t delay_st;   /*!< �ȴ�50ms */
    uint8_t flag_io : 4; /*!< �ϲ����״̬��¼ */
    gpio_t gpio_o;
    gpio_t gpio_i0;
    gpio_t gpio_i1;
} efsm_node_config_x4_t;

efsm_node_config_x4_t s_config_04 = {
    .gpio_o = {O_E_PORT, O_E_PIN},
    .gpio_i0 = {I_0E_PORT, I_0E_PIN},
    .gpio_i1 = {I_1E_PORT, I_1E_PIN},
};
extern efsm_node_config_x3_t s_config_03;
void init()
{
    s_config_04.step = 0;
    s_config_04.step_last = 0;
}
void tick()
{
    uint32_t tick_curr = HAL_GetTick();
    if (s_config_04.step_last != s_config_04.step)
    {
        s_config_04.step_last = s_config_04.step;
        s_config_04.tick_last = tick_curr;
    }
    if ((s_config_04.step > 1) &&
        (1000 < tick_curr - s_config_04.tick_last))
    { // ��ʱ
        EFSM_EVENT_T event = EFSM_EVENT_WARNING;
        efsm_action(&efsm_task_0, &event);
    }

    switch (s_config_04.step)
    {
    case 0x00:
        HAL_GPIO_WritePin(s_config_04.gpio_o.port, s_config_04.gpio_o.pin, GPIO_PIN_RESET);

        s_config_04.step++;
        break;
    case 0x01:
        if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_04.gpio_i0.port, s_config_04.gpio_i0.pin))
        {
            HAL_GPIO_WritePin(O_A_PORT, O_A_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(O_B_PORT, O_B_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(O_C_PORT, O_C_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(O_D_PORT, O_D_PIN, GPIO_PIN_SET);
            s_config_04.step++;
            s_config_04.flag_io = 0;
        }
        break;
    case 0x02: // ��������IO������
        switch (s_config_04.flag_io)
        {
        case 0x00: // ���͵�ƽ
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_03.gpio_i0.port, s_config_03.gpio_i0.pin))
            {
                s_config_04.flag_io++;
            }
            break;
        case 0x01: // ���ָ��ߵ�ƽ
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(s_config_03.gpio_i0.port, s_config_03.gpio_i0.pin))
            {
                s_config_04.flag_io++;
            }
            break;
        case 0x02:
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(s_config_04.gpio_i0.port, s_config_04.gpio_i0.pin))
            {
                HAL_GPIO_WritePin(s_config_04.gpio_o.port, s_config_04.gpio_o.pin, GPIO_PIN_SET);

                s_config_04.flag_io++;
            }
            break;
        default:
            break;
        }
        if (s_config_04.flag_io > 0x02)
        {
            HAL_GPIO_WritePin(O_F_PORT, O_F_PIN, GPIO_PIN_RESET);

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
