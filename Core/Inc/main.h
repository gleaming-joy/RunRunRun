/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern TIM_HandleTypeDef htim4;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

//底盘相关定时器
#define CHASSIS_MOTOR_PWM_DRIVER_TIM htim4
#define CHASSIS_MOTOR_CALCULATE_TIM htim4
#define RMOTOR_PWM_DRIVER_TIM htim2

//串口通信定时器
#define UART_TRANSMIT_TIM htim10
//巡线串口接收
#define LP_YL_HUART huart6
#define LP_YR_HUART huart3
#define LP_X_HUART huart7
//树莓派串口接收
#define B_HUART huart2

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

//麦轮电机GPIO设置
#define Pin_Pushpull_MotorDirectionA1_Pin GPIO_PIN_1
#define Pin_Pushpull_MotorDirectionA1_GPIO_Port GPIOF
#define Pin_Pushpull_MotorDirectionA2_Pin GPIO_PIN_5
#define Pin_Pushpull_MotorDirectionA2_GPIO_Port GPIOE
#define Pin_Pushpull_MotorDirectionA3_Pin GPIO_PIN_6
#define Pin_Pushpull_MotorDirectionA3_GPIO_Port GPIOE
#define Pin_Pushpull_MotorDirectionA4_Pin GPIO_PIN_2
#define Pin_Pushpull_MotorDirectionA4_GPIO_Port GPIOC
#define Pin_Pushpull_MotorDirectionB1_Pin GPIO_PIN_0
#define Pin_Pushpull_MotorDirectionB1_GPIO_Port GPIOF
#define Pin_Pushpull_MotorDirectionB2_Pin GPIO_PIN_4
#define Pin_Pushpull_MotorDirectionB2_GPIO_Port GPIOE
#define Pin_Pushpull_MotorDirectionB3_Pin GPIO_PIN_12
#define Pin_Pushpull_MotorDirectionB3_GPIO_Port GPIOE
#define Pin_Pushpull_MotorDirectionB4_Pin GPIO_PIN_0
#define Pin_Pushpull_MotorDirectionB4_GPIO_Port GPIOB
//胶轮电机GPIO设置
#define RMotorDirectionA1_Pin GPIO_PIN_5
#define RMotorDirectionA1_GPIO_Port GPIOC
#define RMotorDirectionA2_Pin GPIO_PIN_5
#define RMotorDirectionA2_GPIO_Port GPIOA
#define RMotorDirectionB1_Pin GPIO_PIN_1
#define RMotorDirectionB1_GPIO_Port GPIOC
#define RMotorDirectionB2_Pin GPIO_PIN_4
#define RMotorDirectionB2_GPIO_Port GPIOA
//超声测距GPIO设置
#define HCSR04_Trig_GPIO_Port GPIOC
#define HCSR04_Trig_GPIO_PIN GPIO_PIN_4
#define HCSR04_Echo_GPIO_Port GPIOC
#define HCSR04_Echo_GPIO_PIN GPIO_PIN_0
//步进电机方向设置
#define STEPMOTOR_DIRECTION_UP 0
#define STEPMOTOR_DIRECTION_DOWN 1
#define STEPMOTOR_STATUS_ENABLE 1
#define STEPMOTOR_STATUS_DISABLE 0

//霍尔编码器相关（没用到）
#define Pin_Exti_HallEncoderA1_Pin GPIO_PIN_7
#define Pin_Exti_HallEncoderA1_GPIO_Port GPIOF
#define Pin_Exti_HallEncoderA1_EXTI_IRQn EXTI7_IRQn
#define Pin_Exti_HallEncoderA2_Pin GPIO_PIN_6
#define Pin_Exti_HallEncoderA2_GPIO_Port GPIOF
#define Pin_Exti_HallEncoderA2_EXTI_IRQn EXTI6_IRQn
#define Pin_Exti_HallEncoderA3_Pin GPIO_PIN_10
#define Pin_Exti_HallEncoderA3_GPIO_Port GPIOD
#define Pin_Exti_HallEncoderA3_EXTI_IRQn EXTI10_IRQn
#define Pin_Exti_HallEncoderA4_Pin GPIO_PIN_15
#define Pin_Exti_HallEncoderA4_GPIO_Port GPIOE
#define Pin_Exti_HallEncoderA4_EXTI_IRQn EXTI15_IRQn
#define Pin_PullDown_HallEncoderB1_Pin GPIO_PIN_11
#define Pin_PullDown_HallEncoderB1_GPIO_Port GPIOF
#define Pin_PullDown_HallEncoderB2_Pin GPIO_PIN_8
#define Pin_PullDown_HallEncoderB2_GPIO_Port GPIOF
#define Pin_PullDown_HallEncoderB3_Pin GPIO_PIN_8
#define Pin_PullDown_HallEncoderB3_GPIO_Port GPIOD
#define Pin_PullDown_HallEncoderB4_Pin GPIO_PIN_7
#define Pin_PullDown_HallEncoderB4_GPIO_Port GPIOE

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
