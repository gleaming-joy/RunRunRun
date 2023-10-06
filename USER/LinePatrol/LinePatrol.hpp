#ifndef LINEPATROL_HPP
#define LINEPATROL_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "chassis.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

void LinePatrol_Receive(UART_HandleTypeDef *__huart, uint8_t *__LP_Receive);
void LinePatrol_Decide(uint8_t* __LP_Receive_front, uint8_t* __LP_Receive_back);

// void LinePatrol_Judge(uint8_t ADC_Bool[]);
// void LinePatrol_Decide(uint8_t __ADC_Bool[]);

#endif
