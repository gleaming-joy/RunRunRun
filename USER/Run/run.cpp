/* Includes ------------------------------------------------------------------*/

#include "run.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

extern uint8_t LP_Receive_yl;
extern uint8_t LP_Receive_yr;
extern uint8_t LP_Receive_x;
extern uint8_t B_Receive;

extern uint8_t Barrier_Location;

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 简易采集右侧晶体矿
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 */
 
void LinePatrol_Easy_Catch_Orange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer)
{
	uint16_t counter = 0;
	Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 90.0f, 0, __Arm_Steer, __Claw_Steer);
	
	while(1)
	{
    Chassis.Velocity_Control(0, 0.4, 0);
		if ((LP_Receive_yl & (uint8_t)0x7F) == (uint8_t)0x38)
		{
      Chassis.Velocity_Control(0, 0, 0);
			Arm_Catch(__Arm_Steer, __Claw_Steer);
			HAL_Delay(1000);
			Arm_Catch_Back(__Arm_Steer, __Claw_Steer);
			counter++;
			if(counter == 5)
        break;
      Chassis.Velocity_Control(0, 0.4, 0);
			HAL_Delay(300);
		}
	}
  Chassis.Velocity_Control(0, 0, 0);
}

// void LinePatrol_Easy_Catch_Orange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, uint8_t *__LP_Receive_yr, UART_HandleTypeDef *__huart_yr)
// {
// 	uint16_t counter=0;
// 	LinePatrol_Receive(__huart_yr);
// 	Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 90.0f, 0, __Arm_Steer, __Claw_Steer);
	
// 	while(1)
// 	{
// 		Chassis.Set_Velocity(v_front);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
// 		if ((*__LP_Receive_yr & (uint8_t)0x7F) == (uint8_t)0x38)
// 		{
// 			Chassis.Set_Velocity(v_stop);
// 			Chassis.Calculate_TIM_PeriodElapsedCallback();
// 			Arm_Catch(__Arm_Steer, __Claw_Steer);
// 			HAL_Delay(1000);
// 			Arm_Catch_Back(__Arm_Steer, __Claw_Steer);
// 			counter++;
// 			if(counter==5) break;
// 			Chassis.Set_Velocity(v_front);
// 			Chassis.Calculate_TIM_PeriodElapsedCallback();
// 			HAL_Delay(300);
// 		}
// 	}
// 	Chassis.Set_Velocity(v_stop);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
// }

/**
 * @brief 从启动区上坡到高平面采矿区并完整采矿
 *
 * @param Class_Steer __Arm_Steer[]
 * @param Class_Steer __Claw_Steer
 * @param 
 */
void Start_to_High(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer)
{
    Arm_Catch(__Arm_Steer, __Claw_Steer);

    TestMotor1.Set_Motor_Running_Status(1,1);
    Chassis.Velocity_Control(0, 0.4, 0);
    RChassis.R_Velocity_Control(0.3f, 0.3f);
    HAL_Delay(3500);
    Chassis.Velocity_Control(0, 0, 0);
    RChassis.R_Velocity_Control(0.0f, 0.0f);
    HAL_Delay(10500);
        
    TestMotor1.Set_Motor_Running_Status(0,0);
    Chassis.Velocity_Control(0, 0.6, 0);
    RChassis.R_Velocity_Control(0.9f, 0.9f);
	while((LP_Receive_x & (uint8_t)0x99) != (uint8_t) 0x18);
	while(LP_Receive_x != (uint8_t) 0xFF);
	HAL_Delay(2500);
        
    TestMotor1.Set_Motor_Running_Status(1,0);
    Chassis.Velocity_Control(0, 0, 0);
    RChassis.R_Velocity_Control(0.0f, 0.0f);
    HAL_Delay(14000);
				
	TestMotor1.Set_Motor_Running_Status(0,0);
    Chassis.Velocity_Control(0.6, 0, 0);
    while((LP_Receive_yl & (uint8_t)0x38) != (uint8_t)0x38);
    HAL_Delay(1800);
    Chassis.Velocity_Control(0, 0, 0);
    HAL_Delay(14000);
					
	LinePatrol_Easy_Catch_Orange(__Arm_Steer, __Claw_Steer);
	HAL_Delay(2000);

    Chassis.Velocity_Control(-0.2, 0.1, -1);	
	HAL_Delay(800);
	while(LP_Receive_yl != LP_Receive_yr);
    Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(500);
    Chassis.Velocity_Control(0.6, 0, 0);
	while(LP_Receive_yl != 0xFF);
	while(LP_Receive_yl == 0xFF);
	HAL_Delay(100);
    Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(500);
    Chassis.Velocity_Control(0, 0.4, 0);
	while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
    Chassis.Velocity_Control(0, 0, 0);
	Arm_Catch(__Arm_Steer, __Claw_Steer);
	HAL_Delay(1000);
	Arm_Catch_Back(__Arm_Steer, __Claw_Steer);
    Chassis.Velocity_Control(0, 0.4, 0);
	HAL_Delay(300);
	while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
    Chassis.Velocity_Control(0, 0, 0);
	Arm_Catch(__Arm_Steer, __Claw_Steer);
	HAL_Delay(1000);
	Arm_Catch_Back(__Arm_Steer, __Claw_Steer);
	HAL_Delay(20000);
}

