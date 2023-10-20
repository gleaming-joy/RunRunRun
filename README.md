# gleaming_joy！
## 电机

### 麦轮电机
PWM：绿  
GPIO_Output：蓝 紫
- 0: 麦轮左前 Motor[0]    
tim4 CH1: PD12/H  
GPIO_Output: PF1/I1  PF0/I2  

- 1: 麦轮右前 Motor[1]  
tim4 CH2: PD13/G  
GPIO_Output: PE5/J1  PE4/J2 

- 2: 麦轮左后 Motor[2]  
tim4 CH3: PD14/F  
GPIO_Output: PE6/K1  PE12/K2  

- 3: 麦轮右后 Motor[3]  
tim4 CH4: PD15/E  
GPIO_Output: PC2/L1  PB0/L2    

### 胶轮电机  
- 0: 右胶轮  
tim2 CH1: PA0/S  
GPIO_Output: PC5/O1  PC1/O2  

- 1: 左胶轮  
tim2 CH2: PA1/T  
GPIO_Output: PA5/P1  PA4/P2  

## 舵机

### 机械爪
机械爪舵机由下往上编号  
舵机棕色地线，红色vcc，黄色信号线   
- 机械爪4 Steer[4]  270  
tim8 CH1: PI5/W  

- 机械爪3 Steer[3]  270  
tim8 CH2: PI6/X  

- 机械爪2 Steer[2]  270  
tim8 CH3: PI7/Y  

- 机械爪1 Steer[1]  180  
tim8 CH4: PI2/Z  

- 机械爪0 Steer[0]  270  
tim5 CH1: PH10/D

### 存储装置
Steer[5]    
tim5 CH2: PH11/C  

## 通信
- 巡线模块（竖左）
USART6_RX: PG9  
USART6_TX: PG14  

- 巡线模块 （竖右）
USART3_RX: PD9  
USART3_TX: PD8

- 巡线模块（横）
UART7_RX: PE7  
UART7_TX: PE8  

- 树莓派
UART8_RX: PE0  
UART8_TX: PE1  

- 超声波测距（前）
Trig GPIO_Output: PC4/N1
Echo GPIO_Input: PC0/N2

- 超声波测距（侧）
Trig GPIO_Output: PC3/M1  
Echo GPIO_Input: PB1/M2
## 直线滑台

- 步进电机（右） TestMotor1  
PUL: tim9 CH1: PA2/U  
ENA: PF10/Q1  
DIR: PI9/Q2  

## 巡线

调试时只接电源线。  
长按K1进入调试模式（红灯亮）。  
第一个灯亮采集背景色，按K2，红色灯闪说明采集数据有效。  
按K1，第二个灯亮，采集线的颜色，采集方法同上。
按K1，第三个灯亮，选择高低电平模式。按K2切换模式，第六个灯亮浅色区域返回低电平，第六个灯灭浅色区域返回高电平。  
按K1，第四个灯亮，选择输出的数据类型。第七个灯亮说明输出的是偏移值（串口线），第七个灯灭说明输出的是高低电平。
按K1，第五个灯亮，采集传感器居中时的位置。采集方法同上。  
长按K1退出调试模式（红灯灭）。 

串口  
波特率：9600

2023/10/13  tg_to_htk:  

你的LinePatrol_Easy_Catch_Orange和完整的上坡抓取动作(现在叫Start_to_High)都放在了run里面  
测试一下这两个函数是否还能正常运行，因为我进行了一些形式上的更改  
如果有需要改回去的地方，完整的上坡抓取在主函数里(注释掉了)，LinePatrol_Easy_Catch_Orange你原来的函数放在了现在的下面(也注释掉了)

修改了树莓派的通信，现在不用传参了，但是如果wkh没有搞好的话应该是调不了的

写了Cross_Barrier(),Back_Cross_Barrier两个函数，包含了视觉但是可以用一些略微抽象的方式调试  
比如说Cross_Barrier()你可以在它停在萤石前面后手动用电脑给它发一个0x00(存在障碍物)，波特率为115200，用串口调试助手发（微软商店有），现场应该有USB转TTL，可以找找看  
或者有稍微不那么抽象一点的方法，简单改一下if else的条件  
Back_Cross_Barrier()就好说了，你直接在初始化的时候给Barrier_Location赋个值，main.c里定义的

2023/10/14 4:30 htk_to_tg:

首先，定义了步进电机方向STEPMOTOR_DIRECTION_UP和STEPMOTOR_DIRECTION_DOWN，分别代表上和下；步进电机状态STEPMOTOR_STATUS_ENABLE和STEPMOTOR_STATUS_DISABLE，分别对应开启和关闭
后面调用的时候可以用，前面的我懒得改了

我手动init了PC4和PC0，在gpio里面改了，不知道你重新跑cube的时候会不会覆盖掉，最好是重新跑一次然后把输入设置好

然后什么东西都调不出来

干你妈的超声波

超声波测距最好要求不要有中断，能不能试着解决一下
要不然就给我分配一个用不到的TIM我用来计时