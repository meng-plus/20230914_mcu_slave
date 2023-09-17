/**
 * @file motor_port.c
 * @author 蒙蒙plus (chengmeng_2@outlook.com)
 * @brief 电机驱动的接口文件
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "gpio.h"
#include "tim.h"
#include "motor.h"
void motor_hardware_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = O11_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void motor_port_gpio_ctrl(MOTOR_CTRL_E ctrl)
{
    switch (ctrl)
    {
    case MOTOR_IDLE: /*!< 自由悬空 */
        HAL_GPIO_WritePin(GPIOB, O11_Pin | O12_Pin, GPIO_PIN_RESET);
        break;
    case MOTOR_FORWARD: /*!< 正转 */
        HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_WritePin(GPIOB, O12_Pin, GPIO_PIN_SET);
        break;
    case MOTOR_REVERSE: /*!< 反转 */
        HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_SET);
        // HAL_GPIO_WritePin(GPIOB, O12_Pin, GPIO_PIN_RESET);
        break;
    case MOTOR_STOP: /*!<短路刹车 */
        HAL_GPIO_WritePin(GPIOB, O11_Pin | O12_Pin, GPIO_PIN_SET);
        break;
    case MOTOR_PER:
        HAL_GPIO_WritePin(GPIOB, O11_Pin | O12_Pin, GPIO_PIN_SET);
        break;
    default:
        break;
    }
}
void motor_port_set_speed(float per)
{
    if (0 == per)
    { /*!< 停机 */
        HAL_TIMEx_PWMN_Stop(&htim4, TIM_CHANNEL_1);
    }
    else
    {
        if (HAL_TIM_CHANNEL_STATE_BUSY != TIM_CHANNEL_STATE_GET(&htim4, TIM_CHANNEL_1))
        { /*!< 未开PWM 则启动 */
            HAL_TIMEx_PWMN_Start(&htim4, TIM_CHANNEL_1);
        }
        if (0 > per)
        { /*!< 正传 */
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);
            HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_RESET);
        }
        else if (0 < per)
        { /*!< 反转 */
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1000 - speed);
            HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_SET);
        }
    }
}