/**
 * @brief 从启动区向左平移到避障区
 *
 * @param 
 */
void Start_to_Barrier()
{
  //前进
  while (LP_Receive_yl != (uint8_t)0x00)
  {
	if (LP_Receive_yl < (uint8_t)0x60) //0110,0000
    {
		Chassis.Velocity_Control(0.6,0.2,0);
		HAL_Delay(200);
    }
    else if (LP_Receive_yl > (uint8_t)0x70)
    {
		Chassis.Velocity_Control(0.6,-0.2,0);
		HAL_Delay(200);
    }	
	else if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
	{
		Chassis.Velocity_Control(0.6,0,0.3);
		HAL_Delay(200);
	}
	else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
	{
		Chassis.Velocity_Control(0.6,0,-0.3);
		HAL_Delay(200);
	}
    else
    {
		Chassis.Velocity_Control(0.6,0,0);
		HAL_Delay(400);
    }
  }
  Chassis.Velocity_Control(0, 0, 0);
  HAL_Delay(2000);
}

/**
 * @brief 障碍识别及位置调整
 *
 * @param 
 */
void Cross_Barrier()
{
  Berry_Barrier_Open();
  //第一次识别（此时车在右侧）
  Berry_Receive();
  //第一个障碍物在右侧（此时车在右侧）
  if (B_Receive == (uint8_t)0x00)
  {
    //向左前移动避开障碍物
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0.4, 0.6, 0);
    }
    Chassis.Velocity_Control(0, 0, 0);
    //第二次识别（此时车在左侧）
    Berry_Receive();
    //第二个障碍物在左侧（此时车在左侧）
    if (B_Receive == (uint8_t)0x00)
    {
      //向右前移动避开障碍物
      while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
      {
        Chassis.Velocity_Control(-0.4, 0.6, 0);
      }
      //向左前移动到采矿区
      while (LP_Receive_x != 0xFF)
      {
        Chassis.Velocity_Control(0.4, 0.6, 0);
      }
      Chassis.Velocity_Control(0, 0, 0);
      Barrier_Location = 1; //右左 01
    }
    //第二个障碍物在右侧（此时车在左侧）
    else
    {
      //直接前进到采矿区
      while (LP_Receive_x != 0xFF)
      {
        Chassis.Velocity_Control(0, 0.6, 0);
      }
      Chassis.Velocity_Control(0, 0, 0);
      Barrier_Location = 0; //右右 00
    }
  }
  //第一个障碍物在左侧（此时车在右侧）
  else
  {
    //前进避开障碍物
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0, 0.6, 0);
    }
    //第二次识别（此时车在右侧）
    Berry_Receive();
    //第二个障碍物在右侧（此时车在右侧）
    if (B_Receive == (uint8_t)0x00)
    {
      //向左前移动避开障碍物
      while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
      {
          Chassis.Velocity_Control(0.4, 0.6, 0);
      }
      //向前移动到采矿区
      while (LP_Receive_x != 0xFF)
      {
        Chassis.Velocity_Control(0, 0.6, 0);
      }
      Chassis.Velocity_Control(0, 0, 0);
      Barrier_Location = 2; //左右 10
    }
    //第二个障碍物在左侧（此时车在右侧）
    else
    {
      //向前避开障碍物
      while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
      {
        Chassis.Velocity_Control(0, 0.6, 0);
      }
      //向左前移动到采矿区
      while (LP_Receive_x != 0xFF)
      {
        Chassis.Velocity_Control(0.4, 0.6, 0);
      }
      Chassis.Velocity_Control(0, 0, 0);
      Barrier_Location = 3; //左左 11
    }
  }
  //关闭树莓派摄像头
  Berry_Close();
}

