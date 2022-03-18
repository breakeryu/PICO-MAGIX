#ifndef VL6180X_H_
#define VL6180X_H_

#include "Arduino.h"
#include <Wire.h>
#include "vl6180def.h"


void VL6180x_StartDistanceMeasurement(void);
uint8_t VL6180x_Read_Distance(void);
void VL6180x_HardInit(void);

/***1. IDENTIFICATION***/
uint8_t VL6180x_Read_IDENTIFICATION__MODEL_ID(void);
int VL6180x_Set_IDENTIFICATION__MODEL_ID(uint8_t id);

uint8_t VL6180x_Read_IDENTIFICATION__MODEL_REV_MAJOR(void);
int VL6180x_Set_IDENTIFICATION__MODEL_REV_MAJOR(uint8_t data);

uint8_t VL6180x_Read_IDENTIFICATION__MODEL_REV_MINOR(void);
int VL6180x_Set_IDENTIFICATION__MODEL_REV_MINOR(uint8_t data);

uint8_t VL6180x_Read_IDENTIFICATION__MODULE_REV_MAJOR(void);
int VL6180x_Set_IDENTIFICATION__MODULE_REV_MAJOR(uint8_t data);

uint8_t VL6180x_Read_IDENTIFICATION__MODULE_REV_MINOR(void);
int VL6180x_Set_IDENTIFICATION__MODULE_REV_MINOR(uint8_t data);

uint16_t VL6180x_Read_IDENTIFICATION__DATE(void);
int VL6180x_Set_IDENTIFICATION__DATE(uint16_t data);

uint16_t VL6180x_Read_IDENTIFICATION__TIME(void);
int VL6180x_Set_IDENTIFICATION__TIME(uint16_t data);

/***2. SYSTEM SETUP***/

uint8_t VL6180x_Read_SYSTEM__MODE_GPIO0(void);
int VL6180x_Set_SYSTEM__MODE_GPIO0(uint8_t data);

uint8_t VL6180x_Read_SYSTEM__MODE_GPIO1(void);
int VL6180x_Set_SYSTEM__MODE_GPIO1(uint8_t data);

uint8_t VL6180x_Read_SYSTEM__HISTORY_CTRL(void);
int VL6180x_Set_SYSTEM__HISTORY_CTRL(uint8_t data);

uint8_t VL6180x_Read_SYSTEM__INTERRUPT_CONFIG_GPIO(void);
int VL6180x_Set_SYSTEM__INTERRUPT_CONFIG_GPIO(uint8_t data);

uint8_t VL6180x_Read_SYSTEM__INTERRUPT_CLEAR(void);
int VL6180x_Set_SYSTEM__INTERRUPT_CLEAR(uint8_t data);

uint8_t VL6180x_Read_SYSTEM__FRESH_OUT_OF_RESET(void);
int VL6180x_Set_SYSTEM__FRESH_OUT_OF_RESET(uint8_t data);

uint8_t VL6180x_Read_SYSTEM__GROUPED_PARAMETER_HOLD(void);
int VL6180x_Set_SYSTEM__GROUPED_PARAMETER_HOLD(uint8_t data);


