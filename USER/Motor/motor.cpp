/* Includes ------------------------------------------------------------------*/

#include "motor.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

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
void Math_Constrain(Type *x, Type Min, Type Max)
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
 * @brief ��ʼ�����
 * 
 * @param __Driver_PWM_TIM ���������ʱ�����
 * @param __Driver_PWM_TIM_Channel_x ���������ʱ��ͨ��
 * @param __Output_A_GPIO_Pin �������A�����ź�
 * @param __Output_A_GPIOx �������A��������
 * @param __Output_B_GPIO_Pin �������B�����ź�
 * @param __Output_B_GPIOx �������B��������
 */
void Class_Motor::Init(TIM_HandleTypeDef __Driver_PWM_TIM, uint8_t __Driver_PWM_TIM_Channel_x, uint16_t __Output_A_GPIO_Pin, GPIO_TypeDef *__Output_A_GPIOx, uint16_t __Output_B_GPIO_Pin, GPIO_TypeDef *__Output_B_GPIOx)
{
    Driver_PWM_TIM = __Driver_PWM_TIM;
    Driver_PWM_TIM_Channel_x = __Driver_PWM_TIM_Channel_x;
    Output_A_GPIO_Pin = __Output_A_GPIO_Pin;
    Output_A_GPIOx = __Output_A_GPIOx;
    Output_B_GPIO_Pin = __Output_B_GPIO_Pin;
    Output_B_GPIOx = __Output_B_GPIOx;

    //���PWM
    HAL_TIM_PWM_Start(&__Driver_PWM_TIM, __Driver_PWM_TIM_Channel_x);
}

/**
 * @brief �趨���������ת����
 *
 * @param __Rotate_Direction_Flag ���������ת����
 */
void Class_Motor::Set_Rotate_Direction_Flag(Enum_Rotate_Direction __Rotate_Direction_Flag)
{
    Rotate_Direction_Flag = __Rotate_Direction_Flag;
}

/**
 * @brief �趨������ٺ����תת��
 *
 * @param __Motor_Full_Omega ������ٺ���תת�ٶ�Ӧ����ֵ
 */
void Class_Motor::Set_Motor_Full_Omega(float __Motor_Full_Omega)
{
    Motor_Full_Omega = __Motor_Full_Omega;
}

/**
 * @brief �趨���PWM��ռ�ձȶ�Ӧ����ֵ
 *
 * @param __Motor_PWM_Period ���PWM��ռ�ձȶ�Ӧ����ֵ
 */
void Class_Motor::Set_Motor_PWM_Period(int32_t __Motor_PWM_Period)
{
    Motor_PWM_Period = __Motor_PWM_Period;
}

/**
 * @brief �趨���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 *
 * @param __Out ���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 */
void Class_Motor::Set_Out(int32_t __Out)
{
    Out = __Out;
}

/**
 * @brief �趨���ֵ��Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 *
 * @param __ROut ���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 */
void Class_Motor::R_Set_Out(int32_t __ROut)
{
    ROut = __ROut;
}

/**
 * @brief ��ȡ���������ת����
 *
 * @return Enum_Rotate_Direction ���������ת����
 */
Enum_Rotate_Direction Class_Motor::Get_Rotate_Direction_Flag()
{
    return(Rotate_Direction_Flag);
}

/**
 * @brief ��ȡ������ٺ���תת��, rad/s
 *
 * @return float ������ٺ���תת��, rad/s
 */
float Class_Motor::Get_Motor_Full_Omega()
{
    return(Motor_Full_Omega);
}

/**
 * @brief ��ȡ���PWM��ռ�ձȶ�Ӧ����ֵ
 *
 * @return int32_t ���PWM��ռ�ձȶ�Ӧ����ֵ
 */
int32_t Class_Motor::Get_Motor_PWM_Period()
{
    return(Motor_PWM_Period);
}

/**
 * @brief ��ȡ���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 *
 * @return int32_t ���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 */
int32_t Class_Motor::Get_Out()
{
    return(Out);
}

/**
 * @brief ��ȡ���ֵ��Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 *
 * @return int32_t ���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
 */
int32_t Class_Motor::R_Get_Out()
{
    return(ROut);
}

/**
 * @brief �趨���ֵ��ռ�ձ�, ȷ�����
 *
 */
