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

void Arm_Complete_Catch(float location);

//局部动作
void LinePatrol_Catch_LOrange();
void LinePatrol_Catch_ROrange();
void LinePatrol_Catch_Purple();
void LinePatrol_Catch_Right_Purple();
void LinePatrol_Catch_Purple_NoVision();
void Barrier_to_Catch(uint8_t model);
void High_Spin();
void Spin_Back();
void L_Skip();

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
void Place_Brick_Right();

void Catch_Orange_NoVision_1();
void Catch_Orange_NoVision_2();
void Catch_Orange_NoVision_3();
void Catch_Purple_NoVision_1();
void Catch_Purple_NoVision_2();
void Catch_Purple_NoVision_3();

void Whole_Process_Left(uint32_t mode);
void Whole_Process_Right(uint32_t mode);

#endif
