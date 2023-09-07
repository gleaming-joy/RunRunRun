#ifndef CHASSIS_HPP
#define CHASSIS_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "motor.hpp"

/* Exported macros -----------------------------------------------------------*/

//轮半径, m
const float WHEEL_RADIUS = 0.0635f;

//轮组满转线速度, m/s
const float WHEEL_FULL_V = (MOTOR_FULL_OMEGA * WHEEL_RADIUS);

//omega到m/s映射系数, (横轮距+纵轮距)/2, m/rad
const float OMEGA_TO_MS = ((0.360f + 0.412f) / 2);

//绝对速度限制, 任何情况不能超过
//横移速度上限, m/s
const float X_MAX = 1.0f;
//前进速度上限, m/s
const float Y_MAX = 1.0f;
//旋转速度上限, rad/s
const float OMEGA_MAX = 2.0f;

/* Exported types ------------------------------------------------------------*/

/**
 * @brief 速度类型定义
 *
 */
struct SpeedTypeDef
{
    //横移 m/s 右为正
    float X;
    //前后 m/s 前为正
    float Y;
    //旋转 rad/s 逆时针为正
    float Omega;
};

class Class_Chassis
{
public:

    //底盘对应的电机
    Class_Motor_With_Hall_Encoder Motor[4];

    void Init(TIM_HandleTypeDef __Driver_PWM_TIM, TIM_HandleTypeDef __Calculate_EXTI_TIM);

    void Set_Velocity(SpeedTypeDef __Velocity);
    void Set_Control_Method(Enum_Control_Method __Control_Method);

    void Hall_Encoder_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
    void Calculate_TIM_PeriodElapsedCallback();

protected:

    //电机PWM驱动定时器
    TIM_HandleTypeDef Driver_PWM_TIM;
    //电机计算定时器中断
    TIM_HandleTypeDef Calculate_TIM;

    //底盘控制方式
    Enum_Control_Method Control_Method = Control_Method_OMEGA;

    //底盘速度
    SpeedTypeDef Velocity =
    {
        0,
        0,
        0
    };

};

extern Class_Chassis Chassis;

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif
