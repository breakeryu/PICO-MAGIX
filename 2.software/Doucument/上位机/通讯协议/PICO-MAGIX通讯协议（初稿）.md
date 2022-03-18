PICO-MAGIX通讯协议（初稿）



# 第一章：综述

PICO_MAGIX通讯协议文件是总括上位机和下位机定义的通讯方式，所有的通讯指令都在本文件中包括。

- 本协议参考MODBUS协议进行编写。


- 本协议软件参考木南协议进行编写。


https://github.com/foxclever/Modbus

- 本协议参考GESHE测控大师软件编写。


http://www.geshe.com/zh-cn/

- 本协议参考“中国电光MODBUS3.0 馈电开关”编写。

# 第二章：通讯协议总括

本章将总括使用的ModBus-RTU通讯协议。



# 各指令对应的地址说明

## 1.读单个线圈01命令（起始地址：00H）



| 线圈起始地址 |            位功能定义            | 事件代码（HEX） |
| :----------: | :------------------------------: | :-------------: |
|     00H      |           设备停止状态           |       ——        |
|     01H      |           设备运行状态           |       ——        |
|     02H      |               备用               |       ——        |
|     03H      |               备用               |       ——        |
|     04H      |               备用               |       ——        |
|     05H      |               备用               |       ——        |
|     06H      |               备用               |       ——        |
|     07H      |               备用               |       ——        |
|     08H      |               备用               |       ——        |
|     09H      |               备用               |       ——        |
|     0AH      |               备用               |       ——        |
|     0BH      |               备用               |       ——        |
|     0CH      |               备用               |       ——        |
|     0DH      |               备用               |       ——        |
|     0FH      |               备用               |       ——        |
|     10H      | 灯带运行状态（启动：1，停止：0） |                 |
|     11H      | 灯带剧场模式（开启：1，关闭：0） |                 |
|     12H      | 灯带彩虹模式（开启：1，关闭：0） |                 |
|     13H      | 灯带测试模式（开启：1，关闭：0） |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |

## 2.写单个线圈05命令（起始地址：100H）

| 线圈起始地址 |            位功能定义            | 事件代码（HEX） |
| :----------: | :------------------------------: | :-------------: |
|     100H     |   灯带运行（启动：1，停止：0）   |       ——        |
|     101H     | 灯带剧场打开（开启：1，关闭：0） |       ——        |
|     102H     | 灯带彩虹打开（开启：1，关闭：0） |       ——        |
|     103H     | 灯带测试打开（开启：1，关闭：0） |       ——        |
|     104H     |        读AL6180读写寄存器        |       ——        |
|     105H     |        写AL6180读写寄存器        |       ——        |
|     106H     |        读AL6180结果寄存器        |       ——        |
|     107H     |                                  |       ——        |
|     108H     |                                  |       ——        |
|     109H     |                                  |       ——        |
|     0AH      |                                  |       ——        |
|     0BH      |                                  |       ——        |
|     0CH      |                                  |       ——        |
|     0DH      |                                  |       ——        |
|     0FH      |                                  |       ——        |
|     10H      |                                  |                 |
|     11H      |                                  |                 |
|     12H      |                                  |                 |
|     13H      |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |
|              |                                  |                 |

## 3.读多路寄存器03命令（起始地址：00H）——模拟量

| 寄存器起始地址 | 功能定义 | 系数 |
| :------------: | :------: | :--: |
|      00H       |   备用   |  ——  |
|      01H       |   备用   |  ——  |
|      02H       |   备用   |  ——  |
|      03H       |   备用   |  ——  |
|      04H       |   备用   |  ——  |
|      05H       |   备用   |  ——  |
|      06H       |   备用   |  ——  |
|      07H       |   备用   |  ——  |
|      08H       |   备用   |  ——  |
|      09H       |   备用   |  ——  |
|      0AH       | 系统电压 | 0.01 |
|      0BH       | 气体浓度 |  1   |
|      0CH       |   光强   |  1   |
|      0DH       |   温度   | 0.01 |
|      0EH       |   湿度   | 0.01 |
|      0FH       |   距离   |  1   |
|      10H       |          |      |
|      11H       |          |      |
|      12H       |          |      |
|      13H       |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |
|                |          |      |

