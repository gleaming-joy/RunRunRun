/* Includes ------------------------------------------------------------------*/

#include "run.hpp"

/* Private macros ------------------------------------------------------------*/

#define blue 0x04
#define orange 0x01
#define purple 0x02
#define empty 0x03 

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

extern uint8_t LP_Receive_yl;
extern uint8_t LP_Receive_yr;
extern uint8_t LP_Receive_x;
extern uint8_t B_Receive;

extern uint8_t Barrier_Location;

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 采集左侧晶体矿
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 */
 
void LinePatrol_Catch_LOrange()
{
	uint16_t counter = 0;
	uint8_t ocounter = 0;
	Chassis.Velocity_Control(0, 0, 0);
	Arm.Arm_Claw_Steer_Control(-45.0f, 50.0f, -100.0f, 90.0f,0);
	B_Receive = 0x00;
	HAL_Delay(2000);
	while(1)
	{		
		Chassis.Velocity_Control(0, 0.4, 0);
		while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
		Chassis.Velocity_Control(0, 0, 0);
        counter++;
		if(counter == 4)
        	break;
        Berry_Orange_Open();
        HAL_Delay(2000);
        Berry_Receive();
        if (B_Receive == blue)
        {
			Chassis.Velocity_Control(0, 0.4, 0);
			HAL_Delay(500);
        	continue;
        }
        else if(B_Receive == orange)
        {
			ocounter++;
        	Arm.Arm_Catch();
			HAL_Delay(1000);
			Arm.Arm_Catch_Back();
			if (ocounter == 1)
			{
				Arm.Box_Steer_Rotate(-90);
			}
			else if (ocounter == 2)
			{
				Arm.Box_Steer_Rotate(-180);
			}
        }
        Chassis.Velocity_Control(0, 0.4, 0);
		HAL_Delay(200);	
	}
    Chassis.Velocity_Control(0, 0, 0);
}

void LinePatrol_Catch_LOrange_NoVisual()
{
	Chassis.Velocity_Control(0, 0, 0);
	Arm.Arm_Claw_Steer_Control(-35.0f, 50.0f, 100.0f, 90.0f,0);
	HAL_Delay(2000);
	
	HAL_Delay(500);
	Arm.Arm_Catch();
	HAL_Delay(1000);
	//Arm.Arm_Catch_Back();
	Arm.Box_Steer_Rotate(-90);
	Chassis.Velocity_Control(0, 0.4, 0);
	HAL_Delay(200);
	while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
		
//	Chassis.Velocity_Control(0, 0, 0);
//	HAL_Delay(500);
//	Arm_Catch(__Arm_Steer, __Claw_Steer);
//	HAL_Delay(1000);
//	Arm_Catch_Back(__Arm_Steer, __Claw_Steer);
//	Box_Steer_Rotate(__Box_Steer, -180);
//	Chassis.Velocity_Control(0, 0.4, 0);
	HAL_Delay(200);
	while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
		
	Chassis.Velocity_Control(0, 0.4, 0);
	HAL_Delay(200);
	while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
	HAL_Delay(200);
	while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
	Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(1000);
}

/**
 * @brief 采集右侧晶体矿
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 */
 
void LinePatrol_Catch_ROrange()
{
	uint16_t counter = 0;
	Arm.Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 90.0f, 0);
	
	while(1)
	{
    	Chassis.Velocity_Control(0, 0.4, 0);
		if ((LP_Receive_yl & (uint8_t)0x7F) == (uint8_t)0x38)
		{
        	Chassis.Velocity_Control(0, 0, 0);
			//Arm.Arm_Catch();
			HAL_Delay(1000);
			//Arm.Arm_Catch_Back();
			counter++;
			if(counter == 5)
        		break;
        	Chassis.Velocity_Control(0, 0.4, 0);
			HAL_Delay(300);
		}
	}
    Chassis.Velocity_Control(0, 0, 0);
}

