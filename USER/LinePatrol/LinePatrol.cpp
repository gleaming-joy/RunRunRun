/* Includes ------------------------------------------------------------------*/

#include "LinePatrol.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

  extern UART_HandleTypeDef huart6;

  SpeedTypeDef v_front=
  {
    0, 0.6, 0
  };
  
  SpeedTypeDef v_back=
  {
    0, -0.6, 0
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
    0, 0, -1
  };

  SpeedTypeDef v_crotate=
  {
    0, 0, 1
  };

  SpeedTypeDef v_stop=
  {
    0, 0, 0
  };

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 巡线模块信息接收
 *
 * @param uint8_t __LP_Receive
 * @param UART_HandleTypeDef *__huart
 */
void LinePatrol_Receive(UART_HandleTypeDef *__huart, uint8_t *__LP_Receive)
{
  HAL_UART_Receive(__huart, __LP_Receive, 1, HAL_MAX_DELAY);
}

/**
 * @brief 调整偏移
 *
 * @param uint8_t *__LP_Receive_yl
 * @param uint8_t *__LP_Receive_yr
 * @param UART_HandleTypeDef *__huart_yl
 * @param UART_HandleTypeDef *__huart_yr
 */
void LinePatrol_Adjust(uint8_t *__LP_Receive_yl, uint8_t *__LP_Receive_yr, UART_HandleTypeDef *__huart_yl, UART_HandleTypeDef *__huart_yr)
{
  while (*__LP_Receive_yl != *__LP_Receive_yr)
  {
    //需要顺时针旋转
    if (*__LP_Receive_yl > *__LP_Receive_yr)
    {
      Chassis.Set_Velocity(v_rotate);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
      LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
    }
    //需要逆时针旋转
    else
    {
      Chassis.Set_Velocity(v_crotate);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
      LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
    }
  }
}  
  

/**
 * @brief 从启动区平移到采矿区
 *
 * @param uint8_t *__LP_Receive_yl
 * @param uint8_t *__LP_Receive_yr
 * @param UART_HandleTypeDef *__huart_yl
 * @param UART_HandleTypeDef *__huart_yr
 */

void LinePatrol_Start_Low(uint8_t *__LP_Receive_yl, uint8_t *__LP_Receive_yr, UART_HandleTypeDef *__huart_yl, UART_HandleTypeDef *__huart_yr)
{
  LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
  LinePatrol_Receive(__huart_yr, __LP_Receive_yr);

  while (1)
  {
    //左右巡线检测结果不一致，调整车的偏转
    if (*__LP_Receive_yl != *__LP_Receive_yr && *__LP_Receive_yl != (uint8_t)0x00)
    {
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      LinePatrol_Adjust(__LP_Receive_yl, __LP_Receive_yr, __huart_yl, __huart_yr);
      //调整后车偏后
      if ((*__LP_Receive_yl & (uint8_t)0x18) == (uint8_t)0x10)
      {
        while ((*__LP_Receive_yl & (uint8_t)0x18) != (uint8_t)0x18)
        {
          Chassis.Set_Velocity(v_front);
          Chassis.Calculate_TIM_PeriodElapsedCallback();
          LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
          LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
        }
      }
      //调整后车偏前
      else if ((*__LP_Receive_yl & (uint8_t)0x18) == (uint8_t)0x08)
      {
        Chassis.Set_Velocity(v_back);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
        LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
      }
    }
    else
    {
      //左侧巡线识别到黑线，持续向左平移
      if ((*__LP_Receive_yl & (uint8_t)0x18) == (uint8_t)0x18)
      {
        Chassis.Set_Velocity(v_left);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
        LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
      }
      //左侧巡线识别到空白，停止运动
      else if (*__LP_Receive_yl == (uint8_t)0x00)
      {
        Chassis.Set_Velocity(v_stop);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        break;
      }
    }
  }
}

/**
 * @brief 从树莓派接收信息
 *
 * @param UART_HandleTypeDef *__huart
 * @param uint8_t *__B_Receive
 */

void Berry_Receive(UART_HandleTypeDef *__huart, uint8_t *__B_Receive)
{
  HAL_UART_Receive(__huart, __B_Receive, 1, HAL_MAX_DELAY);
}

