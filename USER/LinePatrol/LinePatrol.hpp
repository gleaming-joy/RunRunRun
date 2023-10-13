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

void LinePatrol_Receive(UART_HandleTypeDef *__huart);
void Berry_Receive();
void Berry_Barrier_Open();
void Berry_Orange_Open();
void Berry_Exsit_Open();
void Berry_Close();

void HAL_Delay_us(uint32_t us);
uint32_t HCSR04_Run();

#endif