/***3. RANGE SETUP ***/
uint8_t VL6180x_Read_SYSRANGE__START(void);
int VL6180x_Set_SYSRANGE__START(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__THRESH_HIGH(void);
int VL6180x_Set_SYSRANGE__THRESH_HIGH(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__THRESH_LOW(void);
int VL6180x_Set_SYSRANGE__THRESH_LOW(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__INTERMEASUREMENT_PERIOD(void);
int VL6180x_Set_SYSRANGE__INTERMEASUREMENT_PERIOD(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__MAX_CONVERGENCE_TIME(void);
int VL6180x_Set_SYSRANGE__MAX_CONVERGENCE_TIME(uint8_t data);

uint16_t VL6180x_Read_SYSRANGE__CROSSTALK_COMPENSATION_RATE(void);
int VL6180x_Set_SYSRANGE__CROSSTALK_COMPENSATION_RATE(uint16_t data);

uint8_t VL6180x_Read_SYSRANGE__CROSSTALK_VALID_HEIGHT(void);
int VL6180x_Set_SYSRANGE__CROSSTALK_VALID_HEIGHT(uint8_t data);

uint16_t VL6180x_Read_SYSRANGE__EARLY_CONVERGENCE_ESTIMATE(void);
int VL6180x_Set_SYSRANGE__EARLY_CONVERGENCE_ESTIMATE(uint16_t data);

uint8_t VL6180x_Read_SYSRANGE__PART_TO_PART_RANGE_OFFSET(void);
int VL6180x_Set_SYSRANGE__PART_TO_PART_RANGE_OFFSET(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__RANGE_IGNORE_VALID_HEIGHT(void);
int VL6180x_Set_SYSRANGE__RANGE_IGNORE_VALID_HEIGHT(uint8_t data);

uint16_t VL6180x_Read_SYSRANGE__RANGE_IGNORE_THRESHOLD(void);
int VL6180x_Set_SYSRANGE__RANGE_IGNORE_THRESHOLD(uint16_t data);

uint8_t VL6180x_Read_SYSRANGE__MAX_AMBIENT_LEVEL_MULT(void);
int VL6180x_Set_SYSRANGE__MAX_AMBIENT_LEVEL_MULT(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__RANGE_CHECK_ENABLES(void);
int VL6180x_Set_SYSRANGE__RANGE_CHECK_ENABLES(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__VHV_RECALIBRATE(void);
int VL6180x_Set_SYSRANGE__VHV_RECALIBRATE(uint8_t data);

uint8_t VL6180x_Read_SYSRANGE__VHV_REPEAT_RATE(void);
int VL6180x_Set_SYSRANGE__VHV_REPEAT_RATE(uint8_t data);

/***4. ALS SETUP ***/
uint8_t VL6180x_Read_SYSALS__START(void);
int VL6180x_Set_SYSALS__START(uint8_t data);

uint16_t VL6180x_Read_SYSALS__THRESH_HIGH(void);
int VL6180x_Set_SYSALS__THRESH_HIGH(uint16_t data);

uint16_t VL6180x_Read_SYSALS__THRESH_LOW(void);
int VL6180x_Set_SYSALS__THRESH_LOW(uint16_t data);

uint8_t VL6180x_Read_SYSALS__INTERMEASUREMENT_PERIOD(void);
int VL6180x_Set_SYSALS__INTERMEASUREMENT_PERIOD(uint8_t data);

uint8_t VL6180x_Read_SYSALS__ANALOGUE_GAIN(void);
int VL6180x_Set_SYSALS__ANALOGUE_GAIN(uint8_t data);

uint16_t VL6180x_Read_SYSALS__INTEGRATION_PERIOD(void);
int VL6180x_Set_SYSALS__INTEGRATION_PERIOD(uint16_t data);

/***5. RESULTS ***/

uint8_t VL6180x_Read_RESULT__RANGE_STATUS(void);

uint8_t VL6180x_Read_RESULT__ALS_STATUS(void);

uint8_t VL6180x_Read_RESULT__INTERRUPT_STATUS_GPIO(void);

uint16_t VL6180x_Read_RESULT__ALS_VAL(void);

uint16_t VL6180x_Read_RESULT__HISTORY_BUFFER_x(uint8_t bufferx);

uint8_t VL6180x_Read_RESULT__RANGE_VAL(void);

uint8_t VL6180x_Read_RESULT__RANGE_RAW(void);

uint16_t VL6180x_Read_RESULT__RANGE_RETURN_RATE(void);

uint16_t VL6180x_Read_RESULT__RANGE_REFERENCE_RATE(void);

uint32_t VL6180x_Read_RESULT__RANGE_RETURN_SIGNAL_COUNT(void);

uint32_t VL6180x_Read_RESULT__RANGE_REFERENCE_SIGNAL_COUNT(void);

uint32_t VL6180x_Read_RESULT__RANGE_RETURN_AMB_COUNT(void);

uint32_t VL6180x_Read_RESULT__RANGE_REFERENCE_AMB_COUNT(void);

uint32_t VL6180x_Read_RESULT__RANGE_RETURN_CONV_TIME(void);

uint32_t VL6180x_Read_RESULT__RANGE_REFERENCE_CONV_TIME(void);

/****** 6.other  ******/

uint8_t VL6180x_Read_READOUT__AVERAGING_SAMPLE_PERIOD(void);
int VL6180x_Set_READOUT__AVERAGING_SAMPLE_PERIOD(uint8_t data);

uint8_t VL6180x_Read_FIRMWARE__BOOTUP(void);
int VL6180x_Set_FIRMWARE__BOOTUP(uint8_t data);

uint8_t VL6180x_Read_FIRMWARE__RESULT_SCALER(void);
int VL6180x_Set_FIRMWARE__RESULT_SCALER(uint8_t data);

uint8_t VL6180x_Read_I2C_SLAVE__DEVICE_ADDRESS(void);
int VL6180x_Set_I2C_SLAVE__DEVICE_ADDRESS(uint8_t data);

uint8_t VL6180x_Read_INTERLEAVED_MODE__ENABLE(void);
int VL6180x_Set_INTERLEAVED_MODE__ENABLE(uint8_t data);




/*** iic lowel level functions ***/
int VL6180x_ReadByte(uint16_t index, uint8_t *data);
int VL6180x_ReadWord(uint16_t index, uint16_t *data);
int VL6180x_ReadDWord(uint16_t index, uint32_t *data);
int VL6180x_ReadMulti(uint16_t index, uint8_t *data, uint8_t nData);
int VL6180x_writeByte(uint16_t index, uint8_t data);
int VL6180x_UpdateByte(uint16_t index, uint8_t AndData, uint8_t OrData);
int VL6180x_writeWord(uint16_t index, uint16_t data);
int VL6180x_writeDWord(uint16_t index, uint32_t data);


extern uint8_t _i2caddr;
#endif

