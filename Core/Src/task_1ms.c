#include "main.h"

void task_1ms()
{

    uint32_t tick_cur = HAL_GetTick();
    { /*!<  IO 输出控制 */
        static uint32_t tick_next = 0;
        if (tick_next < tick_cur)
        {
            return;
        }
        tick_next = tick_cur + 1;

        static uint8_t status = 0;
        static uint32_t tick_flag1 = 0;
        switch (status)
        {
            /** 第一步 */
        case 0x00: /*!< start X0 = 0 */
            if (HAL_GPIO_ReadPin(X0_GPIO_Port, X0_Pin))
            {
                status++;
            }
            break;
        case 0x01: /*!<  start X0 1->0 */
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(X0_GPIO_Port, X0_Pin))
            {
                status++;
                HAL_GPIO_WritePin(Y2_GPIO_Port, Y2_Pin, GPIO_PIN_SET);
            }
            break;
        case 0x02: /*!< Io输出低电平脉冲 开始*/
            if (HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin))
            {
                status++;
            }
            break;
        case 0x03:
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin))
            {
                status++;
            }
            break;
        case 0x04: /*!< Io输出低电平脉冲 结束 */
            if (GPIO_PIN_SET == HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin))
            {
                status++;
            }
            break;
        case 0x05: /*!< I1输出低电平脉冲结束 */
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin))
            {
                status++;
                tick_flag1 = tick_cur;
            }
            break;
        case 0x06: /*!< 等待50ms */
            if (tick_flag1 + 50 > tick_cur)
            {
                status++;
            }
            break;
        /** 第二步 */
        case 0x06:
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin))
            {
                status++;
                tick_flag1 = tick_cur;
            }
            break;
        default:
            break;
        }
    }


    {
        /*!< 步进电机控制 */
        static uint32_t tick_next = 0;
        if (tick_next < tick_cur)
        {
            return;
        }
        tick_next = tick_cur + 1;
    }
}
