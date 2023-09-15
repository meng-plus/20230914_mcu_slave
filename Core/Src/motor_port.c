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
#include "motor.h"
void motor_hardware_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB, O11_Pin | O12_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = O11_Pin | O12_Pin;
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
        HAL_GPIO_WritePin(GPIOB, O12_Pin, GPIO_PIN_SET);
        break;
    case MOTOR_REVERSE: /*!< ��ת */
        HAL_GPIO_WritePin(GPIOB, O11_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, O12_Pin, GPIO_PIN_RESET);
        break;
    case MOTOR_STOP: /*!<��·ɲ�� */
        HAL_GPIO_WritePin(GPIOB, O11_Pin | O12_Pin, GPIO_PIN_SET);
        break;

    default:
        break;
    }
}
