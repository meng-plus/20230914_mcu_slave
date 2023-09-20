/**
 * @file efsm_task1.c
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 状态机任务
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "efsm_task_0.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern efsm_node_t efsm_node_idle;
extern efsm_node_t efsm_node_warning;
extern efsm_node_t efsm_node_0_A;
extern efsm_node_t efsm_node_0_BD;
extern efsm_node_t efsm_node_0_C;
extern efsm_node_t efsm_node_0_E;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void init();
static void action(void *event_ptr);

efsm_manage_t efsm_task_0 =
    {
        .init = init,
        .action = action,
};
#define efsm efsm_task_0
#define efsm_this (&efsm)
void init()
{
    // 初始化状态机任务链表
    list_init(&(efsm.list));
    list_append(&(efsm.list), &(efsm_node_idle.element));
    list_append(&(efsm.list), &(efsm_node_0_A.element));
    list_append(&(efsm.list), &(efsm_node_0_BD.element));
    list_append(&(efsm.list), &(efsm_node_0_C.element));
    list_append(&(efsm.list), &(efsm_node_0_E.element));
    list_append(&(efsm.list), &(efsm_node_warning.element));
    list_iterator_init(&efsm.it, &efsm.list);
    efsm.it.current = &(efsm_node_idle.element);
}
void action(void *event_ptr)
{
    struct list_iterator it_curr = efsm.it;
    struct list_element* element;
    if (it_curr.current&&
        ((efsm_node_ptr)(it_curr.current))->action(efsm_this, event_ptr))
    { // 节点处理了此消息 则此结束
        return;
    }

    switch (*(EFSM_EVENT_T *)event_ptr)
    {
    case EFSM_EVENT_IDLE:
    case EFSM_EVENT_STOP:
        efsm.it.current = &(efsm_node_idle.element);
        efsm_transfer((efsm_node_ptr)it_curr.current, (efsm_node_ptr)efsm.it.current);
        break;
    case EFSM_EVENT_TICK:
        EFSM_SAFE_RUN(((efsm_node_ptr)it_curr.current), tick);
        break;
    case EFSM_EVENT_START:
        efsm.it.current = &(efsm_node_0_A.element);
        efsm_transfer(((efsm_node_ptr)it_curr.current), (efsm_node_ptr)efsm.it.current);
        break;
    case EFSM_EVENT_PREV:
        list_iterator_previous(&efsm.it, &element);
        efsm_transfer(((efsm_node_ptr)it_curr.current), (efsm_node_ptr)efsm.it.current);
        break;
    case EFSM_EVENT_NEXT:
        list_iterator_next(&efsm.it, &element);
        efsm_transfer(((efsm_node_ptr)it_curr.current), (efsm_node_ptr)efsm.it.current);
        break;
    case EFSM_EVENT_WARNING:
    case EFSM_EVENT_ERROR:
        efsm.it.current = &efsm_node_warning.element;
        efsm_transfer(((efsm_node_ptr)it_curr.current), (efsm_node_ptr)efsm.it.current);
        break;
    case EFSM_EVENT_VALUE:
        break;
    default:
        break;
    }
}
