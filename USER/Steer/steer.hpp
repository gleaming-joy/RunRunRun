#ifndef STEER_HPP
#define STEER_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported macros -----------------------------------------------------------*/

//圆周率
extern const float PI;

//舵机PWM周期
const float STEER_PWM_PERIOD = 0.003f;

//舵机PWM满占空比对应的数值
const int32_t STEER_PWM_PRESCALER = 2999;

//舵机中心对应时间
const float STEER_PWM_MIDDLE = 0.0015;

//舵机最小对应时间
const float STEER_PWM_LEFT = 0.0005;

//舵机最大对应时间
const float STEER_PWM_RIGHT = 0.0025;

//舵机极端与中心相对时间
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

    //舵机驱动定时器编号
    TIM_HandleTypeDef Driver_PWM_TIM;
    //定时器通道
    uint8_t Driver_PWM_TIM_Channel_x;

    //舵机角度范围, 默认270度舵机
    //float Max_Angle = 270;
    //设置输出级别
    int32_t Out;

};

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif
