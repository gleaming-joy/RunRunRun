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
#include "HCSR04.hpp"

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

//麦轮底盘定义
Class_Chassis Chassis;
//胶轮底盘定义
Class_Chassis RChassis;
//机械臂相关舵机定义
Class_Arm Arm;
Class_Steer Arm_Steer[4];
Class_Steer Claw_Steer;
Class_Steer Box_Steer;
//步进电机定义
StepMotor TestMotor1;
//超声测距定义
Class_HCSR04 HC1;

uint32_t tim;
//巡线接收定义
uint8_t LP_Receive_yl;
uint8_t LP_Receive_yr;
uint8_t LP_Receive_x;
//树莓派接收定义
uint8_t B_Receive;
//记录障碍物位置
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

  //串口通信定时器中断使能
  HAL_TIM_Base_Start_IT(&UART_TRANSMIT_TIM);
  //底盘定时器中断使能（实际上没有用到）
  HAL_TIM_Base_Start_IT(&CHASSIS_MOTOR_CALCULATE_TIM);
  //底盘初始化及工作模式设置
  Chassis.Init(CHASSIS_MOTOR_PWM_DRIVER_TIM, CHASSIS_MOTOR_CALCULATE_TIM);
  Chassis.Set_Control_Method(Control_Method_OPENLOOP);
  RChassis.R_Init(RMOTOR_PWM_DRIVER_TIM, CHASSIS_MOTOR_CALCULATE_TIM);
  //机械臂初始化
  Arm.Init(Arm_Steer, Claw_Steer, Box_Steer);
  //步进电机初始化及工作模式设置
	TestMotor1.init(&htim9, TIM_CHANNEL_1, 1000000U, GPIOF, GPIO_PIN_10, GPIOI, GPIO_PIN_9);
	TestMotor1.Set_Motor_Running_Speed(6400, 6400);
  HAL_TIM_OC_DelayElapsedCallback(&htim9);
	TestMotor1.Set_Motor_Running_Status(0,0);
  //超声测距初始化
  HC1.Init(HCSR04_Trig_GPIO_PIN, HCSR04_Trig_GPIO_Port, HCSR04_Echo_GPIO_PIN, HCSR04_Echo_GPIO_Port);
  //开启巡线接收
  LinePatrol_Receive(&LP_YL_HUART);
  LinePatrol_Receive(&LP_YR_HUART);
  LinePatrol_Receive(&LP_X_HUART);

	HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //		Arm.Arm_Catch();
//		Arm.Box_Steer_Rotate(0);
//		Start_to_Barrier();
//		HAL_Delay(2000);
//		Cross_Barrier();
//    LinePatrol_Catch_LOrange_NoVisual();
	// 	HAL_Delay(2000);
	// 	LinePatrol_Catch_Purple_NoVision();
	// 	HAL_Delay(4000);

  // //避障区返回准备代码
  // HAL_Delay(2000);
  // Chassis.Velocity_Control(-0.3, 0.1, -1);
	// HAL_Delay(2200);
	// Chassis.Velocity_Control(0.7,0.3,0);
	// HAL_Delay(1200); 
  // Chassis.Velocity_Control(0,0.5,0);
  // while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
  // Chassis.Velocity_Control(0,0,0);
  // Catch_Position_Adjust();

  // //避障区改为高地（版本1）
  // Chassis.Velocity_Control(0, 0.1, -1);
	// HAL_Delay(5000);
  // while (LP_Receive_yl != LP_Receive_yr) {}
  // Chassis.Velocity_Control(0,0,0);
  // HAL_Delay(4000);

  // //高地返回准备代码
  // HAL_Delay(2200);
  // Chassis.Velocity_Control(-0.3, 0, 1);
	// HAL_Delay(2500);
  // Chassis.Velocity_Control(0,0,0);
  // HAL_Delay(2200);
  // Chassis.Velocity_Control(0,-0.5,0);
  // while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {}
  // Chassis.Velocity_Control(0,0,0);
  // Catch_Position_Adjust();
	


    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//
	//现在要用到v2

//	HAL_Delay(1000);
//	Catch_Purple_NoVision_3();
//	Barrier_to_Catch(1);

//	HAL_Delay(500);
//	Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,1);
//	HAL_Delay(1000);
//	Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,0);
//	HAL_Delay(1000);
//	Arm.Arm_Catch();
//	HAL_Delay(1000);
	
	//init
	HAL_Delay(200);
	Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,0);
	Arm.Box_Steer_Rotate(0);
	HAL_Delay(500);
	Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,1);
	HAL_Delay(200);
	Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,0);
	
//	Whole_Process_Left(0);
	Whole_Process_Right(0);

