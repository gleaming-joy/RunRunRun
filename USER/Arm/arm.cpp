/* Includes ------------------------------------------------------------------*/

#include "arm.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function declarations ---------------------------------------------*/

/**
 * @brief 设定机械臂夹取时的位置
 *
 * @param __Arm_Steer[]  机械臂舵机
 */

void Arm_Steer_Output_Get_Locate(Class_Steer __Arm_Steer[])
{
    __Arm_Steer[0].Set_Out(-50.0f, 270);
    __Arm_Steer[0].Output();
    __Arm_Steer[1].Set_Out(50.0f, 180);
    __Arm_Steer[1].Output();
    __Arm_Steer[2].Set_Out(30.0f, 270);
    __Arm_Steer[2].Output();
    __Arm_Steer[3].Set_Out(0.0f, 270);
    __Arm_Steer[3].Output();
}

/**
 * @brief 设定机械臂放置矿物时的位置
 *
 * @param __Arm_Steer[]  机械臂舵机
 */

void Arm_Steer_Output_Store_Locate(Class_Steer __Arm_Steer[])
{
    __Arm_Steer[0].Set_Out(-10.0f, 270);
    __Arm_Steer[0].Output();
    __Arm_Steer[1].Set_Out(-70.0f, 180);
    __Arm_Steer[1].Output();
    __Arm_Steer[2].Set_Out(0.0f, 270);
    __Arm_Steer[2].Output();
    __Arm_Steer[3].Set_Out(0.0f, 270);
    __Arm_Steer[3].Output();
}

/**
 * @brief 设定机械爪打开
 *
 * @param __Claw_Steer  机械爪舵机
 */

void Claw_Steer_Open(Class_Steer __Claw_Steer)
{
    __Claw_Steer.Set_Out(0.0f, 270);
    __Claw_Steer.Output();
}

/**
 * @brief 设定机械爪关上
 *
 * @param __Claw_Steer  机械爪舵机
 */

void Claw_Steer_Close(Class_Steer __Claw_Steer)
{
    __Claw_Steer.Set_Out(-10.0f, 270);
    __Claw_Steer.Output();
}

/**
 * @brief 设定木盒旋转
 *
 * @param __Box_Steer  木盒舵机
 */

void Box_Steer_Rotate(Class_Steer __Box_Steer, float location)
{
    // if (location == 0.0f)
    // {
    //     __Box_Steer.Set_Out(0.0f, 350);
    //     __Box_Steer.Output(); 
    // }
    // else if (location == 90.0f)
    // {
    //     __Box_Steer.Set_Out(0.0f, 350);
    //     __Box_Steer.Output();
    // }
    __Box_Steer.Set_Out(location, 350);
    __Box_Steer.Output();
}