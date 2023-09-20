/**
 * @file task_def.h
 * @author ����plus (chengmeng_2@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __TASK_DEF_H_
#define __TASK_DEF_H_

#include "efsm.h"
#include "product_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct EFSM_NODE_CONFIG_X1
    {
        uint8_t step;       /*!< ���� */
        uint8_t step_last;  /*!< ��ʷ���裬���ڼ��㳬ʱ */
        uint32_t tick_last; /*!< ms �ϴ��źŴ���ʱ�� ,��ʱ������ */
        uint32_t delay_st;  /*!< �ȴ�50ms */
        gpio_t gpio_o;
        gpio_t gpio_i0;
        gpio_t gpio_i1;
    } efsm_node_config_x1_t;
    typedef struct EFSM_NODE_CONFIG_X2
    {
        uint8_t step;       /*!< ���� */
        uint8_t step_last;  /*!< ��ʷ���裬���ڼ��㳬ʱ */
        uint32_t tick_last; /*!< ms �ϴ��źŴ���ʱ�� ,��ʱ������ */
        uint32_t delay_st;  /*!< �ȴ�50ms */
        gpio_t gpio_o1;
        gpio_t gpio_o2;

        gpio_t gpio_i10;
        gpio_t gpio_i11;
        gpio_t gpio_i20;
        gpio_t gpio_i21;
    } efsm_node_config_x2_t;
    typedef struct EFSM_NODE_CONFIG_X3
    {
        uint8_t step;         /*!< ���� */
        uint8_t step_last;    /*!< ��ʷ���裬���ڼ��㳬ʱ */
        uint32_t tick_last;   /*!< ms �ϴ��źŴ���ʱ�� ,��ʱ������ */
        uint32_t delay_st;    /*!< �ȴ�50ms */
        uint8_t flag_io1 : 4; /*!< �ϲ����״̬��¼ */
        uint8_t flag_io2 : 4; /*!< �ϲ����״̬��¼ */
        gpio_t gpio_o;
        gpio_t gpio_i0;
        gpio_t gpio_i1;
    } efsm_node_config_x3_t;
#ifdef __cplusplus
}
#endif
#endif //__TASK_DEF_H_
