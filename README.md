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
- 0: 左胶轮  

- 1: 右胶轮

## 巡线  

GPIO_Input: PC3/M1  PB1/M2  PC4/N1  PC0/N2  

## 舵机

### 机械爪
机械爪舵机由下往上编号  
舵机棕色地线，红色vcc，黄色信号线   
- 机械爪4  
tim8 CH1: PI5/W  

- 机械爪3
tim8 CH2: PI6/X  

- 机械爪2  
tim8 CH3: PI7/Y  

- 机械爪1  
tim8 CH4: PI2/Z  

- 机械爪0  
tim5 CH1: PH10/D

### 存储装置  
tim5 CH2: PH11/C