void Class_Motor::Output()
{
    if (Out == 0)
    {
        HAL_GPIO_WritePin(Output_A_GPIOx, Output_A_GPIO_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Output_B_GPIOx, Output_B_GPIO_Pin, GPIO_PIN_RESET);
    }
    else if (Out > 0)
    {
        HAL_GPIO_WritePin(Output_A_GPIOx, Output_A_GPIO_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(Output_B_GPIOx, Output_B_GPIO_Pin, GPIO_PIN_RESET);
    }
    else if (Out < 0)
    {
        HAL_GPIO_WritePin(Output_A_GPIOx, Output_A_GPIO_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Output_B_GPIOx, Output_B_GPIO_Pin, GPIO_PIN_SET);
    }
    __HAL_TIM_SetCompare(&Driver_PWM_TIM, Driver_PWM_TIM_Channel_x, Math_Abs(Out));
}

/**
 * @brief �趨���ֵ��ռ�ձ�, ȷ�����
 *
 */
void Class_Motor::R_Output()
{
    if (ROut == 0)
    {
        HAL_GPIO_WritePin(Output_A_GPIOx, Output_A_GPIO_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Output_B_GPIOx, Output_B_GPIO_Pin, GPIO_PIN_RESET);
    }
    else if (ROut > 0)
    {
        HAL_GPIO_WritePin(Output_A_GPIOx, Output_A_GPIO_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(Output_B_GPIOx, Output_B_GPIO_Pin, GPIO_PIN_RESET);
    }
    else if (ROut < 0)
    {
        HAL_GPIO_WritePin(Output_A_GPIOx, Output_A_GPIO_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Output_B_GPIOx, Output_B_GPIO_Pin, GPIO_PIN_SET);
    }
    __HAL_TIM_SetCompare(&Driver_PWM_TIM, Driver_PWM_TIM_Channel_x, Math_Abs(999));
}

/**
 * @brief ��ʼ�����
 *
 * @param __Driver_PWM_TIM ���������ʱ�����
 * @param __Driver_PWM_TIM_Channel_x ���������ʱ��ͨ��
 * @param __Output_A_GPIO_Pin �������A�����ź�
 * @param __Output_A_GPIOx �������A��������
 * @param __Output_B_GPIO_Pin �������B�����ź�
 * @param __Output_B_GPIOx �������B��������
 * @param __Calculate_TIM �ٶȼ��㶨ʱ�����
 * @param __Input_A_GPIO_Pin ��������������A���ź�
 * @param __Input_A_GPIOx ��������������A������
 * @param __Input_B_GPIO_Pin ��������������B���ź�
 * @param __Input_B_GPIOx ��������������B������
 */
void Class_Motor_With_Hall_Encoder::Init(TIM_HandleTypeDef __Driver_PWM_TIM, uint8_t __Driver_PWM_TIM_Channel_x, uint16_t __Output_A_GPIO_Pin, GPIO_TypeDef* __Output_A_GPIOx, uint16_t __Output_B_GPIO_Pin, GPIO_TypeDef* __Output_B_GPIOx, TIM_HandleTypeDef __Calculate_TIM, uint16_t __Input_A_GPIO_Pin, GPIO_TypeDef* __Input_A_GPIOx, uint16_t __Input_B_GPIO_Pin, GPIO_TypeDef* __Input_B_GPIOx)
{
    Driver_PWM_TIM = __Driver_PWM_TIM;
    Driver_PWM_TIM_Channel_x = __Driver_PWM_TIM_Channel_x;
    Output_A_GPIO_Pin = __Output_A_GPIO_Pin;
    Output_A_GPIOx = __Output_A_GPIOx;
    Output_B_GPIO_Pin = __Output_B_GPIO_Pin;
    Output_B_GPIOx = __Output_B_GPIOx;
    Calculate_TIM = __Calculate_TIM;
    Input_A_GPIO_Pin = __Input_A_GPIO_Pin;
    Input_A_GPIOx = __Input_A_GPIOx;
    Input_B_GPIO_Pin = __Input_B_GPIO_Pin;
    Input_B_GPIOx = __Input_B_GPIOx;
    HAL_TIM_PWM_Start(&__Driver_PWM_TIM, __Driver_PWM_TIM_Channel_x);
}

/**
 * @brief �趨������Ʒ�ʽ
 *
 * @param __Control_Method ������Ʒ�ʽ
 */
void Class_Motor_With_Hall_Encoder::Set_Control_Method(Enum_Control_Method __Control_Method)
{
    Control_Method = __Control_Method;
}

/**
 * @brief �趨Ŀ����ת��, rad/s
 *
 * @param __Omega_Target Ŀ����ת��, rad/s
 */
void Class_Motor_With_Hall_Encoder::Set_Omega_Target(float __Omega_Target)
{
    Omega_Target = __Omega_Target;
}

/**
 * @brief �趨������ٺ����������������, /rad
 *
 * @param __Motor_Encoder_Num_Per_Rad Ŀ����ת��, rad/s
 */
void Class_Motor_With_Hall_Encoder::Set_Motor_Encoder_Num_Per_Rad(float __Motor_Encoder_Num_Per_Rad)
{
    Motor_Encoder_Num_Per_Rad = __Motor_Encoder_Num_Per_Rad;
}

/**
 * @brief �趨Ŀ�����Ƕ�, rad
 *
 * @param __Angle_Target Ŀ�����Ƕ�, rad
 */
void Class_Motor_With_Hall_Encoder::Set_Angle_Target(float __Angle_Target)
{
    Angle_Target = __Angle_Target;
}

/**
 * @brief ��ȡ������Ʒ�ʽ
 *
 * @return Enum_Control_Method ������Ʒ�ʽ
 */
Enum_Control_Method Class_Motor_With_Hall_Encoder::Get_Control_Method()
{
    return(Control_Method);
}

/**
 * @brief ��ȡ��ǰ���ת��, rad/s
 *
 * @return float ��ǰ���ת��, rad/s
 */
float Class_Motor_With_Hall_Encoder::Get_Omega_Now()
{
    return(Omega_Now);
}

/**
 * @brief ��ȡ��ǰ����Ƕ�, rad
 *
 * @return float ��ǰ����Ƕ�, rad
 */
float Class_Motor_With_Hall_Encoder::Get_Angle_Now()
{
    return(Angle_Now);
}

/**
 * @brief �����������жϴ�����
 *
 */
void Class_Motor_With_Hall_Encoder::Hall_Encoder_GPIO_EXTI_Callback()
{
    //������ת���ı�����, �Ա��������ǶȺ��ٶ�
    if (((HAL_GPIO_ReadPin(Input_B_GPIOx, Input_B_GPIO_Pin) == 0) ^ (Rotate_Direction_Flag == CW)) == 0)
    {
        Hall_Encoder_Count--;
    }
    else
    {
        Hall_Encoder_Count++;
    }
}

/**
 * @brief ��ʱ���жϴ�����
 *
 */
void Class_Motor_With_Hall_Encoder::Calculate_TIM_PeriodElapsedCallback()
{
    int32_t delta;
    delta = Hall_Encoder_Count - Prev_Hall_Encoder_Count;
    //����Ƕ�
    Angle_Now += (float)delta / Motor_Encoder_Num_Per_Rad;
    //�����ٶ�
    Omega_Now = (float)delta / Motor_Encoder_Num_Per_Rad / MOTOR_CALCULATE_PERIOD;
    Prev_Hall_Encoder_Count = Hall_Encoder_Count;

    if (Control_Method == Control_Method_OPENLOOP)
    {
        //��������ֱ������ٶ�
        Out = Omega_Target * Motor_PWM_Period / Motor_Full_Omega;
    }
    else if (Control_Method == Control_Method_OMEGA)
    {
        //�ٶȿ���, ����PID

        Omega_PID.Set_Now(Omega_Now);
        Omega_PID.Set_Target(Omega_Target);
        Omega_PID.Adjust_TIM_PeriodElapsedCallback();
        Out = Omega_PID.Get_Out();

    }
    else if (Control_Method == Control_Method_ANGLE)
    {
        //�Ƕȿ���, ˫��PID

        Angle_PID.Set_Target(Angle_Target);

        Angle_PID.Set_Now(Angle_Now);
        Angle_PID.Adjust_TIM_PeriodElapsedCallback();
        Omega_PID.Set_Target(Angle_PID.Get_Out());

        Omega_PID.Set_Now(Omega_Now);
        Omega_PID.Adjust_TIM_PeriodElapsedCallback();
        Out = Omega_PID.Get_Out();
    }
    Math_Constrain(&Out, -MOTOR_CALCULATE_PRESCALER, MOTOR_CALCULATE_PRESCALER);
    Output();
}

/* Function prototypes -------------------------------------------------------*/
