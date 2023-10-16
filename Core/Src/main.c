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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "chassis.hpp"
#include "connect.hpp"
#include "steer.hpp"
#include "arm.hpp"
#include "run.hpp"
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

uint32_t tim;

StepMotor TestMotor1;

// uint8_t LP_Detect_Bool[4];
uint8_t LP_Receive_yl;
uint8_t LP_Receive_yr;
uint8_t LP_Receive_x;
uint8_t B_Receive;

SpeedTypeDef v_stop_main = 
{
	0,0,0
};
SpeedTypeDef v_front_slow =
{
	0,0.4,0
};
SpeedTypeDef v_front_medium =
{
	0,0.6,0
};
SpeedTypeDef v_front_fast = 
{
	0,0.8,0
};
SpeedTypeDef v_left_medium =
{
	0.6,0,0
};
SpeedTypeDef v_turn = 
{
	-0.2,0.1,-1
};
extern SpeedTypeDef v_crotate_left;
extern SpeedTypeDef v_rotate_left;

uint8_t Barrier_Location;
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
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_TIM9_Init();
  MX_USART6_UART_Init();
  MX_UART7_Init();
  MX_UART8_Init();
  MX_USART3_UART_Init();
  MX_TIM10_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim10);

  Chassis.Init(CHASSIS_MOTOR_PWM_DRIVER_TIM, CHASSIS_MOTOR_CALCULATE_TIM);
  Chassis.Set_Control_Method(Control_Method_OPENLOOP);
  RChassis.R_Init(RMOTOR_PWM_DRIVER_TIM, CHASSIS_MOTOR_CALCULATE_TIM);
  Arm_Steer[0].Init(htim5, TIM_CHANNEL_1);
  Arm_Steer[1].Init(htim8, TIM_CHANNEL_4);
  Arm_Steer[2].Init(htim8, TIM_CHANNEL_3);
  Arm_Steer[3].Init(htim8, TIM_CHANNEL_2);
  Claw_Steer.Init(htim8, TIM_CHANNEL_1);
  Box_Steer.Init(htim5, TIM_CHANNEL_2);
	TestMotor1.init(&htim9, TIM_CHANNEL_1, 1000000U, GPIOF, GPIO_PIN_10, GPIOI, GPIO_PIN_9);
	TestMotor1.Set_Motor_Running_Speed(6400, 6400);
  HAL_TIM_OC_DelayElapsedCallback(&htim9);
	TestMotor1.Set_Motor_Running_Status(0,0);
  HAL_TIM_Base_Start_IT(&CHASSIS_MOTOR_CALCULATE_TIM);

  LinePatrol_Receive(&LP_YL_HUART);
  LinePatrol_Receive(&LP_YR_HUART);
  LinePatrol_Receive(&LP_X_HUART);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		// Arm_Catch(Arm_Steer, Claw_Steer);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    // LinePatrol_Receive(&huart6, &LP_Receive_y);
    // LinePatrol_Receive(&huart7, &LP_Receive_x);

    // LinePatrol_Judge(LP_Detect_Bool);

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

    // Box_Steer_Rotate(Box_Steer, 200.0f);
    // HAL_Delay(3000);
    // Arm_Catch(Arm_Steer,Claw_Steer);
		// Arm_Claw_Steer_Control(-30.0f, -90.0f, 10.0f, 0.0f, 1, Arm_Steer, Claw_Steer);
    // Box_Steer_Rotate(Box_Steer, 90.0f);
    // HAL_Delay(2000);
    // Box_Steer_Rotate(Box_Steer, 0.0f);
    // HAL_Delay(2000);
    // Box_Steer_Rotate(Box_Steer, -90.0f);
    // HAL_Delay(2000);
		// Box_Steer_Rotate(Box_Steer, -180.0f);0
		
		// // 1down 0up
//		TestMotor1.Set_Motor_Running_Status(1,1);
//		HAL_Delay(4000);
//		TestMotor1.Set_Motor_Running_Status(1,0);
//		HAL_Delay(4000);
//		TestMotor1.Set_Motor_Running_Status(0,0);
//		HAL_Delay(4000);

    // RChassis.R_Set_Velocity(100.0f);
    // RChassis.R_Calculate_TIM_PeriodElapsedCallback();

//		HAL_Delay(1000);
//    Start_to_Barrier();
		// HAL_Delay(1000);

    // LinePatrol_Barrier(&B_HUART, &B_Receive, &LP_X_HUART, &LP_Receive_x, &Barrier_Location);
		
		// LinePatrol_Easy_Catch_Orange(Arm_Steer, Claw_Steer, &LP_Receive_yr, &LP_YR_HUART);

    // Box_Steer_Rotate(Box_Steer, 200.0f);
    // LinePatrol_Catch_LOrange(Arm_Steer, Claw_Steer, &B_HUART, &B_Receive, &LP_YL_HUART, &LP_Receive_yl);
    // Box_Steer_Rotate(Box_Steer, 90.0f);
    // LinePatrol_Catch_LOrange(Arm_Steer, Claw_Steer, &B_HUART, &B_Receive, &LP_YL_HUART, &LP_Receive_yl);
    // Box_Steer_Rotate(Box_Steer, 0.0f);

    // //��ȼ�Ͽ�
    // LinePatrol_Catch_Purple(Arm_Steer, Claw_Steer, &B_HUART, &B_Receive, &LP_YL_HUART, &LP_Receive_yl, &LP_YR_HUART, &LP_Receive_yr);

    // //����������
    // LinePatrol_Back_Low(&Barrier_Location);
    
    // //�ſ�
    // LinePatrol_Ad_Drop(Box_Steer, &LP_YL_HUART, &LP_Receive_yl, &LP_YR_HUART, &LP_Receive_yr);
		
//		HAL_Delay(2000);
//		Cross_Barrier();
		
//		tim=HCSR04_Run();
//		HAL_Delay(2000);

//    TestMotor1.Set_Motor_Running_Status(1,1);
//    Chassis.Velocity_Control(0,0.4f,0);
//    RChassis.R_Velocity_Control(0.3f,0.3f);
//    HAL_Delay(3000);
//    Chassis.Velocity_Control(0,0,0);
//    RChassis.R_Velocity_Control(0,0);
//    HAL_Delay(11000);
//        
//    TestMotor1.Set_Motor_Running_Status(0,0);
//    Chassis.Velocity_Control(0.0f,1.0f,0.0f);
//    RChassis.R_Velocity_Control(5.0f,5.0f);
//    HAL_Delay(2200);
//        
//    TestMotor1.Set_Motor_Running_Status(1,0);
//    Chassis.Velocity_Control(0,0,0);
//    RChassis.R_Velocity_Control(0,0);
//    HAL_Delay(14000);
//		
//		TestMotor1.Set_Motor_Running_Status(0,0);
//    Chassis.Velocity_Control(0.6f,0,0);
//    while((LP_Receive_yl & (uint8_t)0x38) != (uint8_t)0x38){}
//    HAL_Delay(2200);
//    Chassis.Velocity_Control(0,0,0);
//    HAL_Delay(10000);

//	LinePatrol_Start_Low(&LP_Receive_x, &LP_Receive_yl, &LP_Receive_yr);

