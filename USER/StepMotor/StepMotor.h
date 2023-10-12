#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#include "stm32f4xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim5;

class StepMotor
{
private:
    TIM_HandleTypeDef *htim;
    uint32_t TIM_Channel;
    uint32_t remain_half_pulse;
    uint32_t tim_counts_per_half_pulse;
    uint32_t TIM_Rate;
    GPIO_TypeDef *EnableGPIOx;
    uint16_t EnableGPIO_Pin;
    GPIO_TypeDef *DirectionGPIOx;
    uint16_t DirectionGPIO_Pin;
    
public:
    void Set_Motor_Running_Speed(uint32_t step_per_second, uint32_t max_running_steps);
		void Set_Motor_Running_Status(uint16_t enable, uint16_t direction);
    void Set_Motor_Timer_Output();
    void init(TIM_HandleTypeDef *htim,
                    uint32_t TIM_Channel, 
                    uint32_t TIM_Rate, 
                    GPIO_TypeDef *EnableGPIOx, 
                    uint16_t EnableGPIO_Pin, 
                    GPIO_TypeDef *DirectionGPIOx, 
                    uint16_t DirectionGPIO_Pin);
    TIM_HandleTypeDef *Get_htim();
};

extern StepMotor TestMotor1;


#endif