/**
 * @brief 从采矿区反向穿过障碍区
 *
 * @param 
 */
void Back_Cross_Barrier()
{
    //我不知道你拿完矿在哪个位置，假设它现在车头朝着障碍物并且冲出了采矿区的一堆巡线
  if (Barrier_Location == 0) //右右
  {
    //向车的右前移动到第二根障碍物线上
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(-0.4, 0.6, 0);
    }
    //向前移动到第一根障碍物线上
    Chassis.Velocity_Control(0, 0.6, 0);
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18);
    //向左前移动到返回启动区的巡线上
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0.4, 0.6, 0);
    }
    Chassis.Velocity_Control(0, 0, 0);
  }
  else if (Barrier_Location == 1) //右左
  {
    //向车的左前移动到第二根障碍物线上
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0.4, 0.6, 0);
    }
    //向右前移动到第一根障碍物线上
    Chassis.Velocity_Control(0, 0.6, 0);
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(-0.4, 0.6, 0);
    }
    //向左前移动到返回启动区的巡线上
    Chassis.Velocity_Control(0, 0.6, 0);
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0.4, 0.6, 0);
    }
    Chassis.Velocity_Control(0, 0, 0);
  }
  else if (Barrier_Location == 2) //左右
  {
    //向车的右前移动到第二根障碍物线上
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(-0.4, 0.6, 0);
    }
    //向左前移动到第一根障碍物线上
    Chassis.Velocity_Control(0, 0.6, 0);
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0.4, 0.6, 0);
    }
    //向前移动到返回启动区的巡线上
    Chassis.Velocity_Control(0, 0.6, 0);
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18);
    Chassis.Velocity_Control(0, 0, 0);
  }
  else if (Barrier_Location ==  3) //左左
  {
    //向车的左前移动到第二根障碍物线上
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18)
    {
        Chassis.Velocity_Control(0.4, 0.6, 0);
    }
    //向前移动到第一根障碍物线上
    Chassis.Velocity_Control(0, 0.6, 0);
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18);
    //向前移动到返回启动区的巡线上
    HAL_Delay(1000);
    while (LP_Receive_yl != (uint8_t)0x18 || LP_Receive_yr != (uint8_t)0x18);
    Chassis.Velocity_Control(0, 0, 0);
  }
}

/**
 * @brief 从避障区向左平移回启动区
 *
 * @param 
 */
void Barrier_to_Start()
{
  //前进
  while (LP_Receive_yl != (uint8_t)0xFF)
  {
	if (LP_Receive_yl < (uint8_t)0x60) //0110,0000
    {
		Chassis.Velocity_Control(0.6,0.2,0);
		HAL_Delay(200);
    }
    else if (LP_Receive_yl > (uint8_t)0x70)
    {
		Chassis.Velocity_Control(0.6,-0.2,0);
		HAL_Delay(200);
    }	
	else if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
	{
		Chassis.Velocity_Control(0.6,0,0.3);
		HAL_Delay(200);
	}
	else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
	{
		Chassis.Velocity_Control(0.6,0,-0.3);
		HAL_Delay(200);
	}
    else
    {
		Chassis.Velocity_Control(0.6,0,0);
		HAL_Delay(400);
    }
  }
  Chassis.Velocity_Control(0, 0, 0);
  HAL_Delay(2000);
}
