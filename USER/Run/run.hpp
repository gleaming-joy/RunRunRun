#ifndef RUN_HPP
#define RUN_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "chassis.hpp"
#include "arm.hpp"
#include "StepMotor.h"
#include "connect.hpp"
#include "HCSR04.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

//局部动作
void LinePatrol_Catch_LOrange();
void LinePatrol_Catch_LOrange_NoVisual();
void LinePatrol_Catch_ROrange();
void LinePatrol_Catch_Purple();
void LinePatrol_Catch_Purple_NoVision();
void Barrier_to_Catch(uint8_t model);
void High_Spin();
void Spin_Back();

//整体运动
void Start_to_High();
void Start_to_Barrier();
void Cross_Barrier();
void Back_Cross_Barrier();
void Barrier_to_Start();
void Barrier_Position_Adjust();
void Catch_Position_Adjust();
void High_to_Start();
void Place_Brick();
#endif
