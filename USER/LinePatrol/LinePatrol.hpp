#ifndef LINEPATROL_HPP
#define LINEPATROL_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "chassis.hpp"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

void LinePatrol_Judge(uint8_t ADC_Bool[]);
void LinePatrol_Decide(uint8_t __ADC_Bool[]);

#endif
