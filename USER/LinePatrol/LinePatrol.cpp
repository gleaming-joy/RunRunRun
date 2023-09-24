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
 * @param uint8_t __LP_Receive[]
 */
void LinePatrol_Receive(uint8_t __LP_Receive[])
{
  HAL_UART_Receive(&huart6, __LP_Receive, sizeof(__LP_Receive), HAL_MAX_DELAY);
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
