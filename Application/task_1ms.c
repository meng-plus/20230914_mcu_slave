#include "main.h"
#include "efsm_task_0.h"
void task_1ms()
{

    uint32_t tick_cur = HAL_GetTick();
    { /*!<  IO ������� */
        static uint32_t tick_next = 0;
        if (tick_next < tick_cur)
        {
            return;
        }
        tick_next = tick_cur + 1;

        { /*!< init  */
            bool init_ok = 0;
            if (!init_ok)
            {
                efsm_init(&efsm_task_0);
                EFSM_EVENT_T event = EFSM_EVENT_IDLE;
                efsm_action(&efsm_task_0, &event);
                event = EFSM_EVENT_START;
                efsm_action(&efsm_task_0, &event);
            }
            EFSM_EVENT_T event = EFSM_EVENT_TICK;
            efsm_action(&efsm_task_0, &event);
        }
    }

    {
        /*!< ����������� */
        static uint32_t tick_next = 0;
        if (tick_next < tick_cur)
        {
            return;
        }
        tick_next = tick_cur + 1;

        void motor_ctrl_task();
        motor_ctrl_task();
    }
}
