/* Includes ------------------------------------------------------------------*/

#include "arm.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 初始化机械臂相关舵机
 * 
 * @param Class_Steer __Arm_Steer[]
 * @param Class_Steer __Claw_Steer
 * @param Class_Steer __Box_Steer
 */
void Class_Arm::Init(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, Class_Steer __Box_Steer)
{
	Arm_Steer = __Arm_Steer;
	Claw_Steer = __Claw_Steer;
	Box_Steer = __Box_Steer;

	Arm_Steer[0].Init(htim5, TIM_CHANNEL_1);
    Arm_Steer[1].Init(htim8, TIM_CHANNEL_4);
    Arm_Steer[2].Init(htim8, TIM_CHANNEL_3);
    Arm_Steer[3].Init(htim8, TIM_CHANNEL_2);
    Claw_Steer.Init(htim8, TIM_CHANNEL_1);
	Box_Steer.Init(htim5, TIM_CHANNEL_2);
}

/**
 * @brief 设定机械臂及舵机的位置
 * 
 * @param 
 */

void Class_Arm::Arm_Claw_Steer_Control(float Arm_Angle_0, float Arm_Angle_1, float Arm_Angle_2, float Arm_Angle_3, uint16_t Claw_Stat)
{
    Arm_Steer[0].Set_Out(Arm_Angle_0, 270);
    Arm_Steer[0].Output();
    Arm_Steer[1].Set_Out(Arm_Angle_1, 180);
    Arm_Steer[1].Output();
    Arm_Steer[2].Set_Out(Arm_Angle_2, 270);
    Arm_Steer[2].Output();
    Arm_Steer[3].Set_Out(Arm_Angle_3, 270);
    Arm_Steer[3].Output();
	if(Claw_Stat == 0)
	{
		Claw_Steer.Set_Out(10.0f, 270);
		Claw_Steer.Output();
	}
	else if(Claw_Stat==1)
	{
		Claw_Steer.Set_Out(-20.0f, 270);
		Claw_Steer.Output();
	}
}


/**
 * @brief 设定舵机停在原处
 * 
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 */
void Class_Arm::Arm_Rest()
{
	Arm_Steer[0].Stop();
	Arm_Steer[1].Stop();
	Arm_Steer[2].Stop();
	Arm_Steer[3].Stop();
	Claw_Steer.Stop();
}

/**
 * @brief 设定木盒旋转
 *
 * @param __Box_Steer  木盒舵机
 */

void Class_Arm::Box_Steer_Rotate(float location)
{
    Box_Steer.Set_Out(location, 350);
    Box_Steer.Output();
}

void Class_Arm::Arm_Catch()
{
	uint16_t i;
	Arm_Claw_Steer_Control(-45.0f, 50.0f, 130.0f, 90.0f,0);
	HAL_Delay(1000);
	Arm_Claw_Steer_Control(-45.0f, 50.0f, 90.0f, 90.0f,0);
	HAL_Delay(1000);
 	Arm_Claw_Steer_Control(-40.0f, 70.0f, 80.0f, 90.0f,0);
 	HAL_Delay(500);
 	Arm_Claw_Steer_Control(-40.0f, 70.0f, 80.0f, 90.0f,1);
 	HAL_Delay(500);
 	Arm_Claw_Steer_Control(-40.0f, 45.0f, 90.0f, 90.0f,1);
 	HAL_Delay(500);
	Arm_Claw_Steer_Control(-20.0f, 45.0f, 130.0f, 90.0f,1);
	HAL_Delay(500);
	for(i=0;i<15;i++)
	{
		Arm_Claw_Steer_Control(-20.0f - i, 45.0f - 7.0f * i, 130.0f, 90.0f,1);
		HAL_Delay(100);
	}
	Arm_Claw_Steer_Control(-40.0f, -60.0f, 130.0f, 90.0f,1);
	HAL_Delay(500);
	for(i=0;i<15;i++)
	{
		Arm_Claw_Steer_Control(-40.0f, -60.0f, 130.0f - 10.0f * i, 90.0f,1);
		HAL_Delay(100);
	}
	Arm_Claw_Steer_Control(-40.0f, -60.0f, -20.0f, 90.0f,1);
	HAL_Delay(500);
	Arm_Claw_Steer_Control(-40.0f, -60.0f, -20.0f, 90.0f,0);
	HAL_Delay(500);
	for(i=0;i<15;i++)
	{
		Arm_Claw_Steer_Control(-40.0f, -60.0f, -20.0f + 10.0f * i, 90.0f,0);
		HAL_Delay(100);
	}
	
//	for(i=0;i<20;i++)
//	{
//		Arm_Claw_Steer_Control(30.0f, 50.0f-2.5f*i, 90.0f, 90.0f,1, __Arm_Steer, __Claw_Steer);
//		HAL_Delay(50);
//	}
//	Arm_Claw_Steer_Control(30.0f, 0.0f, 90.0f, 90.0f,1, __Arm_Steer, __Claw_Steer);
//	for(i=0;i<15;i++)
//	{
//		Arm_Claw_Steer_Control(30.0f - 5.0f*i, -4.0f*i, 90.0f-4.5f*i, 90.0f,1, __Arm_Steer, __Claw_Steer);
//		HAL_Delay(100);
//	}
// Arm_Claw_Steer_Control(-45.0f, -90.0f, -10.0f, 90.0f,1, __Arm_Steer, __Claw_Steer);
// HAL_Delay(500);
// Arm_Claw_Steer_Control(-45.0f, -90.0f, -10.0f, 90.0f,0, __Arm_Steer, __Claw_Steer);
// HAL_Delay(500);
// Arm_Claw_Steer_Control(-30.0f, -70.0f, 80.0f, 90.0f,0, __Arm_Steer, __Claw_Steer);
// HAL_Delay(1000);
// Arm_Claw_Steer_Control(-30.0f, -70.0f, 80.0f, 90.0f,1, __Arm_Steer, __Claw_Steer);
}

