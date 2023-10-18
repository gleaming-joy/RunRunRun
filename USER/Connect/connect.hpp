#ifndef CONNECT_HPP
#define CONNECT_HPP

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
void Berry_Orange_Open();
void Berry_Purple_Open();

#endif
