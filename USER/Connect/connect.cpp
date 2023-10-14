/* Includes ------------------------------------------------------------------*/

#include "connect.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

uint8_t Send_to_LinePatrol = 0x57;
extern uint8_t LP_Receive_yl;
extern uint8_t LP_Receive_yr;
extern uint8_t LP_Receive_x;;

uint8_t Send_Barrier = 0x01;
uint8_t Send_Orange = 0x02;
uint8_t Send_Exsit = 0x03;
uint8_t Send_Close = 0x00;
extern uint8_t B_Receive;

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart8;

extern TIM_HandleTypeDef htim10;

  SpeedTypeDef v_front=
  {
    0, 0.4, 0
  };
  
  SpeedTypeDef v_back=
  {
    0, -0.4, 0
  };

  SpeedTypeDef v_right=
  {
    -0.6, 0, 0
  };  
  
  SpeedTypeDef v_left=
  {
    0.6, 0, 0
  }; 
  
  SpeedTypeDef v_rotate=
  {
    0, 0, 1
  };

  SpeedTypeDef v_crotate=
  {
    0, 0, -1
  };

  SpeedTypeDef v_stop=
  {
    0, 0, 0
  };
	
	SpeedTypeDef v_rotate_left=
  {
    0.6, 0, -0.3
  };

  SpeedTypeDef v_crotate_left=
  {
    0.6, 0, 0.3
  };
	
	SpeedTypeDef v_front_left=
	{
		0.6,0.2,0
	};
	
	SpeedTypeDef v_back_left=
	{
		
		0.6,-0.2,0
	};

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 定时器中断回调函数
 *
 * @param TIM_HandleTypeDef *htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &UART_TRANSMIT_TIM)
  {
    HAL_UART_Transmit_IT(&LP_YL_HUART, &Send_to_LinePatrol, 1);
    HAL_UART_Transmit_IT(&LP_YR_HUART, &Send_to_LinePatrol, 1);
    HAL_UART_Transmit_IT(&LP_X_HUART, &Send_to_LinePatrol, 1);
  }
}

/**
 * @brief 巡线模块信息接收
 *
 * @param uint8_t __LP_Receive
 * @param UART_HandleTypeDef *__huart
 */
void LinePatrol_Receive(UART_HandleTypeDef *__huart)
{
	if (__huart == &LP_YL_HUART)
	{
		HAL_UART_Receive_IT(__huart, &LP_Receive_yl, 1);
	}
	else if (__huart == &LP_YR_HUART)
	{
		HAL_UART_Receive_IT(__huart, &LP_Receive_yr, 1);
	}
	else if (__huart == &LP_X_HUART)
	{
		HAL_UART_Receive_IT(__huart, &LP_Receive_x, 1);
	}
}

/**
 * @brief 串口接收中断回调函数
 *
 * @param UART_HandleTypeDef *__huart
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &LP_YL_HUART || huart == &LP_YR_HUART || huart == &LP_X_HUART)
	{
		LinePatrol_Receive(huart);
	}
}

/**
 * @brief 从树莓派接收信息
 *
 * @param 
 */
void Berry_Receive()
{
  HAL_UART_Receive_IT(&B_HUART, &B_Receive, 1);
}

/**
 * @brief 向树莓派发送信息使其开启障碍物识别
 *
 * @param UART_HandleTypeDef *__B_huart
 */
void Berry_Barrier_Open()
{
  HAL_UART_Transmit_IT(&B_HUART, &Send_Barrier, 1);
}

/**
 * @brief 向树莓派发送信息使其开启扫描橙色
 *
 * @param
 */
void Berry_Orange_Open()
{
  HAL_UART_Transmit_IT(&B_HUART, &Send_Orange, 1);
}

/**
 * @brief 向树莓派发送信息使其开启识别前方是否有矿
 *
 * @param
 */
void Berry_Exsit_Open()
{
  HAL_UART_Transmit_IT(&B_HUART, &Send_Exsit, 1);
}

/**
 * @brief 向树莓派发送信息使其关闭摄像头
 *
 * @param
 */
void Berry_Close()
{
  HAL_UART_Transmit_IT(&B_HUART, &Send_Close, 1);
}

/**
 * @brief 微秒级延时
 *
 * @param us 微秒数
 */
