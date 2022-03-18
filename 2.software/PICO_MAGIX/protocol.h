#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <Arduino.h>
#include "src/modbus/mbconfig.h"
#include "src/modbus/noos_config.h"
#include "led.h"

#define MCUDRECEIVELENGTH 256    //接收数据的最大长度

/* 线圈指令对应地址 */

#define LED_STRIP_READ_SYS_STATUS               0x10
#define LED_STRIP_READ_THEATER_MODE_STATUS      0x11
#define LED_STRIP_READ_RAINBOW_MODE_STATUS      0x12
#define LED_STRIP_READ_TEST_MODE_STATUS         0x13

#define LED_STRIP_SET_SYS_OPEN                  0x100
#define LED_STRIP_SET_THEATER_MODE_OPEN         0x101
#define LED_STRIP_SET_RAINBOW_MODE_OPEN         0x102
#define LED_STRIP_SET_TEST_MODE_OPEN            0x103
#define VL_READ_RW_ENABLE                       0x104
#define VL_WRITE_RW_ENABLE                      0x105
#define VL_READ_RESULT_ENABLE                   0x106




/* 寄存器指令对应地址 */

#define SENSOR_READ_SYS_VOLTAGE                 0x0A
#define SENSOR_READ_GAS_DENSITY                 0x0B
#define SENSOR_READ_LIGHT_INTENSITY             0x0C
#define SENSOR_READ_TEMPERTURE                  0x0D
#define SENSOR_READ_HUMIDITY                    0x0E
#define SENSOR_READ_DISTANCE                    0x0F



/*  VL6180寄存器地址 */



#define VL_MODEL_ID                                     0x30 
#define VL_MODEL_REV_MAJOR                              0x31 
#define VL_MODEL_REV_MINOR                              0x32 
#define VL_MODULE_REV_MAJOR                             0x33 
#define VL_MODULE_REV_MINOR                             0x34 
#define VL_DATE_HI                                      0x35 
#define VL_DATE_LO                                      0x36 
#define VL_TIME                                         0x37 
#define VL_MODE_GPIO0                                   0x38 
#define VL_MODE_GPIO1                                   0x39 
#define VL_HISTORY_CTRL                                 0x3A 
#define VL_INTERRUPT_CONFIG_GPIO                        0x3B 
#define VL_INTERRUPT_CLEAR                              0x3C 
#define VL_FRESH_OUT_OF_RESET                           0x3D 
#define VL_GROUPED_PARAMETER_HOLD                       0x3E 
#define VL_RANGE_START                                  0x3F

#define VL_RANGE_THRESH_HIGH                            0x40 
#define VL_RANGE_THRESH_LOW                             0x41 
#define VL_RANGE_INTERMEASUREMENT_PERIOD                0x42 
#define VL_RANGE_MAX_CONVERGENCE_TIME                   0x43 
#define VL_RANGE_CROSSTALK_COMPENSATION_RATE            0x44 
#define VL_RANGE_CROSSTALK_VALID_HEIGHT                 0x45 
#define VL_RANGE_EARLY_CONVERGENCE_ESTIMATE             0x46 
#define VL_RANGE_PART_TO_PART_RANGE_OFFSET              0x47 
#define VL_RANGE_RANGE_IGNORE_VALID_HEIGHT              0x48 
#define VL_RANGE_RANGE_IGNORE_THRESHOLD                 0x49 
#define VL_RANGE_MAX_AMBIENT_LEVEL_MULT                 0x4A 
#define VL_RANGE_RANGE_CHECK_ENABLES                    0x4B 
#define VL_RANGE_VHV_RECALIBRATE                        0x4C 
#define VL_RANGE_VHV_REPEAT_RATE                        0x4D 
#define VL_ALS_START                                    0x4E 
#define VL_ALS_THRESH_HIGH                              0x4F

#define VL_ALS_THRESH_LOW                               0x50 
#define VL_ALS_INTERMEASUREMENT_PERIOD                  0x51 
#define VL_ALS_ANALOGUE_GAIN                            0x52 
#define VL_ALS_INTEGRATION_PERIOD                       0x53 
#define VL_READOUT__AVERAGING_SAMPLE_PERIOD             0x54 
#define VL_FIRMWARE__BOOTUP                             0x55 
#define VL_FIRMWARE__RESULT_SCALER                      0x56 
#define VL_I2C_SLAVE__DEVICE_ADDRESS                    0x57 
#define VL_INTERLEAVED_MODE__ENABLE                     0x58

#define VL_RESULT_RANGE_STATUS                          0x59 
#define VL_RESULT_ALS_STATUS                            0x5A 
#define VL_RESULT_INTERRUPT_STATUS_GPIO                 0x5B 
#define VL_RESULT_ALS_VAL                               0x5C 
#define VL_RESULT_HISTORY_BUFFER_0                      0x5D 
#define VL_RESULT_HISTORY_BUFFER_1                      0x5E 
#define VL_RESULT_HISTORY_BUFFER_2                      0x5F

#define VL_RESULT_HISTORY_BUFFER_3                      0x60 
#define VL_RESULT_HISTORY_BUFFER_4                      0x61 
#define VL_RESULT_HISTORY_BUFFER_5                      0x62 
#define VL_RESULT_HISTORY_BUFFER_6                      0x63 
#define VL_RESULT_HISTORY_BUFFER_7                      0x64 
#define VL_RESULT_RANGE_VAL                             0x65 
#define VL_RESULT_RANGE_RAW                             0x66 
#define VL_RESULT_RANGE_RETURN_RATE                     0x67 
#define VL_RESULT_RANGE_REFERENCE_RATE                  0x68 
#define VL_RESULT_RANGE_RETURN_SIGNAL_COUNT_H           0x69 
#define VL_RESULT_RANGE_RETURN_SIGNAL_COUNT_L           0x6A 
#define VL_RESULT_RANGE_REFERENCE_SIGNAL_COUNT_H        0x6B 
#define VL_RESULT_RANGE_REFERENCE_SIGNAL_COUNT_L        0x6C 
#define VL_RESULT_RANGE_RETURN_AMB_COUNT_H              0x6D 
#define VL_RESULT_RANGE_RETURN_AMB_COUNT_L              0x6E 
#define VL_RESULT_RANGE_REFERENCE_AMB_COUNT_H           0x6F

#define VL_RESULT_RANGE_REFERENCE_AMB_COUNT_L           0x70 
#define VL_RESULT_RANGE_RETURN_CONV_TIME_H              0x71 
#define VL_RESULT_RANGE_RETURN_CONV_TIME_L              0x72 
#define VL_RESULT_RANGE_REFERENCE_CONV_TIME_H           0x73 
#define VL_RESULT_RANGE_REFERENCE_CONV_TIME_L           0x74 


   



void slaveDataInit(void);
extern void modbusSlave_Init(void);
extern void deviceProcessCmd(void);
extern bool modbusSlave_poll(void);
extern void serialEvent1(void);


extern AnalogParaTypeDef aPara;
extern DigitalParaTypeDef dPara;

#endif  /* _PROTOCOL_H_ */
