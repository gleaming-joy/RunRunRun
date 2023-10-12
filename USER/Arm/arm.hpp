#ifndef ARM_HPP
#define ARM_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "steer.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

void Arm_Claw_Steer_Control(float Arm_Angle_0, float Arm_Angle_1, float Arm_Angle_2, float Arm_Angle_3, uint16_t Claw_Stat, Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);

void Arm_Steer_Output_Get_High_Locate(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
void Arm_Steer_Output_Get_Low_Locate(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
void Arm_Steer_Output_Store_Locate(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
void Arm_Steer_Output_Go_Locate(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);

void Box_Steer_Rotate(Class_Steer __Box_Steer, float location);

void Arm_Catch(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
#endif
