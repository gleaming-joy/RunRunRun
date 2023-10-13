/* Includes ------------------------------------------------------------------*/

#include "Chassis.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

SpeedTypeDef v_now=
{
    0, 0, 0
};

/* Private function declarations ---------------------------------------------*/

/**
 * @brief �޷�����
 *
 * @tparam Type
 * @param x ��������
 * @param Min ��Сֵ
 * @param Max ���ֵ
 */
template <typename Type>
void Math_Constrain(Type* x, Type Min, Type Max)
{
    if (*x < Min)
    {
        *x = Min;
    }
    else if (*x > Max)
    {
        *x = Max;
    }
}

/**
 * @brief �����ֵ
 *
 * @tparam Type
 * @param x ��������
 * @return Type x�ľ���ֵ
 */
template <typename Type>
Type Math_Abs(Type x)
{
    return((x > 0) ? x : -x);
}

/**
 * @brief ��ʼ������
 *
 * @param __Driver_PWM_TIM ���ֵ��������ʱ�����
 * @param __Calculate_EXTI_TIM �ٶȼ��㶨ʱ�����
 */
void Class_Chassis::Init(TIM_HandleTypeDef __Driver_PWM_TIM, TIM_HandleTypeDef __Calculate_EXTI_TIM)
{
    Driver_PWM_TIM = __Driver_PWM_TIM;
    Calculate_TIM = __Calculate_EXTI_TIM;

    //�����ʼ��

    Motor[0].Init(__Driver_PWM_TIM, TIM_CHANNEL_1, Pin_Pushpull_MotorDirectionA1_Pin, Pin_Pushpull_MotorDirectionA1_GPIO_Port, Pin_Pushpull_MotorDirectionB1_Pin, Pin_Pushpull_MotorDirectionB1_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA1_Pin, Pin_Exti_HallEncoderA1_GPIO_Port, Pin_PullDown_HallEncoderB1_Pin, Pin_PullDown_HallEncoderB1_GPIO_Port);
    Motor[0].Set_Rotate_Direction_Flag(CW);

    Motor[1].Init(__Driver_PWM_TIM, TIM_CHANNEL_2, Pin_Pushpull_MotorDirectionA2_Pin, Pin_Pushpull_MotorDirectionA2_GPIO_Port, Pin_Pushpull_MotorDirectionB2_Pin, Pin_Pushpull_MotorDirectionB2_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA2_Pin, Pin_Exti_HallEncoderA2_GPIO_Port, Pin_PullDown_HallEncoderB2_Pin, Pin_PullDown_HallEncoderB2_GPIO_Port);
    Motor[1].Set_Rotate_Direction_Flag(CW);

    Motor[2].Init(__Driver_PWM_TIM, TIM_CHANNEL_3, Pin_Pushpull_MotorDirectionA3_Pin, Pin_Pushpull_MotorDirectionA3_GPIO_Port, Pin_Pushpull_MotorDirectionB3_Pin, Pin_Pushpull_MotorDirectionB3_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA3_Pin, Pin_Exti_HallEncoderA3_GPIO_Port, Pin_PullDown_HallEncoderB3_Pin, Pin_PullDown_HallEncoderB3_GPIO_Port);
    Motor[2].Set_Rotate_Direction_Flag(CW);

    Motor[3].Init(__Driver_PWM_TIM, TIM_CHANNEL_4, Pin_Pushpull_MotorDirectionA4_Pin, Pin_Pushpull_MotorDirectionA4_GPIO_Port, Pin_Pushpull_MotorDirectionB4_Pin, Pin_Pushpull_MotorDirectionB4_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA4_Pin, Pin_Exti_HallEncoderA4_GPIO_Port, Pin_PullDown_HallEncoderB4_Pin, Pin_PullDown_HallEncoderB4_GPIO_Port);
    Motor[3].Set_Rotate_Direction_Flag(CW);

    //���PID��ʼ��
    for (int i = 0; i < 4; i++)
    {
        Motor[i].Omega_PID.Init(2000, 3000, 25, ULONG_MAX, ULONG_MAX);
    }
}

/**
 * @brief ��ʼ������
 *
 * @param __RDriver_PWM_TIM ���ֵ��������ʱ�����
 * @param __Calculate_EXTI_TIM �ٶȼ��㶨ʱ�����
 */
void Class_Chassis::R_Init(TIM_HandleTypeDef __RDriver_PWM_TIM, TIM_HandleTypeDef __Calculate_EXTI_TIM)
{
    RDriver_PWM_TIM = __RDriver_PWM_TIM;
    Calculate_TIM = __Calculate_EXTI_TIM;

    RMotor[0].Init(__RDriver_PWM_TIM, TIM_CHANNEL_1, RMotorDirectionA1_Pin, RMotorDirectionA1_GPIO_Port, RMotorDirectionB1_Pin, RMotorDirectionB1_GPIO_Port);
    RMotor[0].Set_Rotate_Direction_Flag(CW);
    RMotor[1].Init(__RDriver_PWM_TIM, TIM_CHANNEL_2, RMotorDirectionA2_Pin, RMotorDirectionA2_GPIO_Port, RMotorDirectionB2_Pin, RMotorDirectionB2_GPIO_Port);
    RMotor[1].Set_Rotate_Direction_Flag(CCW);
}

