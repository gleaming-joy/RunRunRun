#ifndef HCSR04_HPP
#define HCSR04_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

class Class_HCSR04
{
public:
    void Init(uint16_t __HCSR04_Trig_GPIO_Pin, GPIO_TypeDef* __HCSR04_Trig_GPIOx, uint16_t __HCSR04_Echo_GPIO_Pin, GPIO_TypeDef* __HCSR04_Echo_GPIOx);
    void HCSR04_Run();

    uint32_t Distance;

protected:

    uint16_t HCSR04_Trig_GPIO_Pin;
    GPIO_TypeDef* HCSR04_Trig_GPIOx;

    uint16_t HCSR04_Echo_GPIO_Pin;
    GPIO_TypeDef* HCSR04_Echo_GPIOx;
};

extern Class_HCSR04 HC1;

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

void HAL_Delay_us(uint32_t us);

#endif
