/* Includes ------------------------------------------------------------------*/

#include "HCSR04.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 微秒级延时
 *
 * @param us 微秒数
 */
void HAL_Delay_us(uint32_t us)
{       
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000);
    HAL_Delay(us-1);
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
}

/**
 * @brief HC_SR04初始化
 *
 * @param uint16_t __HCSR04_Trig_GPIO_Pin
 * @param GPIO_TypeDef* __HCSR04_Trig_GPIOx
 * @param uint16_t __HCSR04_Echo_GPIO_Pin
 * @param GPIO_TypeDef* __HCSR04_Echo_GPIOx
 */
void Class_HCSR04::Init(uint16_t __HCSR04_Trig_GPIO_Pin, GPIO_TypeDef* __HCSR04_Trig_GPIOx, uint16_t __HCSR04_Echo_GPIO_Pin, GPIO_TypeDef* __HCSR04_Echo_GPIOx)
{
    HCSR04_Trig_GPIO_Pin = __HCSR04_Trig_GPIO_Pin;
    HCSR04_Trig_GPIOx = __HCSR04_Trig_GPIOx;
    HCSR04_Echo_GPIO_Pin = __HCSR04_Echo_GPIO_Pin;
    HCSR04_Echo_GPIOx = __HCSR04_Echo_GPIOx;
}


/**
 * @brief HC_SR04测量距离
 *
 * @param
 */

void Class_HCSR04::HCSR04_Run()
{
	uint32_t i = 0;
	uint32_t uc=1;
	HAL_GPIO_WritePin(HCSR04_Trig_GPIOx, HCSR04_Trig_GPIO_Pin, GPIO_PIN_SET);
	HAL_Delay_us(20);
	HAL_GPIO_WritePin(HCSR04_Trig_GPIOx, HCSR04_Trig_GPIO_Pin, GPIO_PIN_RESET);
	while(HAL_GPIO_ReadPin(HCSR04_Echo_GPIOx, HCSR04_Echo_GPIO_Pin) == GPIO_PIN_RESET)
	{
		uc++;
		if(uc>8000000)
		{
			// return 9999;
            Distance = 9999;
			break;
		}
	}
	while(HAL_GPIO_ReadPin(HCSR04_Echo_GPIOx, HCSR04_Echo_GPIO_Pin) != GPIO_PIN_RESET)
	{
		i++;
	}
	Distance = (uint32_t)i/35;
}