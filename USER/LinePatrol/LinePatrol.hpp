#ifndef LINEPATROL_HPP
#define LINEPATROL_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "chassis.hpp"
#include "arm.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

void LinePatrol_Receive(UART_HandleTypeDef *__huart, uint8_t *__LP_Receive);
void LinePatrol_Adjust(uint8_t *__LP_Receive_yl, uint8_t *__LP_Receive_yr, UART_HandleTypeDef *__huart_yl, UART_HandleTypeDef *__huart_yr);
void LinePatrol_Start(uint8_t *__LP_Receive_yl, uint8_t *__LP_Receive_yr, UART_HandleTypeDef *__huart_yl, UART_HandleTypeDef *__huart_yr);
void Berry_Receive(UART_HandleTypeDef *__huart, uint8_t *__B_Receive);
void LinePatrol_Barrier(UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_x_huart, uint8_t *__LP_x_Receive);
void LinePatrol_Catch_LOrange(Class_Steer __Arm_Steer[], Class_Steer __Claw_Steer, UART_HandleTypeDef *__B_huart, uint8_t *__B_Receive, UART_HandleTypeDef *__LP_yl_huart, uint8_t *__LP_yl_Receive);
// void LinePatrol_Judge(uint8_t ADC_Bool[]);
// void LinePatrol_Decide(uint8_t __ADC_Bool[]);

#endif
