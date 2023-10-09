/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "chassis.hpp"
#include "LinePatrol.hpp"
#include "steer.hpp"
#include "arm.hpp"
#include "StepMotor.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

Class_Chassis Chassis;
Class_Chassis RChassis;
Class_Steer Arm_Steer[4];
Class_Steer Claw_Steer;
Class_Steer Box_Steer;

// uint8_t LP_Detect_Bool[4];
uint8_t LP_Receive_yl;
uint8_t LP_Receive_yr;
uint8_t LP_Receive_x;
uint8_t B_Receive;

uint8_t Barrier_Location;

SpeedTypeDef v0=
  {
    0, 0.6, 0
  };
SpeedTypeDef v1=
  {
    0, 0, 1
  };
SpeedTypeDef v2=
  {
    0, 0, -1
  };
SpeedTypeDef v3=
  {
    0.6, 0, 0
  };	
SpeedTypeDef v4=
  {
    -0.6, 0, 0
  };
SpeedTypeDef v5=
  {
    0, -0.6, 0
  };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_TIM9_Init();
  MX_USART6_UART_Init();
  MX_UART7_Init();
  MX_UART8_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  //底盘初始化
  Chassis.Init(CHASSIS_MOTOR_PWM_DRIVER_TIM, CHASSIS_MOTOR_CALCULATE_TIM);
  Chassis.Set_Control_Method(Control_Method_OPENLOOP);
  //胶轮初始化
  RChassis.R_Init(RMOTOR_PWM_DRIVER_TIM, CHASSIS_MOTOR_CALCULATE_TIM);
  //舵机初始化
  Arm_Steer[0].Init(htim5, TIM_CHANNEL_1);
  Arm_Steer[1].Init(htim8, TIM_CHANNEL_4);
  Arm_Steer[2].Init(htim8, TIM_CHANNEL_3);
  Arm_Steer[3].Init(htim8, TIM_CHANNEL_2);
  Claw_Steer.Init(htim8, TIM_CHANNEL_1);
  Box_Steer.Init(htim5, TIM_CHANNEL_2);
	//步进电机初始化
	TestMotor1.init(&htim9, TIM_CHANNEL_1, 1000000U, GPIOF, GPIO_PIN_10, GPIOI, GPIO_PIN_9);
  //使能计算时钟
  HAL_TIM_Base_Start_IT(&CHASSIS_MOTOR_CALCULATE_TIM);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    //巡线模块信息接受
    // LinePatrol_Receive(&huart6, &LP_Receive_y);
    // LinePatrol_Receive(&huart7, &LP_Receive_x);


    //巡线模块判断
    // LinePatrol_Judge(LP_Detect_Bool);

    // //根据巡线模块决定前进方向
    // LinePatrol_Decide(LP_Detect_Bool);

    // Chassis.Set_Velocity(v0);
    // Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(1000);
		// Chassis.Set_Velocity(v1);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(4000);
    // Chassis.Set_Velocity(v2);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(4000);
    // Chassis.Set_Velocity(v3);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(1000);
    // Chassis.Set_Velocity(v4);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(1000);
    // Chassis.Set_Velocity(v5);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(3000);

    // // 控制舵机


    // Box_Steer_Rotate(Box_Steer, 200.0f);
    // HAL_Delay(3000);
    // Arm_Steer_Output_Get_Locate(Arm_Steer);
		// HAL_Delay(3000);
    // Claw_Steer_Close(Claw_Steer);
    // HAL_Delay(2000);
    // Arm_Steer_Output_Store_Locate(Arm_Steer);
    // HAL_Delay(3000);
    // Claw_Steer_Open(Claw_Steer);
    // HAL_Delay(2000);
		// Arm_Steer_Output_Get_Locate(Arm_Steer);
		// HAL_Delay(2000);
    
    // Box_Steer_Rotate(Box_Steer, 90.0f);
    // HAL_Delay(2000);
    // Box_Steer_Rotate(Box_Steer, 0.0f);
    // HAL_Delay(2000);
    // Box_Steer_Rotate(Box_Steer, -90.0f);
    // HAL_Delay(2000);
		// Box_Steer_Rotate(Box_Steer, -180.0f);
		// HAL_Delay(2000);
		
		// //控制步进电机 
		// TestMotor1.Set_Motor_Running_Status(6400, 6400, 1);
    // HAL_TIM_OC_DelayElapsedCallback(&htim9);
		// HAL_Delay(1000);
    // TestMotor1.Set_Motor_Running_Status(6400, 6400, 0);
		// HAL_Delay(1000);
		// HAL_Delay(1000);

    // // 控制胶轮
    // RChassis.R_Set_Velocity(-1.0f);
    // RChassis.R_Calculate_TIM_PeriodElapsedCallback();

    //从启动区移动到低平面的采矿区
    LinePatrol_Start_Low(&LP_Receive_yl, &LP_Receive_yr, &LP_YL_HUART, &LP_YR_HUART);

    // //避障并移动到采矿区巡线处
    // LinePatrol_Barrier(&B_HUART, &B_Receive, &LP_X_HUART, &LP_Receive_x, &Barrier_Location);

    // //采晶体矿
    // Box_Steer_Rotate(Box_Steer, 200.0f);
    // LinePatrol_Catch_LOrange(Arm_Steer, Claw_Steer, &B_HUART, &B_Receive, &LP_YL_HUART, &LP_Receive_yl);
    // Box_Steer_Rotate(Box_Steer, 90.0f);
    // LinePatrol_Catch_LOrange(Arm_Steer, Claw_Steer, &B_HUART, &B_Receive, &LP_YL_HUART, &LP_Receive_yl);
    // Box_Steer_Rotate(Box_Steer, 0.0f);

    // //采燃料矿
    // LinePatrol_Catch_Purple(Arm_Steer, Claw_Steer, &B_HUART, &B_Receive, &LP_YL_HUART, &LP_Receive_yl, &LP_YR_HUART, &LP_Receive_yr);

    // //返回启动区
    // LinePatrol_Back_Low(&Barrier_Location);
    
    // //放矿
    // LinePatrol_Ad_Drop(Box_Steer, &LP_YL_HUART, &LP_Receive_yl, &LP_YR_HUART, &LP_Receive_yr);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