//		//理论上完整上平台的代�??
//		Arm_Catch(Arm_Steer, Claw_Steer);
//		HAL_Delay(2000);
//		Arm_Catch_Back(Arm_Steer, Claw_Steer);
//		HAL_Delay(4000);
//		Arm_Parallel_Catch(Arm_Steer, Claw_Steer);
//		HAL_Delay(2000);
//		Arm_Parallel_Catch_Back(Arm_Steer, Claw_Steer);
//		HAL_Delay(4000);

    // TestMotor1.Set_Motor_Running_Status(1,1);
    // Chassis.Set_Velocity(v_front_slow);
    // Chassis.Calculate_TIM_PeriodElapsedCallback();
    // Chassis.R_Set_Velocity(0.3f);
    // RChassis.R_Calculate_TIM_PeriodElapsedCallback();
    // HAL_Delay(3500);
    // Chassis.Set_Velocity(v_stop_main);
    // Chassis.Calculate_TIM_PeriodElapsedCallback();
    // Chassis.R_Set_Velocity(0.0f);
    // RChassis.R_Calculate_TIM_PeriodElapsedCallback();
    // HAL_Delay(10500);
        
    // TestMotor1.Set_Motor_Running_Status(0,0);
    // Chassis.Set_Velocity(v_front_medium);
    // Chassis.Calculate_TIM_PeriodElapsedCallback();
    // RChassis.R_Set_Velocity(0.9f);
    // RChassis.R_Calculate_TIM_PeriodElapsedCallback();
		// while((LP_Receive_x & (uint8_t)0x99) != (uint8_t) 0x18) {}
		// while(LP_Receive_x != (uint8_t) 0xFF) {}
		// HAL_Delay(2500);
		
		// TestMotor1.Set_Motor_Running_Status(1,0);
    // Chassis.Set_Velocity(v_stop_main);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
    // RChassis.R_Set_Velocity(0.0f);
    // RChassis.R_Calculate_TIM_PeriodElapsedCallback();
    // HAL_Delay(14000);
				
		// TestMotor1.Set_Motor_Running_Status(0,0);
    // Chassis.Set_Velocity(v_left_medium);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
    // while((LP_Receive_yl & (uint8_t)0x38) != (uint8_t)0x38){}
    // HAL_Delay(1800);
    // Chassis.Set_Velocity(v_stop_main);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
    // HAL_Delay(14000);