void HAL_Delay_us(uint32_t us)
{       
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000);
    HAL_Delay(us-1);
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
}

/**
 * @brief HC_SR04测量距离
 *
 * @param
 */

uint32_t HCSR04_Run()
{
	uint32_t i = 0;
	uint32_t uc=1;
  //屏蔽所有中断
  // __set_PRIMASK(1);
	HAL_GPIO_WritePin(HCSR04_Trig_GPIO_Port, HCSR04_Trig_GPIO_PIN, GPIO_PIN_SET);
	HAL_Delay_us(20);
	HAL_GPIO_WritePin(HCSR04_Trig_GPIO_Port, HCSR04_Trig_GPIO_PIN, GPIO_PIN_RESET);
	while(HAL_GPIO_ReadPin(HCSR04_Echo_GPIO_Port, HCSR04_Echo_GPIO_PIN) == GPIO_PIN_RESET)
	{
		uc++;
		if(uc>8000000)
		{
			return 9999;
			// break;
		}
	}
	while(HAL_GPIO_ReadPin(HCSR04_Echo_GPIO_Port, HCSR04_Echo_GPIO_PIN) != GPIO_PIN_RESET)
	{
		i++;
	}
  //取消中断屏蔽
  // __set_PRIMASK(0);
	return (uint32_t)i/35;
}
	

/**
 * @brief 采集左侧晶体矿
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 * @param UART_HandleTypeDef *__B_huart
 * @param uint8_t *__B_Receive
 * @param UART_HandleTypeDef *__LP_yl_huart
 * @param uint8_t *__LP_yl_Receive
 */
// void LinePatrol_Catch_LOrange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive)
// {
//   Berry_Orange_Open(__B_huart);
//   Berry_Receive(__B_huart, __B_Receive);
//   //识别到橙色之前一直前进
//   while (*__B_Receive != 0x01)
//   {
//     Chassis.Set_Velocity(v_front);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//     Berry_Receive(__B_huart, __B_Receive);
//   }
//   //识别到橙色后向前移动到前一根线处
//   LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
//   while ((*__LP_yl_Receive & 0x70) != 0x70)//0111,0000
//   {
//     Chassis.Set_Velocity(v_front);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//     LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
//   }
//   Chassis.Set_Velocity(v_stop);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   //进行一次抓取
//   Arm_Catch(__Arm_Steer, __Claw_Steer);
//   //判断是否抓取成功，若不成功再次进行抓取
//   while (1)
//   {
//     Berry_Exsit_Open(__B_huart);
//     Berry_Receive(__B_huart, __B_Receive);
//     //识别到有矿，抓取不成功
//     if (*__B_Receive == 0x02)
//     {
//       Chassis.Set_Velocity(v_left);
//       Chassis.Calculate_TIM_PeriodElapsedCallback();
//       HAL_Delay(100);
//       Chassis.Set_Velocity(v_stop);
//       Chassis.Calculate_TIM_PeriodElapsedCallback();
//       Arm_Catch(__Arm_Steer, __Claw_Steer);
//     }
//     //抓取成功
//     else
//     {
//       break;
//     }
//   }
// }

/**
 * @brief 采集燃料矿
 *
 * @param __Arm_Steer 机械臂舵机
 * @param __Claw_Steer 机械爪舵机
 * @param UART_HandleTypeDef *__B_huart
 * @param uint8_t *__B_Receive
 * @param UART_HandleTypeDef *__LP_yl_huart
 * @param uint8_t *__LP_yl_Receive
 * @param UART_HandleTypeDef *__LP_yr_huart
 * @param uint8_t *__LP_yr_Receive
 */