## 4.读多路寄存器03命令（起始地址：30H）——定制参数

| 序号 | 寄存器起始地址 | 功能定义                          | 备注                                      |
| ---- | -------------- | --------------------------------- | ----------------------------------------- |
| 1    | 30H            | Model_id                          | 实际8位无符号，复位后为0xb4               |
| 2    | 31H            | Model_Rev_Major                   | 实际8位无符号，复位后为0x1，值有效范围0~7 |
| 3    | 32H            | Model_Rev_Minor                   | 实际8位无符号，复位后为0x3，值有效范围0~7 |
| 4    | 33H            | Module_Rev_Major                  | 实际8位无符号，复位后为0x1，值有效范围0~7 |
| 5    | 34H            | Module_Rev_Minor                  | 实际8位无符号，复位后为0x2，值有效范围0~7 |
| 6    | 35H            | Date_Hi                           | 实际8位无符号，高4位为年，低4位为月       |
| 7    | 36H            | Date_Lo                           | 实际8位无符号，高4位为日，低4位为脉冲数   |
| 8    | 37H            | Id_Time                           | 实际16位无符号，时间 = 寄存器值 *2        |
| 9    | 38H            | Mode_GPIO0                        | 实际8位无符号，复位后为0x60               |
| 10   | 39H            | Mode_GPIO1                        | 实际8位无符号，复位后为0x20               |
| 11   | 3AH            | History_Ctrl                      | 实际8位无符号，复位后为0x0                |
| 12   | 3BH            | Interrupt_Config_GPIO             | 实际8位无符号，复位后为0x0                |
| 13   | 3CH            | Interrupt_Clear                   | 实际8位无符号，复位后为0x0                |
| 14   | 3DH            | Fresh_Out_Of_Reset                | 实际8位无符号，复位后为0x1                |
| 15   | 3EH            | Grouped_Para_Hold                 | 实际8位无符号，复位后为0x0                |
| 16   | 3FH            | Range_start                       | 实际8位无符号，复位后为0x0                |
| 17   | 40H            | Range_Thresh_High                 | 实际8位无符号，复位后为0xFF               |
| 18   | 41H            | Range_Thresh_Low                  | 实际8位无符号，复位后为0x0                |
| 19   | 42H            | Range_InterMeasurement_Period     | 实际8位无符号，复位后为0xFF               |
| 20   | 43H            | Range_Max_ConverGence_Time        | 实际8位无符号，复位后为0x31               |
| 21   | 44H            | Range_CrossTalk_Compensation_Rate | 实际16位无符号，复位后为0x0               |
| 22   | 45H            | Range_CrossTalk_Valid_Height      | 实际8位无符号，复位后为0x14               |
| 23   | 46H            | Range_Early_ConverGence_Estimate  | 实际16位无符号，复位后为0x0               |
| 24   | 47H            | Range_Part_To_Part_Range_Offset   | 实际8位无符号，复位后为0xYY               |
| 25   | 48H            | Range_Ignore_Valid_Height         | 实际8位无符号，复位后为0x0                |
| 26   | 49H            | Range_Ingore_Threshold            | 实际16位无符号，复位后为0x0               |
| 27   | 4AH            | Range_Max_Ambient_Level_Mult      | 实际8位无符号，复位后为0xA0               |
| 28   | 4BH            | Range_Check_Enables               | 实际8位无符号，复位后为0x11               |
| 29   | 4CH            | Range_Vhv_RecalibRate             | 实际8位无符号，复位后为0x0                |
| 30   | 4DH            | Range_Vhv_Repeat_Rate             | 实际8位无符号，复位后为0x0                |
| 31   | 4EH            | Als_Start                         | 实际8位无符号，复位后为0x0                |
| 32   | 4FH            | Als_Thresh_High                   | 实际16位无符号，复位后为0xFFFF            |
| 33   | 50H            | Als_Thresh_Low                    | 实际16位无符号，复位后为0x0               |
| 34   | 51H            | Als_InterMeasurement_Period       | 实际8位无符号，复位后为0xFF               |
| 35   | 52H            | Als_Analogue_Gain                 | 实际8位无符号，复位后为0x06               |
| 36   | 53H            | Als_interRation_Period            | 实际16位无符号，复位后为0x0               |
| 37   | 54H            | Readout_Averaging_Sample_Period   | 实际8位无符号，复位后为0x30               |
| 38   | 55H            | Firmware_bootup                   | 实际8位无符号，复位后为0x1                |
| 39   | 56H            | Firmaware_Result_Scaler           | 实际8位无符号，复位后为0x1                |
| 40   | 57H            | I2C_Slave_Device_Adderss          | 实际8位无符号，复位后为0x29               |
| 41   | 58H            | InterLeaved_Mode_Enable           | 实际8位无符号，复位后为0x0                |
| 1    | 59H            | Range_Status                      | 实际8位无符号，复位后为0x01               |
| 2    | 5AH            | Als_Status                        | 实际8位无符号，复位后为0x01               |
| 3    | 5BH            | Interrupt_Status_GPIO             | 实际8位无符号，复位后为0x00               |
| 4    | 5CH            | Als_Value                         | 实际16位无符号，复位后为0x00              |
| 5    | 5DH            | History_Buffer0                   | 实际16位无符号，复位后为0x00              |
| 6    | 5EH            | History_Buffer1                   | 实际16位无符号，复位后为0x00              |
| 7    | 5FH            | History_Buffer2                   | 实际16位无符号，复位后为0x00              |
| 8    | 60H            | History_Buffer3                   | 实际16位无符号，复位后为0x00              |
| 9    | 61H            | History_Buffer4                   | 实际16位无符号，复位后为0x00              |
| 10   | 62H            | History_Buffer5                   | 实际16位无符号，复位后为0x00              |
| 11   | 63H            | History_Buffer6                   | 实际16位无符号，复位后为0x00              |
| 12   | 64H            | History_Buffer7                   | 实际16位无符号，复位后为0x00              |
| 13   | 65H            | Range_Value                       | 实际8位无符号，复位后为0x00               |
| 14   | 66H            | Range_Raw                         | 实际8位无符号，复位后为0x00               |
| 15   | 67H            | Range_Rerurn_Rate                 | 实际16位无符号，复位后为0x00              |
| 16   | 68H            | Range_Reference_Rate              | 实际16位无符号，复位后为0x00              |
| 17   | 69H            | Range_Return_Signal_Count_H       | 实际32位无符号，复位后为0x00              |
| 18   | 6AH            | Range_Return_Signal_Count_L       | 实际32位无符号，复位后为0x00              |
| 19   | 6BH            | Range_Reference_Signal_Count_H    | 实际32位无符号，复位后为0x00              |
| 20   | 6CH            | Range_Reference_Signal_Count_L    | 实际32位无符号，复位后为0x00              |
| 21   | 6DH            | Range_Return_Amb_Count_H          | 实际32位无符号，复位后为0x00              |
| 22   | 6EH            | Range_Return_Amb_Count_L          | 实际32位无符号，复位后为0x00              |
| 23   | 6FH            | Range_Reference_Amb_Count_H       | 实际32位无符号，复位后为0x00              |
| 24   | 70H            | Range_Reference_Amb_Count_L       | 实际32位无符号，复位后为0x00              |
| 25   | 71H            | Range_Return_Conv_Time_H          | 实际32位无符号，复位后为0x00              |
| 26   | 72H            | Range_Return_Conv_Time_L          | 实际32位无符号，复位后为0x00              |
| 27   | 73H            | Range_Reference_Conv_Time_H       | 实际32位无符号，复位后为0x00              |
| 28   | 74H            | Range_Reference_Conv_Time_L       | 实际32位无符号，复位后为0x00              |