//		HAL_Delay(2000);
//		Start_to_High(Arm_Steer, Claw_Steer);
// TestMotor1.Set_Motor_Running_Status(STEPMOTOR_STATUS_ENABLE,STEPMOTOR_DIRECTION_UP);
// HAL_Delay(14000);

		Box_Steer_Rotate(Box_Steer, 0);
		Arm_Catch(Arm_Steer, Claw_Steer);
		Start_to_Barrier();
		HAL_Delay(2000);
		Cross_Barrier();
    LinePatrol_Catch_LOrange_NoVisual(Arm_Steer, Claw_Steer, Box_Steer);
		HAL_Delay(2000);
		LinePatrol_Catch_Purple_NoVision(Arm_Steer, Claw_Steer,Box_Steer);
		HAL_Delay(4000);
 

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
//	Box_Steer_Rotate(Box_Steer, 0);
//	Arm_Catch(Arm_Steer, Claw_Steer);
//	Start_to_High(Arm_Steer, Claw_Steer, Box_Steer);
//	HAL_Delay(500);
//	LinePatrol_Catch_LOrange(Arm_Steer, Claw_Steer, Box_Steer);
//	// LinePatrol_Catch_LOrange_NoVisual(Arm_Steer, Claw_Steer, Box_Steer);
//	HAL_Delay(500);
//	LinePatrol_Catch_Purple(Arm_Steer, Claw_Steer);
//	// LinePatrol_Catch_Purple_NoVisual(Arm_Steer, Claw_Steer);
//	HAL_Delay(2000);
//	Chassis.Velocity_Control(-0.3, -0.1, -1);	
//	HAL_Delay(2000);
//	Chassis.Velocity_Control(0.5,0.3,0);	
//	HAL_Delay(1200);
//	Catch_Position_Adjust();
//	
//	TestMotor1.Set_Motor_Running_Status(1,1);
//    Chassis.Velocity_Control(0, 0.4, 0);
//    RChassis.R_Velocity_Control(0.3f, 0.3f);
//    HAL_Delay(3500);
//    Chassis.Velocity_Control(0, 0, 0);
//    RChassis.R_Velocity_Control(0.0f, 0.0f);
//    HAL_Delay(10500);
//        
//    TestMotor1.Set_Motor_Running_Status(0,0);
//    Chassis.Velocity_Control(0, 0.2, 0);
//    RChassis.R_Velocity_Control(0.2f, 0.2f);
//	HAL_Delay(6000);
//        
//    TestMotor1.Set_Motor_Running_Status(1,0);
//    Chassis.Velocity_Control(0, 0, 0);
//    RChassis.R_Velocity_Control(0.0f, 0.0f);
//    HAL_Delay(14000);
//		
//		Chassis.Velocity_Control(-0.2f, 0, -0.8f);
//		HAL_Delay(5000);
//		Chassis.Velocity_Control(-0.4f, 0, 0);
//		HAL_Delay(2000);
//		Chassis.Velocity_Control(0,0,0);
//		Box_Steer_Rotate(Box_Steer, -90);
//		HAL_Delay(3000);
//		Chassis.Velocity_Control(0, -0.4f, 0);
//		HAL_Delay(1000);
//		Chassis.Velocity_Control(0,0,0);
//		Box_Steer_Rotate(Box_Steer,0);
//		HAL_Delay(3000);
//		Box_Steer_Rotate(Box_Steer,90);
//		HAL_Delay(20000);
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

		// Chassis.Set_Velocity(v_turn);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(800);
		// while(LP_Receive_yl != LP_Receive_yr) {}
		// Chassis.Set_Velocity(v_stop_main);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(500);
		// Chassis.Set_Velocity(v_left_medium);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// while(LP_Receive_yl != 0xFF) {}
		// while(LP_Receive_yl == 0xFF) {}
		// HAL_Delay(100);
		// Chassis.Set_Velocity(v_stop_main);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(500);
		// Chassis.Set_Velocity(v_front_slow);
    // Chassis.Calculate_TIM_PeriodElapsedCallback();
		// while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
		// Chassis.Set_Velocity(v_stop_main);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// Arm_Catch(Arm_Steer, Claw_Steer);
		// HAL_Delay(1000);
		// Arm_Catch_Back(Arm_Steer, Claw_Steer);
		// Chassis.Set_Velocity(v_front_slow);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// HAL_Delay(300);
		// while((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
		// Chassis.Set_Velocity(v_stop_main);
		// Chassis.Calculate_TIM_PeriodElapsedCallback();
		// Arm_Catch(Arm_Steer, Claw_Steer);
		// HAL_Delay(1000);
		// Arm_Catch_Back(Arm_Steer, Claw_Steer);
		// HAL_Delay(20000);
					
//		//上平台测�??
//		Chassis.Set_Velocity(v_stop_main);
//    Chassis.Calculate_TIM_PeriodElapsedCallback();
//    RChassis.R_Set_Velocity(0.0f);
//    RChassis.R_Calculate_TIM_PeriodElapsedCallback();
//		TestMotor1.Set_Motor_Running_Status(1,1);
//		HAL_Delay(14000);
//		TestMotor1.Set_Motor_Running_Status(0,0);
//		HAL_Delay(1000);
//			
//		TestMotor1.Set_Motor_Running_Status(0,0);
//    Chassis.Set_Velocity(v_front_medium);
//    Chassis.Calculate_TIM_PeriodElapsedCallback();
//    RChassis.R_Set_Velocity(0.8f);
//    RChassis.R_Calculate_TIM_PeriodElapsedCallback();
//    HAL_Delay(6000);
//		
//		TestMotor1.Set_Motor_Running_Status(1,0);
//    Chassis.Set_Velocity(v_stop_main);
//		Chassis.Calculate_TIM_PeriodElapsedCallback();
//    RChassis.R_Set_Velocity(0.0f);
//    RChassis.R_Calculate_TIM_PeriodElapsedCallback();
//    HAL_Delay(14000);
//		
//		TestMotor1.Set_Motor_Running_Status(0,0);
//		HAL_Delay(20000);
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