//	//Place_Brick
//	Chassis.Velocity_Control(0,-0.4,0);
//	while (((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) && ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x7F)) {};
//	Chassis.Velocity_Control(0,0,0);
//	
//	HAL_Delay(500);
//	Chassis.Velocity_Control(-0.3, 0.1, -1);	
//	HAL_Delay(2100);
//	Chassis.Velocity_Control(-0.7,-0.2,0);	
//	HAL_Delay(3000);
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(500);
//	Chassis.Velocity_Control(0,0.3,0);
//	while((LP_Receive_x & (uint8_t) 0x7E) != (uint8_t) 0x7E) {};
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(500);
//	Arm.Box_Steer_Rotate(-90);
//	HAL_Delay(1000);
//	Chassis.Velocity_Control(0,-0.4,0);
//	HAL_Delay(2000);
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(500);
//	Arm.Box_Steer_Rotate(0);
//	HAL_Delay(500);
//	Arm.Box_Steer_Rotate(90);
		
//	
//  Start_to_High();
//  LinePatrol_Catch_LOrange();
// 	HAL_Delay(500);
// 	LinePatrol_Catch_Purple();
//	
//  //High_to_Start_Prep
//	Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,0);
//  HAL_Delay(1000);
//  Chassis.Velocity_Control(-0.3, 0, 1);
//	HAL_Delay(2200);
//  Chassis.Velocity_Control(0,0,0);
//  HAL_Delay(1000);
//  Chassis.Velocity_Control(0,-0.5,0);
//  while ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) {};
//  Chassis.Velocity_Control(0,0,0);
//  Catch_Position_Adjust();
//		
//	//High_to_Start
//	Chassis.Velocity_Control(0,-0.5,0);
//	HAL_Delay(2000);
//	while (LP_Receive_yl != (uint8_t)0x80) {};
//	Chassis.Velocity_Control(0,0,0);
//	TestMotor1.Set_Motor_Running_Status(1,1);
//	HAL_Delay(14000);
//	TestMotor1.Set_Motor_Running_Status(0,1);
//	Chassis.Velocity_Control(0,-0.2,0);
//	RChassis.R_Velocity_Control(-0.2,-0.2);
//	HAL_Delay(3000);
//	while((LP_Receive_x & (uint8_t) 0x7E) != (uint8_t) 0x7E) {};
//	TestMotor1.Set_Motor_Running_Status(1,0);
//	Chassis.Velocity_Control(0,0,0);
//	RChassis.R_Velocity_Control(0,0);
//	HAL_Delay(14000);
//	TestMotor1.Set_Motor_Running_Status(0,0);
//	HAL_Delay(2000);
//		
//	//Place_Brick
//	Chassis.Velocity_Control(0,-0.4,0);
//	while (((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x38) && ((LP_Receive_yl & (uint8_t)0x7F) != (uint8_t)0x7F)) {};
//	Chassis.Velocity_Control(0,0,0);
//	Catch_Position_Adjust();
//	
//	HAL_Delay(500);
//	Chassis.Velocity_Control(-0.3, 0.1, -1);	
//	HAL_Delay(2100);
//	Chassis.Velocity_Control(-0.5,0.3,0);	
//	HAL_Delay(4000);
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(500);
//	Chassis.Velocity_Control(0,-0.3,0);
//	while((LP_Receive_x & (uint8_t) 0x7E) != (uint8_t) 0x7E) {};
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(500);
//	Arm.Box_Steer_Rotate(-90);
//	HAL_Delay(1000);
//	Chassis.Velocity_Control(0,-0.4,0);
//	HAL_Delay(2000);
//	Chassis.Velocity_Control(0,0,0);
//	HAL_Delay(500);
//	Arm.Box_Steer_Rotate(0);
//	HAL_Delay(500);
//	Arm.Box_Steer_Rotate(90);

//  TestMotor1.Set_Motor_Running_Status(1,0);
//	HAL_Delay(20000);

	  //Start_to_High_Again
		
//	  Arm.Box_Steer_Rotate(0);
//	  Arm.Arm_Claw_Steer_Control(-10.0f, -65.0f, 100.0f, 90.0f,0);
//		
//    Start_to_High();
//		
//	  //L_Skip
//	  L_Skip();

//    //LinePatrol_Catch_LOrange();
//		
//	  LinePatrol_Catch_Purple_NoVision();
//		
//	  //High_Spin
//    High_Spin();
//			
//		LinePatrol_Catch_LOrange_NoVisual();
//			
//	//Spin_Back
//    Spin_Back();
//		
//	//High_to_Start
//    High_to_Start();
//		
//	//Place_Brick
//	Place_Brick();
		
	
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
