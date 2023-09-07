/* Includes ------------------------------------------------------------------*/

#include "LinePatrol.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

  SpeedTypeDef v_front=
  {
    0, 0.3, 0
  };
  
  SpeedTypeDef v_back=
  {
    0, -0.3, 0
  };

  SpeedTypeDef v_right=
  {
    0.3, 0, 0
  };  
  
  SpeedTypeDef v_left=
  {
    -0.3, 0, 0
  }; 
  
  SpeedTypeDef v_rotate=
  {
    0, 0, 0.6
  };

  SpeedTypeDef v_crotate=
  {
    0, 0, -0.6
  };

  SpeedTypeDef v_stop=
  {
    0, 0, 0
  };

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 巡线模块判断
 *
 * @param uint16_t __ADC_Value[]
 * @param uint8_t __ADC_Bool[]
 */
void LinePatrol_Judge(uint16_t __ADC_Value[], uint8_t __ADC_Bool[])
{
    if (__ADC_Value[0] < 400)
    {
      __ADC_Bool[0] = 0;
    }
    else if (__ADC_Value[0] > 600)
    {
      __ADC_Bool[0] = 1;
    }

    if (__ADC_Value[1] < 400)
    {
      __ADC_Bool[1] = 0;
    }
    else if (__ADC_Value[1] > 600)
    {
      __ADC_Bool[1] = 1;
    }

    if (__ADC_Value[2] < 400)
    {
      __ADC_Bool[2] = 0;
    }
    else if (__ADC_Value[2] > 600)
    {
      __ADC_Bool[2] = 1;
    }

    if (__ADC_Value[3] < 400)
    {
      __ADC_Bool[3] = 0;
    }
    else if (__ADC_Value[3] > 600)
    {
      __ADC_Bool[3] = 1;
    }
}

/**
 * @brief 巡线模块决定前进方向
 *
 * @param uint8_t __ADC_Bool[]
 */
void LinePatrol_Decide(uint8_t __ADC_Bool[])
{
    //向前运动
    if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 1 && __ADC_Bool[2] == 1)
    {
        Chassis.Set_Velocity(v_front);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
    }
    //右转弯
    else if (__ADC_Bool[0] == 1 && __ADC_Bool[1] == 1 && __ADC_Bool[2] == 1 && __ADC_Bool[3] == 0)
    {
      Chassis.Set_Velocity(v_rotate);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(10000);
      Chassis.Set_Velocity(v_left);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
    }
    //左转弯
    else if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 1 && __ADC_Bool[2] == 1 && __ADC_Bool[3] == 1)
    {
      Chassis.Set_Velocity(v_crotate);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
      HAL_Delay(10000);
      Chassis.Set_Velocity(v_right);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
    }
    //车头向右转
    else if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 0 && __ADC_Bool[2] == 1 && __ADC_Bool[3] == 0)
    {
      while (1)
      {
        if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 1 && __ADC_Bool[2] == 1 && __ADC_Bool[3] == 0)
        {
          break;
        }
        Chassis.Set_Velocity(v_crotate);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
      }
    }
    //车头向左转
    else if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 1 && __ADC_Bool[2] == 0 && __ADC_Bool[3] == 0)
    {
      while (1)
      {
        if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 1 && __ADC_Bool[2] == 1 && __ADC_Bool[3] == 0)
        {
          break;
        }
        Chassis.Set_Velocity(v_rotate);
        Chassis.Calculate_TIM_PeriodElapsedCallback();
      }
    }
    //停下
    else if (__ADC_Bool[0] == 0 && __ADC_Bool[1] == 0 && __ADC_Bool[2] == 0 && __ADC_Bool[3] == 0)
    {
      Chassis.Set_Velocity(v_stop);
      Chassis.Calculate_TIM_PeriodElapsedCallback();
    }
}

/* Function prototypes -------------------------------------------------------*/
