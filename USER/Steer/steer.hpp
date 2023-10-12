#ifndef STEER_HPP
#define STEER_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported macros -----------------------------------------------------------*/

//Բ����
extern const float PI;

//���PWM����
const float STEER_PWM_PERIOD = 0.003f;

//���PWM��ռ�ձȶ�Ӧ����ֵ
const int32_t STEER_PWM_PRESCALER = 2999;

//������Ķ�Ӧʱ��
const float STEER_PWM_MIDDLE = 0.0015;

//�����С��Ӧʱ��
const float STEER_PWM_LEFT = 0.0005;

//�������Ӧʱ��
const float STEER_PWM_RIGHT = 0.0025;

//����������������ʱ��
const float STEER_PWM_EXTREME_TO_MIDDLE = 0.001;

/* Exported types ------------------------------------------------------------*/

class Class_Steer
{
public:


    void Init(TIM_HandleTypeDef __Driver_PWM_TIM, uint8_t __Driver_PWM_TIM_Channel_x);

    void Set_Out(float output, float Max_Angle);

    void Output();

		void Stop();

protected:

    //���������ʱ�����
    TIM_HandleTypeDef Driver_PWM_TIM;
    //��ʱ��ͨ��
    uint8_t Driver_PWM_TIM_Channel_x;

    //����Ƕȷ�Χ, Ĭ��270�ȶ��
    //float Max_Angle = 270;
    //�����������
    int32_t Out;

};

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif
