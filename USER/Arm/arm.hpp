#ifndef ARM_HPP
#define ARM_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "steer.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

void Arm_Steer_Output_Get_Locate(Class_Steer __Arm_Steer[]);
void Arm_Steer_Output_Store_Locate(Class_Steer __Arm_Steer[]);

void Claw_Steer_Open(Class_Steer __Claw_Steer);
void Claw_Steer_Close(Class_Steer __Claw_Steer);

void Box_Steer_Rotate(Class_Steer __Box_Steer, float location);

void Arm_Catch(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
#endif