// void LinePatrol_Catch_Purple(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive, UART_HandleTypeDef *__LP_yr_huart, uint8_t *__LP_yr_Receive)
// {
//   //向前移动
//   LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
//   while ((*__LP_yl_Receive & (uint8_t)0xFE) != (uint8_t)0x00)//1111,1110
//   {
//     Chassis.Set_Velocity(v_front);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//     LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
//   }
//   //顺时针旋转
//   Chassis.Set_Velocity(v_rotate);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   HAL_Delay(200);
//   //向前移动到中线
//   LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
//   LinePatrol_Receive(__LP_yr_huart, __LP_yr_Receive);
//   while (((*__LP_yl_Receive & 0x70) != (uint8_t)0x70) || ((*__LP_yr_Receive & (uint8_t)0x70) != (uint8_t)0x70))//0111,0000
//   {
//     Chassis.Set_Velocity(v_front);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//   }
//   //停下，开始识别
//   Chassis.Set_Velocity(v_stop);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   Berry_Exsit_Open(__B_huart);
//   Berry_Receive(__B_huart, __B_Receive);
//   //识别到燃料矿进行抓取
//   if (*__B_Receive == 0x02)
//   {
//     Arm_Catch(__Arm_Steer, __Claw_Steer);
//     //判断是否抓取成功
//     while (1)
//     {
//       Berry_Exsit_Open(__B_huart);
//       Berry_Receive(__B_huart, __B_Receive);
//       //识别到有矿，抓取不成功
//       if (*__B_Receive == 0x02)
//       {
//         Chassis.Set_Velocity(v_left);
//         Chassis.Calculate_TIM_PeriodElapsedCallback();
//         HAL_Delay(100);
//         Chassis.Set_Velocity(v_stop);
//         Chassis.Calculate_TIM_PeriodElapsedCallback();
//         Arm_Catch(__Arm_Steer, __Claw_Steer);
//       }
//       //抓取成功
//       else
//       {
//         break;
//       }
//     }
//   }
//   //未识别到燃料矿，向前移动再抓取
//   else
//   {
//     Chassis.Set_Velocity(v_front);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//     HAL_Delay(150);
//     Chassis.Set_Velocity(v_stop);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//     Arm_Catch(__Arm_Steer, __Claw_Steer);
//     //判断是否抓取成功
//     while (1)
//     {
//       Berry_Exsit_Open(__B_huart);
//       Berry_Receive(__B_huart, __B_Receive);
//       //识别到燃料矿，抓取不成功
//       if (*__B_Receive == 0x02)
//       {
//         Chassis.Set_Velocity(v_left);
//         Chassis.Calculate_TIM_PeriodElapsedCallback();
//         HAL_Delay(100);
//         Chassis.Set_Velocity(v_stop);
//         Chassis.Calculate_TIM_PeriodElapsedCallback();
//         Arm_Catch(__Arm_Steer, __Claw_Steer);
//       }
//       //抓取成功
//       else
//       {
//         break;
//       }
//     }
//     //退回中线
//     Chassis.Set_Velocity(v_back);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//     HAL_Delay(150);
//     Chassis.Set_Velocity(v_stop);
//     Chassis.Calculate_TIM_PeriodElapsedCallback();
//   }
// }



/**
 * @brief 在启动区调整位置并放矿
 *
 * @param Class_Steer __Box_Steer
 * @param UART_HandleTypeDef *__LP_yl_huart
 * @param uint8_t *__LP_yl_Receive
 * @param UART_HandleTypeDef *__LP_yr_huart
 * @param uint8_t *__LP_yr_Receive 
 */
// void LinePatrol_Ad_Drop(Class_Steer __Box_Steer, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive, UART_HandleTypeDef *__LP_yr_huart, uint8_t *__LP_yr_Receive)
// {
//   LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
//   LinePatrol_Receive(__LP_yr_huart, __LP_yr_Receive);
//   LinePatrol_Adjust(__LP_yl_Receive, __LP_yr_Receive, __LP_yl_huart, __LP_yr_huart);
//   //向前移动到燃料框
//   Chassis.Set_Velocity(v_front);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   HAL_Delay(200);
//   Chassis.Set_Velocity(v_right);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   HAL_Delay(70);
//   //停下，放燃料矿
//   Chassis.Set_Velocity(v_stop);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   Box_Steer_Rotate(__Box_Steer, -90.0f);
//   HAL_Delay(100);
//   //向后移动到货框
//   Chassis.Set_Velocity(v_back);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   HAL_Delay(100);
//   //停下，放晶体矿
//   Chassis.Set_Velocity(v_stop);
//   Chassis.Calculate_TIM_PeriodElapsedCallback();
//   Box_Steer_Rotate(__Box_Steer, -180.0f);
//   HAL_Delay(100);
//   Box_Steer_Rotate(__Box_Steer, 200.0f);
//   HAL_Delay(100);
// }

/* Function prototypes -------------------------------------------------------*/
