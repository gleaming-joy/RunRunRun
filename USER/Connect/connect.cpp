/* Includes ------------------------------------------------------------------*/

#include "connect.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

//巡线相关
uint8_t Send_to_LinePatrol = 0x57;
extern uint8_t LP_Receive_yl;
extern uint8_t LP_Receive_yr;
extern uint8_t LP_Receive_x;;
//树莓派相关
uint8_t Send_Orange = 0x02;
uint8_t Send_Purple = 0x03;
extern uint8_t B_Receive;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart8;

extern TIM_HandleTypeDef htim10;

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 定时器中断回调函数
 *
 * @param TIM_HandleTypeDef *htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &UART_TRANSMIT_TIM)
  {
    HAL_UART_Transmit_IT(&LP_YL_HUART, &Send_to_LinePatrol, 1);
    HAL_UART_Transmit_IT(&LP_YR_HUART, &Send_to_LinePatrol, 1);
    HAL_UART_Transmit_IT(&LP_X_HUART, &Send_to_LinePatrol, 1);
  }
}

/**
 * @brief 巡线模块信息接收
 *
 * @param uint8_t __LP_Receive
 * @param UART_HandleTypeDef *__huart
 */
void LinePatrol_Receive(UART_HandleTypeDef *__huart)
{
	if (__huart == &LP_YL_HUART)
	{
		HAL_UART_Receive_IT(__huart, &LP_Receive_yl, 1);
	}
	else if (__huart == &LP_YR_HUART)
	{
		HAL_UART_Receive_IT(__huart, &LP_Receive_yr, 1);
	}
	else if (__huart == &LP_X_HUART)
	{
		HAL_UART_Receive_IT(__huart, &LP_Receive_x, 1);
	}
}

/**
 * @brief 串口接收中断回调函数
 *
 * @param UART_HandleTypeDef *__huart
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &LP_YL_HUART || huart == &LP_YR_HUART || huart == &LP_X_HUART)
	{
		LinePatrol_Receive(huart);
	}
}

/**
 * @brief 从树莓派接收信息
 *
 * @param 
 */
void Berry_Receive()
{
  HAL_UART_Receive_IT(&B_HUART, &B_Receive, 1);
}

/**
 * @brief 向树莓派发送信息使其开启扫描橙色
 *
 * @param
 */
void Berry_Orange_Open()
{
  HAL_UART_Transmit_IT(&B_HUART, &Send_Orange, 1);
}

/**
 * @brief 向树莓派发送信息使其开始扫描紫色
 *
 * @param
 */
void Berry_Purple_Open()
{
  HAL_UART_Transmit_IT(&B_HUART, &Send_Purple, 1);
}




