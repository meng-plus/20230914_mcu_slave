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
#include "efsm_task1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern efsm_node_t efsm_node_0_A;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void
init();
static void action(void *event_ptr);

efsm_manage_t efsm_task =
    {
        .init = init,
        .action = action,
};
#define efsm_this (&efsm_task)
void init()
{
    // 初始化状态机任务链表
    list_init(&efsm_task.node_list);
    list_prepend(&efsm_task.node_list, &efsm_node_0_A);
}
void action(void *event_ptr)
{
    struct list_iterator it_curr = efsm_this->it;
    if (it_curr.current &&
        (efsm_node_ptr)(it_curr.current)->action(efsm_this, event_ptr))
    { // 节点处理了此消息 则此结束
        return;
    }

    switch (event_ptr)
    {
    case EFSM_EVENT_IDLE:
        list_iterator_init(&efsm_this->it, efsm_this->list);
        efsm_transfer(it_curr.current, &efsm_this->it.current);
        break;
    case EFSM_EVENT_TICK:
        EFSM_SAFE_RUN((efsm_node_ptr)efsm_this->it.current, tick);
        break;
    case EFSM_EVENT_START:
        if (0 == list_iterator_next(&efsm_this->it, efsm_this->list))
        {
            efsm_transfer(it_curr.current, &efsm_this->it.current);
        }
        break;
    case EFSM_EVENT_STOP:
        break;
    case EFSM_EVENT_PREV:
        list_iterator_next(&efsm_this->it, efsm_this->list);
        efsm_transfer(it_curr.current, &efsm_this->it.current);
        break;
    case EFSM_EVENT_NEXT:
        break;
    case EFSM_EVENT_VALUE:
        break;
    case EFSM_EVENT_USER:
        break;
    default:
        break;
    }
}