/**
 * @brief 障碍识别及位置调整
 *
 * @param UART_HandleTypeDef *__B_huart
 * @param uint8_t *__B_Receive
 * @param UART_HandleTypeDef *__LP_x_huart
 * @param uint8_t *__LP_x_Receive
 * @param uint8_t *__Barrier_Location
 */
void LinePatrol_Barrier(UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_x_huart, uint8_t *__LP_x_Receive, uint8_t *__Barrier_Location)
{
  //移动到左侧
  Chassis.Set_Velocity(v_left);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(200);

  //第一次识别
  Berry_Receive(__B_huart, __B_Receive);
  //第一次左侧有障碍物
  if (*__B_Receive == (uint8_t)0x00)
  {
    //向右移动避开障碍物前进
    Chassis.Set_Velocity(v_right);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(400);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(300);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();

    //第二次识别
    Berry_Receive(__B_huart, __B_Receive);
    //第二次右侧有障碍物
    if (*__B_Receive == (uint8_t)0x00)
    {
      //向左移动避开障碍物前进
      Chassis.Set_Velocity(v_left);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(400);
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      //向前移动到采矿区
      LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      while (*__LP_x_Receive != 0xFF)
      {
        Chassis.Set_Velocity(v_front);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      }
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      *__Barrier_Location = 1;
    }
    //第二次左侧有障碍物
    else
    {
      //直接前进
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      //向前再向左移动到采矿区
      LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      while (*__LP_x_Receive != 0xFF)
      {
        Chassis.Set_Velocity(v_front);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      }
      Chassis.Set_Velocity(v_left);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(250);
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      *__Barrier_Location = 0;
    }
  }
  //第一次右侧有障碍物
  else
  {
    //直接前进
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(300);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    
    //第二次识别
    Berry_Receive(__B_huart, __B_Receive);
    //第二次左侧有障碍物
    if (*__B_Receive == (uint8_t)0x00)
    {
      //向右移动避开障碍物前进
      Chassis.Set_Velocity(v_right);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(400);
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      //向前再向左移动到采矿区
      LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      while (*__LP_x_Receive != 0xFF)
      {
        Chassis.Set_Velocity(v_front);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      }
      Chassis.Set_Velocity(v_left);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(250);
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      *__Barrier_Location = 2;
    }
    //第二次右侧有障碍物
    else
    {
      //直接前进
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      //向前移动到采矿区
      LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      while (*__LP_x_Receive != 0xFF)
      {
        Chassis.Set_Velocity(v_front);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__LP_x_huart, __LP_x_Receive);
      }
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      *__Barrier_Location = 3;
    }
  }
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
void LinePatrol_Catch_LOrange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive)
{
  Berry_Receive(__B_huart, __B_Receive);
  //识别到橙色之前一直前进
  while (*__B_Receive != 0x01)
  {
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    Berry_Receive(__B_huart, __B_Receive);
  }
  //识别到橙色后向前移动到前一根线处
  LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
  while ((*__LP_yl_Receive & 0x70) != 0x70)//0111,0000
  {
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
  }
  Chassis.Set_Velocity(v_stop);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  //进行一次抓取
  Arm_Catch(__Arm_Steer, __Claw_Steer);
  //判断是否抓取成功，若不成功再次进行抓取
  while (1)
  {
    Berry_Receive(__B_huart, __B_Receive);
    //识别到橙色矿，抓取不成功
    if (*__B_Receive == 0x01)
    {
      Chassis.Set_Velocity(v_left);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(100);
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      Arm_Catch(__Arm_Steer, __Claw_Steer);
    }
    //抓取成功
    else
    {
      break;
    }
  }
}

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
void LinePatrol_Catch_Purple(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive, UART_HandleTypeDef *__LP_yr_huart, uint8_t *__LP_yr_Receive)
{
  //向前移动
  LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
  while ((*__LP_yl_Receive & (uint8_t)0xFE) != (uint8_t)0x00)//1111,1110
  {
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
  }
  //顺时针旋转
  Chassis.Set_Velocity(v_rotate);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(200);
  //向前移动到中线
  LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
  LinePatrol_Receive(__LP_yr_huart, __LP_yr_Receive);
  while (((*__LP_yl_Receive & 0x70) != (uint8_t)0x70) || ((*__LP_yr_Receive & (uint8_t)0x70) != (uint8_t)0x70))//0111,0000
  {
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
  }
  //停下，开始识别
  Chassis.Set_Velocity(v_stop);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  Berry_Receive(__B_huart, __B_Receive);
  //识别到燃料矿进行抓取
  if (*__B_Receive == 0x02)
  {
    Arm_Catch(__Arm_Steer, __Claw_Steer);
    //判断是否抓取成功
    while (1)
    {
      Berry_Receive(__B_huart, __B_Receive);
      //识别到燃料矿，抓取不成功
      if (*__B_Receive == 0x02)
      {
        Chassis.Set_Velocity(v_left);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        HAL_Delay(100);
        Chassis.Set_Velocity(v_stop);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        Arm_Catch(__Arm_Steer, __Claw_Steer);
      }
      //抓取成功
      else
      {
        break;
      }
    }
  }
  //未识别到燃料矿，向前移动再抓取
  else
  {
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(150);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    Arm_Catch(__Arm_Steer, __Claw_Steer);
    //判断是否抓取成功
    while (1)
    {
      Berry_Receive(__B_huart, __B_Receive);
      //识别到燃料矿，抓取不成功
      if (*__B_Receive == 0x02)
      {
        Chassis.Set_Velocity(v_left);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        HAL_Delay(100);
        Chassis.Set_Velocity(v_stop);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        Arm_Catch(__Arm_Steer, __Claw_Steer);
      }
      //抓取成功
      else
      {
        break;
      }
    }
    //退回中线
    Chassis.Set_Velocity(v_back);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(150);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
  }
}

