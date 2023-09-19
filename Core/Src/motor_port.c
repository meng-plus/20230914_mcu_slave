/**
 * @file motor_port.c
 * @author ����plus (chengmeng_2@outlook.com)
 * @brief ��������Ľӿ��ļ�
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
    case MOTOR_IDLE: /*!< �������� */
        HAL_GPIO_WritePin(GPIOB, O11_Pin | O12_Pin, GPIO_PIN_RESET);
        break;
    case MOTOR_FORWARD: /*!< ��ת */
        HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_WritePin(GPIOB, O12_Pin, GPIO_PIN_SET);
        break;
    case MOTOR_REVERSE: /*!< ��ת */
        HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_SET);
        // HAL_GPIO_WritePin(GPIOB, O12_Pin, GPIO_PIN_RESET);
        break;
    case MOTOR_STOP: /*!<��·ɲ�� */
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
    { /*!< ͣ�� */
        HAL_TIMEx_PWMN_Stop(&htim4, TIM_CHANNEL_1);
    }
    else
    {
        if (HAL_TIM_CHANNEL_STATE_BUSY != TIM_CHANNEL_STATE_GET(&htim4, TIM_CHANNEL_1))
        { /*!< δ��PWM ������ */
            HAL_TIMEx_PWMN_Start(&htim4, TIM_CHANNEL_1);
        }
        if (0 > per)
        { /*!< ���� */
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, speed);
            HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_RESET);
        }
        else if (0 < per)
        { /*!< ��ת */
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1000 - speed);
            HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_SET);
        }
    }
}
