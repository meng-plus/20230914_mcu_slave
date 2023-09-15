
#include "motor.h"

typedef struct _MOTOR_DATA
{
    MOTOR_CTRL_E ctrl;
} motor_data_t;
static motor_data_t s_motor_data = {
    .ctrl = MOTOR_IDLE};

/*!< extern function */
extern void motor_hardware_init();
extern void motor_port_gpio_ctrl(MOTOR_CTRL_E ctrl);
void motor_init()
{
    /*!< 硬件初始化 */
    // motor_hardware_init();

    /*!< 软件初始化 */
    motor_ctrl(MOTOR_IDLE);
}

void motor_ctrl(MOTOR_CTRL_E ctrl)
{
    s_motor_data.ctrl = ctrl;
    motor_port_gpio_ctrl(ctrl);
}

MOTOR_CTRL_E motor_get_ctrl()
{
    return s_motor_data.ctrl;
}
