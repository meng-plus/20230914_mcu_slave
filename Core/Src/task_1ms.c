#include "main.h"

 extern "C" void task_1ms()
{

    uint32_t tick_cur = HAL_GetTick();
    { /*!<  IO 输出控制 */
        static uint32_t tick_next = 0;
        if (tick_next < tick_cur)
        {
            return;
        }
        tick_next = tick_cur + 1;

        /** 获得方向输入 */
        uint16_t input_data_cur = 0;
        input_data_cur = HAL_GPIO_ReadPin(X0_GPIO_Port, X0_Pin);
        input_data_cur |= HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin) << 1;
        input_data_cur |= HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin) << 2;
        input_data_cur |= HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin) << 3;
        input_data_cur |= HAL_GPIO_ReadPin(X4_GPIO_Port, X4_Pin) << 4;
        input_data_cur |= HAL_GPIO_ReadPin(X5_GPIO_Port, X5_Pin) << 5;
        input_data_cur |= HAL_GPIO_ReadPin(X6_GPIO_Port, X6_Pin) << 6;
        input_data_cur |= HAL_GPIO_ReadPin(X7_GPIO_Port, X7_Pin) << 7;
        input_data_cur |= HAL_GPIO_ReadPin(X8_GPIO_Port, X8_Pin) << 8;
        input_data_cur |= HAL_GPIO_ReadPin(X9_GPIO_Port, X9_Pin) << 9;
        input_data_cur |= HAL_GPIO_ReadPin(X10_GPIO_Port, X10_Pin) << 10;
        input_data_cur |= HAL_GPIO_ReadPin(X11_GPIO_Port, X11_Pin) << 11;
        input_data_cur |= HAL_GPIO_ReadPin(X12_GPIO_Port, X12_Pin) << 12;
        input_data_cur |= HAL_GPIO_ReadPin(X13_GPIO_Port, X13_Pin) << 13;
        input_data_cur |= HAL_GPIO_ReadPin(X14_GPIO_Port, X14_Pin) << 14;
        // input_data_cur |= HAL_GPIO_ReadPin(X15_GPIO_Port, X15_Pin) << 1;

        if (input_data_cur != g_sysRam.input_data)
        {
            // 切换任务 do something
            // g_sysRam.out_step = 0; /*!< 复位步骤 */
        }
        g_sysRam.input_data = input_data_cur;

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
                HAL_GPIO_WritePin(Y2_GPIO_Port, Y2_Pin, GPIO_PIN_RESET);
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
