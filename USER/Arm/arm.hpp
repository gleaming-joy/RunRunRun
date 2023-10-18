#ifndef ARM_HPP
#define ARM_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "steer.hpp"

/* Exported macros -----------------------------------------------------------*/
                                           
/* Exported types ------------------------------------------------------------*/

class Class_Arm
{
public:
    void Init(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, Class_Steer __Box_Steer);

    void Arm_Claw_Steer_Control(float Arm_Angle_0, float Arm_Angle_1, float Arm_Angle_2, float Arm_Angle_3, uint16_t Claw_Stat);

    void Arm_Rest();
    void Arm_Catch();
    void Arm_Catch_Back();

    void Box_Steer_Rotate(float location);

protected:
    Class_Steer *Arm_Steer;
    Class_Steer Claw_Steer;
    Class_Steer Box_Steer;
};

extern Class_Arm Arm;
/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif
