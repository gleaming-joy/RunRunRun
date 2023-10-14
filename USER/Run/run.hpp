#ifndef RUN_HPP
#define RUN_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "chassis.hpp"
#include "arm.hpp"
#include "StepMotor.h"
#include "connect.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

//局部动作
void LinePatrol_Easy_Catch_Orange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);

//整体运动
void Start_to_High(Class_Steer __Arm_Steer[] ,Class_Steer __Claw_Steer);
void Start_to_Barrier();
void Cross_Barrier();
void Back_Cross_Barrier();
void Barrier_to_Start();
#endif
