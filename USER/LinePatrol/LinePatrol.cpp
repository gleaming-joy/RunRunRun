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

void LinePatrol_Start(uint8_t *__LP_Receive_yl, uint8_t *__LP_Receive_yr, UART_HandleTypeDef *__huart_yl, UART_HandleTypeDef *__huart_yr)
{
  LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
  LinePatrol_Receive(__huart_yr, __LP_Receive_yr);

  while (1)
  {
    //左右巡线检测结果不一致，调整车的偏转
    if (*__LP_Receive_yl != *__LP_Receive_yr && *__LP_Receive_yl != (uint8_t)0b00000000)
    {
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      LinePatrol_Adjust(__LP_Receive_yl, __LP_Receive_yr);
      //调整后车偏后
      if ((*__LP_Receive_yl & (uint8_t)0b00011000) == (uint8_t)0b00010000)
      {
        while ((*__LP_Receive_yl & (uint8_t)0b00011000) != (uint8_t)0b00011000)
        {
          Chassis.Set_Velocity(v_front);
          Chassis.Calculate_TIM_PeriodElapsedCallback();
          LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
          LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
        }
      }
      //调整后车偏前
      else if ((*__LP_Receive_yl & (uint8_t)0b00011000) == (uint8_t)0b00001000)
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
      if ((*__LP_Receive_yl & (uint8_t)0b00011000) == (uint8_t)0b00011000)
      {
        Chassis.Set_Velocity(v_left);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
        LinePatrol_Receive(__huart_yl, __LP_Receive_yl);
        LinePatrol_Receive(__huart_yr, __LP_Receive_yr);
      }
      //左侧巡线识别到空白，停止运动
      else if (*__LP_Receive_yl == (uint8_t)0b00000000)
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
 * @param UART_HandleTypeDef *__huart
 * @param uint8_t *__B_Receive
 */
void LinePatrol_Barrier(UART_HandleTypeDef *__huart, uint8_t *__B_Receive)
{
  //移动到左侧
  Chassis.Set_Velocity(v_left);
  Chassis.Calculate_TIM_PeriodElapsedCallback();
  HAL_Delay(200);

  //第一次识别
  Berry_Receive(__huart, __B_Receive);
  //第一次左侧有障碍物
  if (*__B_Receive == (uint8_t)0b00000000)
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
    Berry_Receive(__huart, __B_Receive);
    //第二次右侧有障碍物
    if (*__B_Receive == (uint8_t)0b00000000)
    {
      //向左移动避开障碍物前进
      Chassis.Set_Velocity(v_left);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(400);
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
    }
    //第二次左侧有障碍物
    else
    {
      //直接前进
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
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
    Berry_Receive(__huart, __B_Receive);
    //第二次左侧有障碍物
    if (*__B_Receive == (uint8_t)0b00000000)
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
    }
    //第二次右侧有障碍物
    else
    {
      //直接前进
      Chassis.Set_Velocity(v_front);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(300);
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
    }
  }
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
