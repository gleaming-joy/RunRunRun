#include "StepMotor.h"

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == TestMotor1.Get_htim())
    {
        TestMotor1.Set_Motor_Timer_Output();
    }
}

//设置步进电机的运动状态，包括步进电机的速度、最大步数和旋转方向
void StepMotor::Set_Motor_Running_Speed(uint32_t step_per_second, uint32_t max_running_steps)
{
    this->remain_half_pulse = 2 * max_running_steps;
    this->tim_counts_per_half_pulse = TIM_Rate / (step_per_second * 2);
}

void StepMotor::Set_Motor_Running_Status(uint16_t enable, uint16_t direction)
{
		if (direction)
    {
        HAL_GPIO_WritePin(this->DirectionGPIOx, this->DirectionGPIO_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(this->DirectionGPIOx, this->DirectionGPIO_Pin, GPIO_PIN_SET);
    }
		if(enable)
		{
				HAL_GPIO_WritePin(this->EnableGPIOx, this->EnableGPIO_Pin, GPIO_PIN_RESET);
		}
		else
		{
				HAL_GPIO_WritePin(this->EnableGPIOx, this->EnableGPIO_Pin, GPIO_PIN_SET);
		}
}
    
		
//控制步进电机生成脉冲信号，驱动电机旋转
void StepMotor::Set_Motor_Timer_Output()
{
    if (this->remain_half_pulse == 0)
    {
        HAL_GPIO_WritePin(this->EnableGPIOx, this->EnableGPIO_Pin, GPIO_PIN_SET);
    }
    uint32_t count;
    count = __HAL_TIM_GET_COUNTER(this->htim);
    __HAL_TIM_SET_COMPARE(this->htim, this->TIM_Channel, count + this->tim_counts_per_half_pulse);
    this->remain_half_pulse --;
}

void StepMotor::init(TIM_HandleTypeDef *htim,
                    uint32_t TIM_Channel, 
                    uint32_t TIM_Rate, 
                    GPIO_TypeDef *EnableGPIOx, 
                    uint16_t EnableGPIO_Pin, 
                    GPIO_TypeDef *DirectionGPIOx, 
                    uint16_t DirectionGPIO_Pin)
{
    this->htim = htim;
    this->TIM_Channel = TIM_Channel;
    this->TIM_Rate = TIM_Rate;
    __HAL_TIM_SET_COMPARE(this->htim, this->TIM_Channel, 100);
	HAL_TIM_Base_Start(this->htim);
	HAL_TIM_OC_Start_IT(this->htim, this->TIM_Channel);//启动比较输出使能中断
    this->EnableGPIOx = EnableGPIOx;
    this->DirectionGPIOx = DirectionGPIOx;
    this->EnableGPIO_Pin = EnableGPIO_Pin;
    this->DirectionGPIO_Pin = DirectionGPIO_Pin;
}

TIM_HandleTypeDef *StepMotor::Get_htim(){
    return this->htim;
}