/**
 * @brief 采集燃料矿
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 */
 void LinePatrol_Catch_Purple()
 {
//	uint32_t count=0;
	B_Receive = 0x00;
	Arm.Arm_Claw_Steer_Control(-45.0f, 50.0f, 100.0f, 90.0f,0);
	 
	Chassis.Velocity_Control(-0.35, -0.1, -1);
	while(LP_Receive_yl != (uint8_t) 0xFF) {};
	Chassis.Velocity_Control(0,0,0);
	HAL_Delay(1000);
	Chassis.Velocity_Control(-0.3,0,0);
	while(LP_Receive_yr == (uint8_t) 0xFF) {};
	HAL_Delay(200);
	Chassis.Velocity_Control(0,0,0);
	HAL_Delay(1000);
	
	if((LP_Receive_yr & (uint8_t)0xDB) > (uint8_t)0x38)
	{
		Chassis.Velocity_Control(0,-0.3,0);
		while((LP_Receive_yr & (uint8_t)0xDB) != (uint8_t)0x38) {};
	}
	if((LP_Receive_yr & (uint8_t)0xDB) < (uint8_t)0x38)
	{
		Chassis.Velocity_Control(0,0.3,0);
		while((LP_Receive_yr & (uint8_t)0xDB) != (uint8_t)0x38) {};
	}
	Chassis.Velocity_Control(0,0,0);
	HAL_Delay(1000);
	
	Chassis.Velocity_Control(0.4,0,0);
	while((LP_Receive_yl & (uint8_t) 0x3C) == 0x3C) {};
	while((LP_Receive_yl & (uint8_t) 0x3C) != 0x3C) {};
	while((LP_Receive_yl & (uint8_t) 0x3C) == 0x3C) {};
	
//	Chassis.Velocity_Control(-0.3, -0.1, -1);	
//	HAL_Delay(2000);
//	Chassis.Velocity_Control(0.5,0.3,0);	
//	HAL_Delay(1200);
//	Chassis.Velocity_Control(-0.2, -0.1, -1);
//	while(LP_Receive_yl != LP_Receive_yr)
//	{
//		count++;
//		HAL_Delay(50);
//		if(count>20)
//			Chassis.Velocity_Control(0.2, 0.1, 1);
//	}
//    Chassis.Velocity_Control(0, 0, 0);
//	HAL_Delay(500);
//    Chassis.Velocity_Control(0.4, 0, 0);
//	while((LP_Receive_yl & (uint8_t) 0x3C) != 0x3C);
//	while((LP_Receive_yl & (uint8_t) 0x3C) == 0x3C);
	HAL_Delay(100);
  Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(500);
    Chassis.Velocity_Control(0, 0.4, 0);
	while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
    Chassis.Velocity_Control(0, 0, 0);
	Berry_Purple_Open();
	HAL_Delay(1000);
	Berry_Receive();
	if (B_Receive == purple)
	{
		Arm.Arm_Catch();
		HAL_Delay(1000);
		Arm.Arm_Catch_Back();
	}
	else if (B_Receive == empty)
	{
		Chassis.Velocity_Control(0, 0.4, 0);
		HAL_Delay(300);
		while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
		Chassis.Velocity_Control(0, 0, 0);
		Arm.Arm_Catch();
		HAL_Delay(1000);
		Arm.Arm_Catch_Back();
	}
	HAL_Delay(2000);
 }
 
 void LinePatrol_Catch_Purple_NoVision()
 {
//	uint32_t count=0;
//	Arm.Arm_Claw_Steer_Control(-20.0f, 50.0f, 100.0f, 90.0f,0);
//	Chassis.Velocity_Control(-0.3, 0, -1);
//	while(LP_Receive_yl != (uint8_t) 0xFF) {};
//	HAL_Delay(100);
//	Chassis.Velocity_Control(0.1, -0.1, -1);
//	while(LP_Receive_x != (uint8_t) 0xFF) {};
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(1000);
//	Chassis.Velocity_Control(-0.3,0,0);
//	while(LP_Receive_yr == (uint8_t) 0xFF) {};
//	HAL_Delay(200);
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(1000);
//	
//	if((LP_Receive_yr & (uint8_t)0xDB) > (uint8_t)0x38)
//	{
//		Chassis.Velocity_Control(0,-0.3,0);
//		while((LP_Receive_yr & (uint8_t)0xDB) != (uint8_t)0x38) {};
//	}
//	if((LP_Receive_yr & (uint8_t)0xDB) < (uint8_t)0x38)
//	{
//		Chassis.Velocity_Control(0,0.3,0);
//		while((LP_Receive_yr & (uint8_t)0xDB) != (uint8_t)0x38) {};
//	}
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(1000);
//	
//	Chassis.Velocity_Control(0.4,0,0);
//	while((LP_Receive_yl & (uint8_t) 0x3C) == 0x3C) {};
//	while((LP_Receive_yl & (uint8_t) 0x3C) != 0x3C) {};
//	while((LP_Receive_yl & (uint8_t) 0x3C) == 0x3C) {};
	
	Chassis.Velocity_Control(-0.3, 0.1, -1);	
	HAL_Delay(2100);
	Chassis.Velocity_Control(0.5,0.3,0);	
	HAL_Delay(1200);
	// while(LP_Receive_yl != LP_Receive_yr)
	// {
	// 	count++;
	// 	HAL_Delay(20);
	// 	if(count>50)
	// 		Chassis.Velocity_Control(0.2, 0.1, 1);
	// }
   Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(500);
   Chassis.Velocity_Control(-0.4, 0, 0);
	while((LP_Receive_yl & (uint8_t) 0x3C) != 0x3C);
	Chassis.Velocity_Control(0.4, 0, 0);
	HAL_Delay(300);
	
	//巡线向右平移
	// float x_adjust;
	// float y_adjust;
	// float omega_adjust;
	// while ((LP_Receive_x & (uint8_t)0x3C) != (uint8_t)0x3C)
	// {
	// 	// x_adjust=-0.6f;
	// 	// y_adjust=0;
	// 	// omega_adjust=0;
	// 	// if (LP_Receive_yl < (uint8_t)0x30 ) //0110,0000
	// 	// {
	// 	// 	y_adjust += 0.2f;
	// 	// 	if(LP_Receive_yr != (uint8_t)0xFF) omega_adjust -= 0.15f;
	// 	// }
	// 	// else if (LP_Receive_yl > (uint8_t)0x38)
	// 	// {
	// 	// 	y_adjust -= 0.2f;
	// 	// 	if(LP_Receive_yr != (uint8_t)0xFF) omega_adjust +=0.15f;
	// 	// }
	// 	// if (LP_Receive_yr < (uint8_t)0x30 && LP_Receive_yr != (uint8_t)0xFF) //0110,0000
	// 	// {
	// 	// 	y_adjust += 0.2f;
	// 	// 	omega_adjust +=0.15f;
	// 	// }
	// 	// else if (LP_Receive_yr > (uint8_t)0x38 && LP_Receive_yr != (uint8_t)0xFF)
	// 	// {
	// 	// 	y_adjust -= 0.2f;
	// 	// 	omega_adjust -=0.15f;
	// 	// }
	// 	// Chassis.Velocity_Control(x_adjust,y_adjust,omega_adjust);
	// 	// HAL_Delay(50);
	// 	Chassis.Velocity_Control(0.6,0,0);
	// }
	// HAL_Delay(500);
	// Chassis.Velocity_Control(0, 0, 0);
	// HAL_Delay(1000);
	// Catch_Position_Adjust();
	// //顺时针旋转
	// Chassis.Velocity_Control(0, 0, 0.6);
	// HAL_Delay(500);
	// while ((LP_Receive_x & (uint8_t)0x18) != (uint8_t)0x18); //0001,1000
	// Chassis.Velocity_Control(0, 0, 0);
	// HAL_Delay(2000);
    Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(500);
    Chassis.Velocity_Control(0, -0.4, 0);
	while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
    Chassis.Velocity_Control(0, 0, 0);
	HAL_Delay(100);
	Arm.Arm_Catch();
	HAL_Delay(1000);
	Arm.Arm_Catch_Back();
	Arm.Box_Steer_Rotate(-180);
	HAL_Delay(1000);
	Chassis.Velocity_Control(0, 0.4, 0);
	HAL_Delay(500);
	while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
    Chassis.Velocity_Control(0, 0, 0);
	Arm.Arm_Catch();
	HAL_Delay(1000);
	Arm.Arm_Catch_Back();
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
void Start_to_High()
{
    TestMotor1.Set_Motor_Running_Status(1,1);
    Chassis.Velocity_Control(0, 0.4, 0);
    RChassis.R_Velocity_Control(0.3f, 0.3f);
    HAL_Delay(3500);
    Chassis.Velocity_Control(0, 0, 0);
    RChassis.R_Velocity_Control(0.0f, 0.0f);
    HAL_Delay(10500);
        
    TestMotor1.Set_Motor_Running_Status(0,0);
	Chassis.Velocity_Control(0, 0.5, 0);
    RChassis.R_Velocity_Control(0.4f, 0.4f);
    HAL_Delay(1000);
    Chassis.Velocity_Control(0, 1.2, 0);
    RChassis.R_Velocity_Control(2.0f, 2.0f);
	HAL_Delay(1000);
	while((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t) 0x18) {};

    TestMotor1.Set_Motor_Running_Status(1,0);
    Chassis.Velocity_Control(0, 0, 0);
    RChassis.R_Velocity_Control(0.0f, 0.0f);
    HAL_Delay(14000);
	TestMotor1.Set_Motor_Running_Status(0,0);
	Barrier_to_Catch(1);
	HAL_Delay(500);
}

/**
 * @brief 从启动区向左平移到避障区
 *
 * @param 
 */
void Start_to_Barrier()
{
	float x_adjust;
	float y_adjust;
	float omega_adjust;
	while (LP_Receive_yl != (uint8_t)0x00)
	{
		x_adjust=0.6f;
		y_adjust=0;
		omega_adjust=0;
		if (LP_Receive_yl < (uint8_t)0x30) //0110,0000
		{
			y_adjust += 0.1f;
			omega_adjust -= 0.15f;
		}
		else if (LP_Receive_yl > (uint8_t)0x38)
		{
			y_adjust -= 0.1f;
			omega_adjust +=0.15f;
		}
		if (LP_Receive_yr < (uint8_t)0x30) //0110,0000
		{
			y_adjust += 0.1f;
			omega_adjust +=0.15f;
		}
		else if (LP_Receive_yr > (uint8_t)0x38)
		{
			y_adjust -= 0.1f;
			omega_adjust -=0.15f;
		}
//		if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
//		{
//			omega_adjust += 0.6f;
//		}
//		else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
//		{
//			omega_adjust -= 0.6f;
//		}
		Chassis.Velocity_Control(x_adjust,y_adjust,omega_adjust);
		HAL_Delay(50);
	}
	Chassis.Velocity_Control(0,0,0);
	HAL_Delay(1000);
}

/**
 * @brief 第二次避障后前进到采矿区
 *
 * @param uint8_t model  0：表示车在左侧， 1：表示车在右侧
 */
void Barrier_to_Catch(uint8_t model)
{
	uint32_t tim;
    //前进到采矿区
    
    if (model == 0)
    {
		Chassis.Velocity_Control(-0.2, 0.3, 0);
		HAL_Delay(500);
    	while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
		Chassis.Velocity_Control(0,0,0);
		HAL_Delay(500);
		Catch_Position_Adjust();
    	tim=0;
    	//向右平移到中间线
    	while (((LP_Receive_yr & (uint8_t) 0x06) != (uint8_t)0x06) && ((LP_Receive_yl & (uint8_t) 0x06) != (uint8_t)0x06))
    	{
			if (LP_Receive_yl < (uint8_t)0x60) //0110,0000
      		{
		    	Chassis.Velocity_Control(-0.6,0.2,0);
		    	HAL_Delay(50);
      		}
      		else if (LP_Receive_yl > (uint8_t)0x70)
      		{
		    	Chassis.Velocity_Control(-0.6,-0.2,0);
		    	HAL_Delay(50);
      		}	
	    	else if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
	    	{
		    	Chassis.Velocity_Control(-0.6,0,0.3);
				HAL_Delay(50);
	    	}
	    	else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
	    	{
		    	Chassis.Velocity_Control(-0.6,0,-0.3);
		    	HAL_Delay(50);
	    	}
      		else
      		{
		    	Chassis.Velocity_Control(-0.6,0,0);
		    	HAL_Delay(50);
      		}
    	}
			while (tim<115)
    	{
	    	if (LP_Receive_yl < (uint8_t)0x60) //0110,0000
      		{
		    	Chassis.Velocity_Control(0.6,0.2,0);
		    	HAL_Delay(50);
      		}
      		else if (LP_Receive_yl > (uint8_t)0x70)
      		{
		    	Chassis.Velocity_Control(0.6,-0.2,0);
		    	HAL_Delay(50);
      		}	
	    	else if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
	    	{
		    	Chassis.Velocity_Control(0.6,0,0.3);
		    	HAL_Delay(50);
	   		}
	    	else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
	    	{
		    	Chassis.Velocity_Control(0.6,0,-0.3);
		    	HAL_Delay(50);
	    	}
      		else
      		{
		    	Chassis.Velocity_Control(0.6,0,0);
		    	HAL_Delay(50);
      		}
					tim++;
					if((LP_Receive_yr & (uint8_t) 0x06) == (uint8_t)0x06) tim=100;
    	}
		Chassis.Velocity_Control(0, 0, 0);
		HAL_Delay(2000);
  	}
  	else if (model == 1)
  	{
		Chassis.Velocity_Control(0, 0.3, 0);
		HAL_Delay(500);
    	while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38);
		Chassis.Velocity_Control(0,0,0);
		HAL_Delay(500);
		Catch_Position_Adjust();
		tim=0;
    	//向左平移到中间线
    	while (tim<110)
    	{
	    	if (LP_Receive_yl < (uint8_t)0x60) //0110,0000
      		{
		    	Chassis.Velocity_Control(0.6,0.2,0);
		    	HAL_Delay(50);
      		}
      		else if (LP_Receive_yl > (uint8_t)0x70)
      		{
		    	Chassis.Velocity_Control(0.6,-0.2,0);
		    	HAL_Delay(50);
      		}	
	    	else if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
	    	{
		    	Chassis.Velocity_Control(0.6,0,0.3);
		    	HAL_Delay(50);
	   		}
	    	else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
	    	{
		    	Chassis.Velocity_Control(0.6,0,-0.3);
		    	HAL_Delay(50);
	    	}
      		else
      		{
		    	Chassis.Velocity_Control(0.6,0,0);
		    	HAL_Delay(50);
      		}
				tim++;
				if((LP_Receive_yr & (uint8_t) 0x06) == (uint8_t)0x06) tim=100;
    	}
		Chassis.Velocity_Control(0, 0, 0);
		HAL_Delay(2000);
  	}
	Catch_Position_Adjust();
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
  //第一次识别（此时车在右侧）
  //第一个障碍物在右侧（此时车在右侧）
  if (HC1.HCSR04_Run() < 600)
  {
		Chassis.Velocity_Control(0.5, 0.1, 0);
		HAL_Delay(500);
		while(HC1.HCSR04_Run() < 600)
	  {
		HAL_Delay(10);
	  }
		HAL_Delay(1500);
		Chassis.Velocity_Control(0, 0.5, 0);
    //向左前移动避开障碍物
    while ((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18 && (LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18) {}
		Barrier_Position_Adjust();
    Chassis.Velocity_Control(0, 0, 0);
		HAL_Delay(2000);
    //第二次识别（此时车在左侧）
    //第二个障碍物在左侧（此时车在左侧）
    if (HC1.HCSR04_Run() < 1500)
    {
      //向右前移动避开障碍物
	  Chassis.Velocity_Control(0, 0.3, 0);
	  while(HC1.HCSR04_Run() > 400)
	  {
		HAL_Delay(10);
	  }
	  Chassis.Velocity_Control(-0.7, 0.2, 0);
	  while(HC1.HCSR04_Run() < 800) 
	  {
		HAL_Delay(10);
	  }
	  HAL_Delay(1400);
	  Chassis.Velocity_Control(0, 0.3, 0);
      while ((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18 && (LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18) {}
	  Barrier_Position_Adjust();
      //移动到采矿区
      Barrier_to_Catch(1);
      Barrier_Location = 1; //右左 01
    }
    //第二个障碍物在右侧（此时车在左侧）
    else
    {
			Chassis.Velocity_Control(0, 0.6, 0);
			HAL_Delay(500);
			while ((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18 && (LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18) {}
			// Chassis.Velocity_Control(0.4, 0, 0);
			// HAL_Delay(1000);
			Barrier_Position_Adjust();
      
      Barrier_to_Catch(0);
      
      Barrier_Location = 0; //右右 00
    }
  }
  //第一个障碍物在左侧（此时车在右侧）
  else
  {
		Chassis.Velocity_Control(-0.5, 0.4, 0);
		HAL_Delay(900);
		Chassis.Velocity_Control(0, 0.6, 0);
		HAL_Delay(200);
    //前进避开障碍物
    while (((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18) && ((LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18)) {}
		Barrier_Position_Adjust();
    //第二次识别（此时车在右侧）
    //第二个障碍物在右侧（此时车在右侧）
    if (HC1.HCSR04_Run() < 1500)
    {
      //向左前移动避开障碍物
	  Chassis.Velocity_Control(0, 0.3, 0);
	  while(HC1.HCSR04_Run() > 450) 
	  {
		HAL_Delay(10);
	  }
	  Chassis.Velocity_Control(0.7, 0.2, 0);
	  while(HC1.HCSR04_Run() < 800) 
	  {
		HAL_Delay(10);
	  }
	  HAL_Delay(1000);
	  Chassis.Velocity_Control(0, 0.3, 0);
      while (((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18) && ((LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18)) {}
	  Barrier_Position_Adjust();
      //向前移动到采矿区
      Barrier_to_Catch(0);
      Barrier_Location = 2; //左右 10
    }
    //第二个障碍物在左侧（此时车在右侧）
    else
    {
			Chassis.Velocity_Control(0, 0.6, 0);
			HAL_Delay(500);
      //向前避开障碍物
      while (((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18) && ((LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18)){}
			Barrier_Position_Adjust();
      //向左前移动到采矿区
      Barrier_to_Catch(1);
      Barrier_Location = 3; //左左 11-
    }
  }
}

void Barrier_Position_Adjust()
{
	float x_adjust;
	float y_adjust;
	float omega_adjust;
	uint16_t num =0;
	while (((LP_Receive_yl & (uint8_t) 0xDB) != (uint8_t)0x18 || (LP_Receive_yr & (uint8_t) 0xDB) != (uint8_t)0x18) && num<40)
	{
		x_adjust=0;
		y_adjust=0;
		omega_adjust=0;
		if(LP_Receive_yr == (uint8_t) 0x00)
		{
			Chassis.Velocity_Control(0.5,0,0);
			while(LP_Receive_yr == (uint8_t) 0x00) {}
			HAL_Delay(50);
		}
		if(LP_Receive_yl == (uint8_t) 0x00)
		{
			Chassis.Velocity_Control(-0.5,0,0);
			while(LP_Receive_yl == (uint8_t) 0x00) {}
			HAL_Delay(50);
		}
		if ((LP_Receive_yl & (uint8_t) 0xDB) < (uint8_t)0x18) //0110,0000
		{
			y_adjust += 0.2f;
			omega_adjust -= 0.3f;
		}
		else if ((LP_Receive_yl & (uint8_t) 0xDB) > (uint8_t)0x18)
		{
			y_adjust -= 0.2f;
			omega_adjust +=0.3f;
		}
		if ((LP_Receive_yr & (uint8_t) 0xDB) < (uint8_t)0x18) //0110,0000
		{
			y_adjust += 0.2f;
			omega_adjust +=0.3f;
		}
		else if ((LP_Receive_yr & (uint8_t) 0xDB) > (uint8_t)0x18)
		{
			y_adjust -= 0.2f;
			omega_adjust -=0.3f;
		}
//		if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
//		{
//			omega_adjust += 0.6f;
//		}
//		else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
//		{
//			omega_adjust -= 0.6f;
//		}
		Chassis.Velocity_Control(x_adjust,y_adjust,omega_adjust);
		HAL_Delay(50);
		num++;
	}
	Chassis.Velocity_Control(0,0,0);
}

void Catch_Position_Adjust()
{
	float x_adjust;
	float y_adjust;
	float omega_adjust;
	uint16_t num =0;
	while (((LP_Receive_yl & (uint8_t)0x7A) != (uint8_t)0x38 || (LP_Receive_yr & (uint8_t)0x7A) != (uint8_t)0x38)&&num<40)
	{
		x_adjust=0;
		y_adjust=0;
		omega_adjust=0;
		if ((LP_Receive_yl & (uint8_t)0x7A) < (uint8_t)0x38)
		{
			y_adjust += 0.2f;
			omega_adjust -= 0.4f;
		}
		else if ((LP_Receive_yl & (uint8_t)0x7A) > (uint8_t)0x38)
		{
			y_adjust -= 0.2f;
			omega_adjust +=0.4f;
		}
		if ((LP_Receive_yr & (uint8_t)0x7A) < (uint8_t)0x38)
		{
			y_adjust += 0.2f;
			omega_adjust +=0.4f;
		}
		else if ((LP_Receive_yr & (uint8_t)0x7A) > (uint8_t)0x38)
		{
			y_adjust -= 0.2f;
			omega_adjust -=0.4f;
		}
//		if (LP_Receive_yl > LP_Receive_yr || LP_Receive_yl == (uint8_t)0x00)
//		{
//			omega_adjust += 0.6f;
//		}
//		else if (LP_Receive_yl < LP_Receive_yr || LP_Receive_yr == (uint8_t)0x00)
//		{
//			omega_adjust -= 0.6f;
//		}
		Chassis.Velocity_Control(x_adjust,y_adjust,omega_adjust);
		HAL_Delay(25);
		num++;
	}
	Chassis.Velocity_Control(0,0,0);
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