/**
 * @brief 从采矿区返回启动区
 *
 * @param uint8_t *__Barrier_Location
 */
void LinePatrol_Back_Low(uint8_t *__Barrier_Location)
{
  Chassis.Set_Velocity(v_rotate);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(200);
  Chassis.Set_Velocity(v_front);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(400);
  if (*__Barrier_Location == 0)
  {
    Chassis.Set_Velocity(v_left);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(150);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(1000);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
  }
  else if (*__Barrier_Location == 1)
  {
    Chassis.Set_Velocity(v_right);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(150);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(500);
    Chassis.Set_Velocity(v_left);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(200);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(500);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
  }
  else if (*__Barrier_Location == 2)
  {
    Chassis.Set_Velocity(v_left);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(150);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(500);
    Chassis.Set_Velocity(v_right);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(200);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(500);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
  }
  else if (*__Barrier_Location ==  3)
  {
    Chassis.Set_Velocity(v_right);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(150);
    Chassis.Set_Velocity(v_front);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
    HAL_Delay(1000);
    Chassis.Set_Velocity(v_stop);
    Chassis.Calculate_TIM_PeriodElapsedCallback();
  }
  Chassis.Set_Velocity(v_crotate);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(150);
  Chassis.Set_Velocity(v_front);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(400);
  Chassis.Set_Velocity(v_stop);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
}

/**
 * @brief 在启动区调整位置并放矿
 *
 * @param Class_Steer __Box_Steer
 * @param UART_HandleTypeDef *__LP_yl_huart
 * @param uint8_t *__LP_yl_Receive
 * @param UART_HandleTypeDef *__LP_yr_huart
 * @param uint8_t *__LP_yr_Receive 
 */
void LinePatrol_Ad_Drop(Class_Steer __Box_Steer, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive, UART_HandleTypeDef *__LP_yr_huart, uint8_t *__LP_yr_Receive)
{
  LinePatrol_Receive(__LP_yl_huart, __LP_yl_Receive);
  LinePatrol_Receive(__LP_yr_huart, __LP_yr_Receive);
  LinePatrol_Adjust(__LP_yl_Receive, __LP_yr_Receive, __LP_yl_huart, __LP_yr_huart);
  //向前移动到燃料框
  Chassis.Set_Velocity(v_front);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(200);
  Chassis.Set_Velocity(v_right);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(70);
  //停下，放燃料矿
  Chassis.Set_Velocity(v_stop);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  Box_Steer_Rotate(__Box_Steer, -90.0f);
  HAL_Delay(100);
  //向后移动到货框
  Chassis.Set_Velocity(v_back);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(100);
  //停下，放晶体矿
  Chassis.Set_Velocity(v_stop);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  Box_Steer_Rotate(__Box_Steer, -180.0f);
  HAL_Delay(100);
  Box_Steer_Rotate(__Box_Steer, 200.0f);
  HAL_Delay(100);
}