void Class_Arm::Arm_Catch_Back()
{
	Arm_Claw_Steer_Control(-40.0f, -60.0f, 130.0f, 90.0f,0);
	HAL_Delay(1000);
	Arm_Claw_Steer_Control(-45.0f, 30.0f, 130.0f, 90.0f,0);
	HAL_Delay(1000);
}


/**
 * @brief 完成一次抓取
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 */
// void Arm_Parallel_Catch(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer)
// {
// 	uint16_t i;
// 	Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 90.0f, 0, __Arm_Steer, __Claw_Steer);//初始位置
// 	HAL_Delay(500);
// 	Arm_Claw_Steer_Control(-30.0f, 65.0f, -75.0f, 90.0f, 0, __Arm_Steer, __Claw_Steer);//降下
// 	HAL_Delay(500);
// 	Arm_Claw_Steer_Control(-30.0f, 65.0f, -75.0f, 90.0f, 1, __Arm_Steer, __Claw_Steer);//抓取
// 	HAL_Delay(500);
// 	Arm_Claw_Steer_Control(-10.0f, 75.0f, -90.0f, 90.0f, 1, __Arm_Steer, __Claw_Steer);//第一段上升
// 	HAL_Delay(200);
// 	Arm_Claw_Steer_Control(10.0f, 75.0f, -90.0f, 90.0f, 1, __Arm_Steer, __Claw_Steer);//第一段上升
// 	HAL_Delay(300);
// 	Arm_Claw_Steer_Control(10.0f, 70.0f, -90.0f, 90.0f, 1, __Arm_Steer, __Claw_Steer);//转向
// 	HAL_Delay(500);
// 	for( i = 80; i > 0; --i)
// 	{
// 		Arm_Claw_Steer_Control((float)-30.0f+0.5*i, -90.0f + 2*i, (float) -i, (float) 1.125*i, 1, __Arm_Steer, __Claw_Steer);
// 		HAL_Delay(30);
// 	}
// 	Arm_Claw_Steer_Control(-30.0f, -90.0f, 10.0f, 0.0f, 1, __Arm_Steer, __Claw_Steer);
// 	Arm_Claw_Steer_Control(-30.0f, -90.0f, 0.0f, 0.0f, 0, __Arm_Steer, __Claw_Steer);//放矿
// 	HAL_Delay(500);
// 	Arm_Claw_Steer_Control(-20.0f, -20.0f, 0.0f, 0.0f, 0, __Arm_Steer, __Claw_Steer);//防卡死中间形态
// 	HAL_Delay(500);
// 	Arm_Claw_Steer_Control(-15.0f, -120.0f, -90.0f, 0.0f, 1, __Arm_Steer, __Claw_Steer);//待机形态
// }

// void Arm_Parallel_Catch_Back(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer)
// {
// 	Arm_Claw_Steer_Control(-15.0f, -120.0f, -90.0f, 0.0f, 1, __Arm_Steer, __Claw_Steer);
// 	HAL_Delay(500);
// 	Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 0.0f, 1, __Arm_Steer, __Claw_Steer);
// 	HAL_Delay(200);
// 	Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 0.0f, 0, __Arm_Steer, __Claw_Steer);
// 	HAL_Delay(800);
// 	Arm_Claw_Steer_Control(-20.0f, 55.0f, -90.0f, 90.0f, 0, __Arm_Steer, __Claw_Steer);
// }