/**
 * @brief �趨�����ٶ�
 *
 * @param __Velocity �����ٶ�
 */
void Class_Chassis::Set_Velocity(SpeedTypeDef __Velocity)
{
    Velocity = __Velocity;
}

/**
 * @brief �趨�����ٶ�
 *
 * @param __RVelocity �����ٶ�
 */
void Class_Chassis::R_Set_Velocity(float __RVelocity)
{
    RVelocity = __RVelocity;
}


/**
 * @brief �趨���̿��Ʒ�ʽ
 *
 * @param __Control_Method ���̿��Ʒ�ʽ
 */
void Class_Chassis::Set_Control_Method(Enum_Control_Method __Control_Method)
{
    Control_Method = __Control_Method;

    for (int i = 0; i < 4; i++)
    {
        Motor[i].Set_Control_Method(__Control_Method);
    }
}

/**
 * @brief ���̵�����������������жϴ�����
 *
 */
void Class_Chassis::Hall_Encoder_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //�ж��ж�Դ, ��ָ�������жϴ�����
    if (GPIO_Pin == Pin_Exti_HallEncoderA1_Pin)
    {
        Motor[0].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if (GPIO_Pin == Pin_Exti_HallEncoderA2_Pin)
    {
        Motor[1].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if (GPIO_Pin == Pin_Exti_HallEncoderA3_Pin)
    {
        Motor[2].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if (GPIO_Pin == Pin_Exti_HallEncoderA4_Pin)
    {
        Motor[3].Hall_Encoder_GPIO_EXTI_Callback();
    }
}


/**
 * @brief ��ʱ���жϴ�����
 *
 */
void Class_Chassis::Calculate_TIM_PeriodElapsedCallback()
{
    //�ٶȽ���
    Math_Constrain(&Velocity.X, -X_MAX, X_MAX);
    Math_Constrain(&Velocity.Y, -Y_MAX, Y_MAX);
    Math_Constrain(&Velocity.Omega, -OMEGA_MAX, OMEGA_MAX);
    Motor[0].Set_Omega_Target((-OMEGA_TO_MS * 0.8f * Velocity.Omega + Velocity.Y - Velocity.X) / WHEEL_RADIUS * ((Motor[0].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));
    Motor[1].Set_Omega_Target((OMEGA_TO_MS * 0.8f * Velocity.Omega + Velocity.Y + Velocity.X) / WHEEL_RADIUS * ((Motor[1].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));
    Motor[2].Set_Omega_Target((-OMEGA_TO_MS * 1.4f * Velocity.Omega + Velocity.Y + 1.5f * Velocity.X) / WHEEL_RADIUS * ((Motor[2].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));
    Motor[3].Set_Omega_Target((OMEGA_TO_MS * 1.6f * Velocity.Omega + Velocity.Y - 1.5f * Velocity.X) / WHEEL_RADIUS * ((Motor[3].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));

    //������ֵ�趨�����
    for (int i = 0; i < 4; i++)
    {
        Motor[i].Calculate_TIM_PeriodElapsedCallback();
    }

}

 void Class_Chassis::R_Calculate_TIM_PeriodElapsedCallback()
 {
     Math_Constrain(&RVelocity, -R_MAX, R_MAX);
     RMotor[0].R_Set_Out(RVelocity / R_WHEEL_RADIUS * ((RMotor[0].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)) * MOTOR_CALCULATE_PRESCALER / MOTOR_FULL_OMEGA);
     RMotor[1].R_Set_Out(RVelocity / R_WHEEL_RADIUS * ((RMotor[1].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)) * MOTOR_CALCULATE_PRESCALER / MOTOR_FULL_OMEGA);

     //���
     for (int i = 0; i < 2; i++)
     {
         RMotor[i].R_Output();
     }
 }

/**
 * @brief ������Ĳ����趨Ϊ�����ٶ�
 * 
 * @param float x
 * @param float y
 * @param float omega
*/
void Class_Chassis::Velocity_Control(float __x, float __y, float __omega)
{
//    v_now = 
//    {
//        x, y, omega
//    };
		v_now.X = __x;
		v_now.Y = __y;
		v_now.Omega = __omega;
    Chassis.Set_Velocity(v_now);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
}

/**
 * @brief ������Ĳ����趨Ϊ�����ٶ�
 * 
 * @param
*/
void Class_Chassis::R_Velocity_Control(float vl,float vr)
{
    Math_Constrain(&vl, -R_MAX, R_MAX);
    Math_Constrain(&vr, -R_MAX, R_MAX);
    RMotor[0].R_Set_Out(vl / R_WHEEL_RADIUS * ((RMotor[0].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)) * MOTOR_CALCULATE_PRESCALER / MOTOR_FULL_OMEGA);
    RMotor[1].R_Set_Out(vr / R_WHEEL_RADIUS * ((RMotor[0].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)) * MOTOR_CALCULATE_PRESCALER / MOTOR_FULL_OMEGA);
    RMotor[0].R_Output();
    RMotor[1].R_Output();
}   
/* Function prototypes -------------------------------------------------------*/
