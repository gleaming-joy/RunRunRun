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
void LinePatrol_Catch_LOrange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
void LinePatrol_Catch_ROrange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
void LinePatrol_Catch_Purple(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer);
void Barrier_to_Catch(uint8_t model);

//整体运动
void Start_to_High(Class_Steer __Arm_Steer[] ,Class_Steer __Claw_Steer);
void Start_to_Barrier();
void Cross_Barrier();
void Back_Cross_Barrier();
void Barrier_to_Start();
void Barrier_Position_Adjust();
#endif