## 5.写单路寄存器06命令、写多路寄存器10命令（起始地址：30H）——定制参数

| 序号 | 寄存器起始地址 | 功能定义                          | 备注                                      |
| ---- | -------------- | --------------------------------- | ----------------------------------------- |
| 1    | 30H            | Model_id                          | 实际8位无符号，复位后为0xb4               |
| 2    | 31H            | Model_Rev_Major                   | 实际8位无符号，复位后为0x1，值有效范围0~7 |
| 3    | 32H            | Model_Rev_Minor                   | 实际8位无符号，复位后为0x3，值有效范围0~7 |
| 4    | 33H            | Module_Rev_Major                  | 实际8位无符号，复位后为0x1，值有效范围0~7 |
| 5    | 34H            | Module_Rev_Minor                  | 实际8位无符号，复位后为0x2，值有效范围0~7 |
| 6    | 35H            | Date_Hi                           | 实际8位无符号，高4位为年，低4位为月       |
| 7    | 36H            | Date_Lo                           | 实际8位无符号，高4位为日，低4位为脉冲数   |
| 8    | 37H            | Id_Time                           | 实际16位无符号，时间 = 寄存器值 *2        |
| 9    | 38H            | Mode_GPIO0                        | 实际8位无符号，复位后为0x60               |
| 10   | 39H            | Mode_GPIO1                        | 实际8位无符号，复位后为0x20               |
| 11   | 3AH            | History_Ctrl                      | 实际8位无符号，复位后为0x0                |
| 12   | 3BH            | Interrupt_Config_GPIO             | 实际8位无符号，复位后为0x0                |
| 13   | 3CH            | Interrupt_Clear                   | 实际8位无符号，复位后为0x0                |
| 14   | 3DH            | Fresh_Out_Of_Reset                | 实际8位无符号，复位后为0x1                |
| 15   | 3EH            | Grouped_Para_Hold                 | 实际8位无符号，复位后为0x0                |
| 16   | 3FH            | Range_start                       | 实际8位无符号，复位后为0x0                |
| 17   | 40H            | Range_Thresh_High                 | 实际8位无符号，复位后为0xFF               |
| 18   | 41H            | Range_Thresh_Low                  | 实际8位无符号，复位后为0x0                |
| 19   | 42H            | Range_InterMeasurement_Period     | 实际8位无符号，复位后为0xFF               |
| 20   | 43H            | Range_Max_ConverGence_Time        | 实际8位无符号，复位后为0x31               |
| 21   | 44H            | Range_CrossTalk_Compensation_Rate | 实际16位无符号，复位后为0x0               |
| 22   | 45H            | Range_CrossTalk_Valid_Height      | 实际8位无符号，复位后为0x14               |
| 23   | 46H            | Range_Early_ConverGence_Estimate  | 实际16位无符号，复位后为0x0               |
| 24   | 47H            | Range_Part_To_Part_Range_Offset   | 实际8位无符号，复位后为0xYY               |
| 25   | 48H            | Range_Ignore_Valid_Height         | 实际8位无符号，复位后为0x0                |
| 26   | 49H            | Range_Ingore_Threshold            | 实际16位无符号，复位后为0x0               |
| 27   | 4AH            | Range_Max_Ambient_Level_Mult      | 实际8位无符号，复位后为0xA0               |
| 28   | 4BH            | Range_Check_Enables               | 实际8位无符号，复位后为0x11               |
| 29   | 4CH            | Range_Vhv_RecalibRate             | 实际8位无符号，复位后为0x0                |
| 30   | 4DH            | Range_Vhv_Repeat_Rate             | 实际8位无符号，复位后为0x0                |
| 31   | 4EH            | Als_Start                         | 实际8位无符号，复位后为0x0                |
| 32   | 4FH            | Als_Thresh_High                   | 实际16位无符号，复位后为0xFFFF            |
| 33   | 50H            | Als_Thresh_Low                    | 实际16位无符号，复位后为0x0               |
| 34   | 51H            | Als_InterMeasurement_Period       | 实际8位无符号，复位后为0xFF               |
| 35   | 52H            | Als_Analogue_Gain                 | 实际8位无符号，复位后为0x06               |
| 36   | 53H            | Als_interRation_Period            | 实际16位无符号，复位后为0x0               |
| 37   | 54H            | Readout_Averaging_Sample_Period   | 实际8位无符号，复位后为0x30               |
| 38   | 55H            | Firmware_bootup                   | 实际8位无符号，复位后为0x1                |
| 39   | 56H            | Firmaware_Result_Scaler           | 实际8位无符号，复位后为0x1                |
| 40   | 57H            | I2C_Slave_Device_Adderss          | 实际8位无符号，复位后为0x29               |
| 41   | 58H            | InterLeaved_Mode_Enable           | 实际8位无符号，复位后为0x0                |