// /**
//  * @brief 巡线模块判断
//  *
//  * @param uint8_t __LP_Detect_Bool[]
//  */
// void LinePatrol_Judge(uint8_t __LP_Detect_Bool[])
// {
//   __LP_Detect_Bool[0] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3);
//   __LP_Detect_Bool[1] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
//   __LP_Detect_Bool[2] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4);
//   __LP_Detect_Bool[3] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
// }

// /**
//  * @brief 巡线模块决定前进方向
//  *
//  * @param uint8_t __LP_Detect_Bool[]
//  */
// void LinePatrol_Decide(uint8_t __LP_Detect_Bool[])
// {
//     //向前运动
//     if (__LP_Detect_Bool[0] == 0 && __LP_Detect_Bool[1] == 1 && __LP_Detect_Bool[2] == 1 && __LP_Detect_Bool[3] == 0)
//     {
//         Chassis.Set_Velocity(v_front);
//         Chassis.Calculate_TIM_PeriodElapsedCallback();
//     }
//     //左转弯
//     else if (__LP_Detect_Bool[0] == 0 && __LP_Detect_Bool[1] == 1 && __LP_Detect_Bool[2] == 1 && __LP_Detect_Bool[3] == 1)
//     {
//       Chassis.Set_Velocity(v_crotate);
//       Chassis.Calculate_TIM_PeriodElapsedCallback();
//       HAL_Delay(4000);
//       Chassis.Set_Velocity(v_right);
//       Chassis.Calculate_TIM_PeriodElapsedCallback();
//       HAL_Delay(1500);
//       // while (1)
//       // {
//       //   LinePatrol_Judge(__LP_Detect_Bool);
//       //   if(__LP_Detect_Bool[0] == 0 && __LP_Detect_Bool[1] == 1 && __LP_Detect_Bool[2] == 1 && __LP_Detect_Bool[3] == 0)
//       //     break;
//       // }
//       // HAL_Delay(30);
      
//     }
//     //右转弯
//     else if (__LP_Detect_Bool[0] == 1 && __LP_Detect_Bool[1] == 1 && __LP_Detect_Bool[2] == 1 && __LP_Detect_Bool[3] == 0)
//     {
//       Chassis.Set_Velocity(v_rotate);
//       Chassis.Calculate_TIM_PeriodElapsedCallback();
//       HAL_Delay(4000);
//       Chassis.Set_Velocity(v_left);
//       Chassis.Calculate_TIM_PeriodElapsedCallback();
// 			HAL_Delay(1500);
//     }
    // //车头向右转
    // else if (__LP_Detect_Bool[0] == 0 && __LP_Detect_Bool[1] == 0 && __LP_Detect_Bool[2] == 1 && __LP_Detect_Bool[3] == 0)
    // {
    //   Chassis.Set_Velocity(v_crotate);
    //   Chassis.Calculate_TIM_PeriodElapsedCallback();
    // }
    // //车头向左转
    // else if (__LP_Detect_Bool[0] == 0 && __LP_Detect_Bool[1] == 1 && __LP_Detect_Bool[2] == 0 && __LP_Detect_Bool[3] == 0)
    // {
    //   Chassis.Set_Velocity(v_rotate);
    //   Chassis.Calculate_TIM_PeriodElapsedCallback();
    // }
    // //停下
    // else if (__LP_Detect_Bool[0] == 0 && __LP_Detect_Bool[1] == 0 && __LP_Detect_Bool[2] == 0 && __LP_Detect_Bool[3] == 0)
    // {
    //   Chassis.Set_Velocity(v_stop);
    //   Chassis.Calculate_TIM_PeriodElapsedCallback();
    // }
//}

/* Function prototypes -------------------------------------------------------*/
