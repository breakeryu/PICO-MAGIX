#include "vl6180x.h"

uint8_t _i2caddr = 0x29;



void VL6180x_StartDistanceMeasurement(void)
{
    uint8_t status = 0;
    // wait for device to be ready for range measurement
    do
    {
        VL6180x_ReadByte(VL6180X_RESULT_RANGE_STATUS,&status);
        status = status & 0x01;
    } while (!status);
    // Start a range measurement
    VL6180x_writeByte(VL6180X_SYSRANGE_START, 0x01); // Start Single shot mode

}

uint8_t VL6180x_Read_Distance(void)
{
    uint8_t data = 0;
    VL6180x_writeByte(VL6180X_SYSTEM_INTERRUPT_CLEAR, 0x07);
    VL6180x_ReadByte(VL6180X_RESULT_RANGE_VAL,&data);
    return data;
}



void VL6180x_HardInit(void)
{
    // private settings from page 24 of app note
    VL6180x_writeByte(0x0207, 0x01);
    VL6180x_writeByte(0x0208, 0x01);
    VL6180x_writeByte(0x0096, 0x00);
    VL6180x_writeByte(0x0097, 0xfd);
    VL6180x_writeByte(0x00e3, 0x00);
    VL6180x_writeByte(0x00e4, 0x04);
    VL6180x_writeByte(0x00e5, 0x02);
    VL6180x_writeByte(0x00e6, 0x01);
    VL6180x_writeByte(0x00e7, 0x03);
    VL6180x_writeByte(0x00f5, 0x02);
    VL6180x_writeByte(0x00d9, 0x05);
    VL6180x_writeByte(0x00db, 0xce);
    VL6180x_writeByte(0x00dc, 0x03);
    VL6180x_writeByte(0x00dd, 0xf8);
    VL6180x_writeByte(0x009f, 0x00);
    VL6180x_writeByte(0x00a3, 0x3c);
    VL6180x_writeByte(0x00b7, 0x00);
    VL6180x_writeByte(0x00bb, 0x3c);
    VL6180x_writeByte(0x00b2, 0x09);
    VL6180x_writeByte(0x00ca, 0x09);
    VL6180x_writeByte(0x0198, 0x01);
    VL6180x_writeByte(0x01b0, 0x17);
    VL6180x_writeByte(0x01ad, 0x00);
    VL6180x_writeByte(0x00ff, 0x05);
    VL6180x_writeByte(0x0100, 0x05);
    VL6180x_writeByte(0x0199, 0x05);
    VL6180x_writeByte(0x01a6, 0x1b);
    VL6180x_writeByte(0x01ac, 0x3e);
    VL6180x_writeByte(0x01a7, 0x1f);
    VL6180x_writeByte(0x0030, 0x00);

    // Recommended : Public registers - See data sheet for more detail
    VL6180x_writeByte(0x0011, 0x10);        // Enables polling for 'New Sample ready'
                                            // when measurement completes
    VL6180x_writeByte(0x010a, 0x30);        // Set the averaging sample period
                                            // (compromise between lower noise and
                                            // increased execution time)
    VL6180x_writeByte(0x003f, 0x46);        // Sets the light and dark gain (upper
                                            // nibble). Dark gain should not be
                                            // changed.
    VL6180x_writeByte(0x0031, 0xFF);        // sets the # of range measurements after
                                            // which auto calibration of system is
                                            // performed
    VL6180x_writeByte(0x0040, 0x63);        // Set ALS integration time to 100ms
    VL6180x_writeByte(0x002e, 0x01);        // perform a single temperature calibration
                                            // of the ranging sensor

    // Optional: Public registers - See data sheet for more detail
    VL6180x_writeByte(0x001b, 0x09);        // Set default ranging inter-measurement
                                            // period to 100ms
    VL6180x_writeByte(0x003e, 0x31);        // Set default ALS inter-measurement period
                                            // to 500ms
    VL6180x_writeByte(0x0014, 0x24);        // Configures interrupt on 'New Sample
                                            // Ready threshold event'
}



/***1. IDENTIFICATION***/
uint8_t VL6180x_Read_IDENTIFICATION__MODEL_ID(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_IDENTIFICATION_MODEL_ID,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__MODEL_ID(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_IDENTIFICATION_MODEL_ID,data);
}

uint8_t VL6180x_Read_IDENTIFICATION__MODEL_REV_MAJOR(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_IDENTIFICATION_MODEL_REV_MAJOR,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__MODEL_REV_MAJOR(uint8_t data)
{
    data = data & 0x7;
    return VL6180x_writeByte(VL6180X_IDENTIFICATION_MODEL_REV_MAJOR,data);
}

uint8_t VL6180x_Read_IDENTIFICATION__MODEL_REV_MINOR(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_IDENTIFICATION_MODEL_REV_MINOR,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__MODEL_REV_MINOR(uint8_t data)
{
    data = data & 0x7;
    return VL6180x_writeByte(VL6180X_IDENTIFICATION_MODEL_REV_MINOR,data);
}

uint8_t VL6180x_Read_IDENTIFICATION__MODULE_REV_MAJOR(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_IDENTIFICATION_MODULE_REV_MAJOR,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__MODULE_REV_MAJOR(uint8_t data)
{
    data = data & 0x7;
    return VL6180x_writeByte(VL6180X_IDENTIFICATION_MODULE_REV_MAJOR,data);
}

uint8_t VL6180x_Read_IDENTIFICATION__MODULE_REV_MINOR(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_IDENTIFICATION_MODULE_REV_MINOR,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__MODULE_REV_MINOR(uint8_t data)
{
    data = data & 0x7;
    return VL6180x_writeByte(VL6180X_IDENTIFICATION_MODULE_REV_MINOR,data);
}

uint16_t VL6180x_Read_IDENTIFICATION__DATE(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_IDENTIFICATION_DATE,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__DATE(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_IDENTIFICATION_DATE,data);
}

uint16_t VL6180x_Read_IDENTIFICATION__TIME(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_IDENTIFICATION_TIME,&data);
    return data;
}

int VL6180x_Set_IDENTIFICATION__TIME(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_IDENTIFICATION_TIME,data);
}

/***2. SYSTEM SETUP***/

uint8_t VL6180x_Read_SYSTEM__MODE_GPIO0(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_MODE_GPIO0,&data);
    return data;
}

int VL6180x_Set_SYSTEM__MODE_GPIO0(uint8_t data)
{
    data = data & 0x7e;
    return VL6180x_writeByte(VL6180X_SYSTEM_MODE_GPIO0,data);
}

uint8_t VL6180x_Read_SYSTEM__MODE_GPIO1(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_MODE_GPIO1,&data);
    return data;
}

int VL6180x_Set_SYSTEM__MODE_GPIO1(uint8_t data)
{
    data = data & 0x3e;
    return VL6180x_writeByte(VL6180X_SYSTEM_MODE_GPIO1,data);
}

uint8_t VL6180x_Read_SYSTEM__HISTORY_CTRL(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_HISTORY_CTRL,&data);
    return data;
}

int VL6180x_Set_SYSTEM__HISTORY_CTRL(uint8_t data)
{
    data = data & 0x7;
    return VL6180x_writeByte(VL6180X_SYSTEM_HISTORY_CTRL,data);
}

uint8_t VL6180x_Read_SYSTEM__INTERRUPT_CONFIG_GPIO(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO,&data);
    return data;
}

int VL6180x_Set_SYSTEM__INTERRUPT_CONFIG_GPIO(uint8_t data)
{
    data = data & 0x3F;
    return VL6180x_writeByte(VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO,data);
}

uint8_t VL6180x_Read_SYSTEM__INTERRUPT_CLEAR(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_INTERRUPT_CLEAR,&data);
    return data;
}

int VL6180x_Set_SYSTEM__INTERRUPT_CLEAR(uint8_t data)
{
    data = data & 0x7;
    return VL6180x_writeByte(VL6180X_SYSTEM_INTERRUPT_CLEAR,data);
}


uint8_t VL6180x_Read_SYSTEM__FRESH_OUT_OF_RESET(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_FRESH_OUT_OF_RESET,&data);
    return data;
}

int VL6180x_Set_SYSTEM__FRESH_OUT_OF_RESET(uint8_t data)
{
    data = data & 0x1;
    return VL6180x_writeByte(VL6180X_SYSTEM_FRESH_OUT_OF_RESET,data);
}

uint8_t VL6180x_Read_SYSTEM__GROUPED_PARAMETER_HOLD(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSTEM_GROUPED_PARAMETER_HOLD,&data);
    return data;
}

int VL6180x_Set_SYSTEM__GROUPED_PARAMETER_HOLD(uint8_t data)
{
    data = data & 0x1;
    return VL6180x_writeByte(VL6180X_SYSTEM_GROUPED_PARAMETER_HOLD,data);
}


/***3. RANGE SETUP ***/
uint8_t VL6180x_Read_SYSRANGE__START(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_START,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__START(uint8_t data)
{
    data = data & 0x3;
    return VL6180x_writeByte(VL6180X_SYSRANGE_START,data);
}

uint8_t VL6180x_Read_SYSRANGE__THRESH_HIGH(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_THRESH_HIGH,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__THRESH_HIGH(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_THRESH_HIGH,data);
}

uint8_t VL6180x_Read_SYSRANGE__THRESH_LOW(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_THRESH_LOW,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__THRESH_LOW(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_THRESH_LOW,data);
}

uint8_t VL6180x_Read_SYSRANGE__INTERMEASUREMENT_PERIOD(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__INTERMEASUREMENT_PERIOD(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD,data);
}

uint8_t VL6180x_Read_SYSRANGE__MAX_CONVERGENCE_TIME(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__MAX_CONVERGENCE_TIME(uint8_t data)
{
    data = data & 0x3f;
    return VL6180x_writeByte(VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME,data);
}

uint16_t VL6180x_Read_SYSRANGE__CROSSTALK_COMPENSATION_RATE(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_SYSRANGE_CROSSTALK_COMPENSATION_RATE,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__CROSSTALK_COMPENSATION_RATE(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_SYSRANGE_CROSSTALK_COMPENSATION_RATE,data);
}

uint8_t VL6180x_Read_SYSRANGE__CROSSTALK_VALID_HEIGHT(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_CROSSTALK_VALID_HEIGHT,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__CROSSTALK_VALID_HEIGHT(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_CROSSTALK_VALID_HEIGHT,data);
}

uint16_t VL6180x_Read_SYSRANGE__EARLY_CONVERGENCE_ESTIMATE(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__EARLY_CONVERGENCE_ESTIMATE(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE,data);
}

uint8_t VL6180x_Read_SYSRANGE__PART_TO_PART_RANGE_OFFSET(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_PART_TO_PART_RANGE_OFFSET,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__PART_TO_PART_RANGE_OFFSET(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_PART_TO_PART_RANGE_OFFSET,data);
}

uint8_t VL6180x_Read_SYSRANGE__RANGE_IGNORE_VALID_HEIGHT(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_RANGE_IGNORE_VALID_HEIGHT,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__RANGE_IGNORE_VALID_HEIGHT(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_RANGE_IGNORE_VALID_HEIGHT,data);
}

uint16_t VL6180x_Read_SYSRANGE__RANGE_IGNORE_THRESHOLD(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_SYSRANGE_RANGE_IGNORE_THRESHOLD,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__RANGE_IGNORE_THRESHOLD(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_SYSRANGE_RANGE_IGNORE_THRESHOLD,data);
}

uint8_t VL6180x_Read_SYSRANGE__MAX_AMBIENT_LEVEL_MULT(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_MAX_AMBIENT_LEVEL_MULT,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__MAX_AMBIENT_LEVEL_MULT(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_MAX_AMBIENT_LEVEL_MULT,data);
}


uint8_t VL6180x_Read_SYSRANGE__RANGE_CHECK_ENABLES(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_RANGE_CHECK_ENABLES,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__RANGE_CHECK_ENABLES(uint8_t data)
{
    data = data & 0x1b;
    return VL6180x_writeByte(VL6180X_SYSRANGE_RANGE_CHECK_ENABLES,data);
}

uint8_t VL6180x_Read_SYSRANGE__VHV_RECALIBRATE(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_VHV_RECALIBRATE,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__VHV_RECALIBRATE(uint8_t data)
{
    data = data & 0x3;
    return VL6180x_writeByte(VL6180X_SYSRANGE_VHV_RECALIBRATE,data);
}

uint8_t VL6180x_Read_SYSRANGE__VHV_REPEAT_RATE(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSRANGE_VHV_REPEAT_RATE,&data);
    return data;
}

int VL6180x_Set_SYSRANGE__VHV_REPEAT_RATE(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSRANGE_VHV_REPEAT_RATE,data);
}

/***4. ALS SETUP ***/

uint8_t VL6180x_Read_SYSALS__START(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSALS_START,&data);
    return data;
}

int VL6180x_Set_SYSALS__START(uint8_t data)
{
    data = data & 0x3;
    return VL6180x_writeByte(VL6180X_SYSALS_START,data);
}

uint16_t VL6180x_Read_SYSALS__THRESH_HIGH(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_SYSALS_THRESH_HIGH,&data);
    return data;
}

int VL6180x_Set_SYSALS__THRESH_HIGH(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_SYSALS_THRESH_HIGH,data);
}

uint16_t VL6180x_Read_SYSALS__THRESH_LOW(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_SYSALS_THRESH_LOW,&data);
    return data;
}

int VL6180x_Set_SYSALS__THRESH_LOW(uint16_t data)
{
    return VL6180x_writeWord(VL6180X_SYSALS_THRESH_LOW,data);
}

uint8_t VL6180x_Read_SYSALS__INTERMEASUREMENT_PERIOD(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSALS_INTERMEASUREMENT_PERIOD,&data);
    return data;
}

int VL6180x_Set_SYSALS__INTERMEASUREMENT_PERIOD(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_SYSALS_INTERMEASUREMENT_PERIOD,data);
}

uint8_t VL6180x_Read_SYSALS__ANALOGUE_GAIN(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_SYSALS_ANALOGUE_GAIN,&data);
    return data;
}

int VL6180x_Set_SYSALS__ANALOGUE_GAIN(uint8_t data)
{
    data = (data & 0x7) | 0x40;
    return VL6180x_writeByte(VL6180X_SYSALS_ANALOGUE_GAIN,data);
}

uint16_t VL6180x_Read_SYSALS__INTEGRATION_PERIOD(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_SYSALS_INTEGRATION_PERIOD,&data);
    return data;
}

int VL6180x_Set_SYSALS__INTEGRATION_PERIOD(uint16_t data)
{
    data = data & 0x1ff;
    return VL6180x_writeWord(VL6180X_SYSALS_INTEGRATION_PERIOD,data);
}

/***5. RESULTS ***/

uint8_t VL6180x_Read_RESULT__RANGE_STATUS(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_RESULT_RANGE_STATUS,&data);
    return data;
}

uint8_t VL6180x_Read_RESULT__ALS_STATUS(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_RESULT_ALS_STATUS,&data);
    return data;
}

uint8_t VL6180x_Read_RESULT__INTERRUPT_STATUS_GPIO(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_RESULT_INTERRUPT_STATUS_GPIO,&data);
    return data;
}


uint16_t VL6180x_Read_RESULT__ALS_VAL(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_RESULT_ALS_VAL,&data);
    return data;
}

uint16_t VL6180x_Read_RESULT__HISTORY_BUFFER_x(uint8_t bufferx)
{
    uint16_t data = 0;
    VL6180x_ReadWord((VL6180X_RESULT_HISTORY_BUFFER+bufferx*2),&data);
    return data;
}

uint8_t VL6180x_Read_RESULT__RANGE_VAL(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_RESULT_RANGE_VAL,&data);
    return data;
}

uint8_t VL6180x_Read_RESULT__RANGE_RAW(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_RESULT_RANGE_RAW,&data);
    return data;
}

uint16_t VL6180x_Read_RESULT__RANGE_RETURN_RATE(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_RESULT_RANGE_RETURN_RATE,&data);
    return data;
}

uint16_t VL6180x_Read_RESULT__RANGE_REFERENCE_RATE(void)
{
    uint16_t data = 0;
    VL6180x_ReadWord(VL6180X_RESULT_RANGE_REFERENCE_RATE,&data);
    return data;
}

uint32_t VL6180x_Read_RESULT__RANGE_RETURN_SIGNAL_COUNT(void)
{
    uint32_t data = 0;
    VL6180x_ReadDWord(VL6180X_RESULT_RANGE_RETURN_SIGNAL_COUNT,&data);
    return data;
}

uint32_t VL6180x_Read_RESULT__RANGE_REFERENCE_SIGNAL_COUNT(void)
{
    uint32_t data = 0;
    VL6180x_ReadDWord(VL6180X_RESULT_RANGE_REFERENCE_SIGNAL_COUNT,&data);
    return data;
}

uint32_t VL6180x_Read_RESULT__RANGE_RETURN_AMB_COUNT(void)
{
    uint32_t data = 0;
    VL6180x_ReadDWord(VL6180X_RESULT_RANGE_RETURN_AMB_COUNT,&data);
    return data;
}

uint32_t VL6180x_Read_RESULT__RANGE_REFERENCE_AMB_COUNT(void)
{
    uint32_t data = 0;
    VL6180x_ReadDWord(VL6180X_RESULT_RANGE_REFERENCE_AMB_COUNT,&data);
    return data;
}

uint32_t VL6180x_Read_RESULT__RANGE_RETURN_CONV_TIME(void)
{
    uint32_t data = 0;
    VL6180x_ReadDWord(VL6180X_RESULT_RANGE_RETURN_CONV_TIME,&data);
    return data;
}

uint32_t VL6180x_Read_RESULT__RANGE_REFERENCE_CONV_TIME(void)
{
    uint32_t data = 0;
    VL6180x_ReadDWord(VL6180X_RESULT_RANGE_REFERENCE_CONV_TIME,&data);
    return data;
}

/****** 6.other  ******/
uint8_t VL6180x_Read_READOUT__AVERAGING_SAMPLE_PERIOD(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD,&data);
    return data;
}

int VL6180x_Set_READOUT__AVERAGING_SAMPLE_PERIOD(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD,data);
}

uint8_t VL6180x_Read_FIRMWARE__BOOTUP(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_FIRMWARE_BOOTUP,&data);
    return data;
}

int VL6180x_Set_FIRMWARE__BOOTUP(uint8_t data)
{
    data = data & 0x1;
    return VL6180x_writeByte(VL6180X_FIRMWARE_BOOTUP,data);
}


uint8_t VL6180x_Read_FIRMWARE__RESULT_SCALER(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_FIRMWARE_RESULT_SCALER,&data);
    return data;
}

int VL6180x_Set_FIRMWARE__RESULT_SCALER(uint8_t data)
{
    data = data & 0xf;
    return VL6180x_writeByte(VL6180X_FIRMWARE_RESULT_SCALER,data);
}

uint8_t VL6180x_Read_I2C_SLAVE__DEVICE_ADDRESS(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_I2C_SLAVE_DEVICE_ADDRESS,&data);
    return data;
}

int VL6180x_Set_I2C_SLAVE__DEVICE_ADDRESS(uint8_t data)
{
    data = data & 0x7f;
    _i2caddr = data;
    return VL6180x_writeByte(VL6180X_I2C_SLAVE_DEVICE_ADDRESS,data);
}

uint8_t VL6180x_Read_INTERLEAVED_MODE__ENABLE(void)
{
    uint8_t data = 0;
    VL6180x_ReadByte(VL6180X_INTERLEAVED_MODE_ENABLE,&data);
    return data;
}

int VL6180x_Set_INTERLEAVED_MODE__ENABLE(uint8_t data)
{
    return VL6180x_writeByte(VL6180X_INTERLEAVED_MODE_ENABLE,data);
}


/*** iic lowel level functions ***/


/**
 * Read VL6180x single byte register
 * @param index The register index
 * @param data  pointer to 8 bit data
 * @return 0 on success
 */
int VL6180x_ReadByte(uint16_t index, uint8_t *data)
{

  Wire1.beginTransmission(_i2caddr);
  Wire1.write(index>>8);
  Wire1.write(index&0xFF);
  Wire1.endTransmission();

  Wire1.requestFrom(_i2caddr, (uint8_t)1);
  *data = Wire1.read();
  return 0;
  
}


/**
 * Read VL6180x word (2byte) register
 * @param index The register index
 * @param data  pointer to 16 bit data
 * @return 0 on success
 */
int VL6180x_ReadWord(uint16_t index, uint16_t *data)
{
    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.endTransmission();

    Wire1.requestFrom(_i2caddr, (uint8_t)2);
    *data = (uint16_t)Wire1.read()<<8;
    *data|= (uint16_t)Wire1.read();
    
    return 0;
}

/**
 * Read VL6180x dword (4byte) register
 * @param index The register index
 * @param data  pointer to 32 bit data
 * @return 0 on success
 */
int VL6180x_ReadDWord(uint16_t index, uint32_t *data)
{
    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.endTransmission();

    Wire1.requestFrom(_i2caddr, (uint8_t)4);
    *data = (uint16_t)Wire1.read()<<24;
    *data|= (uint16_t)Wire1.read()<<16;
    *data|= (uint16_t)Wire1.read()<<8;
    *data|= (uint16_t)Wire1.read();
    return 0;
}

/**
 * Read VL6180x multiple bytes
 * @note required only if #VL6180x_HAVE_MULTI_READ is set
 * @param index The register index
 * @param data  pointer to 8 bit data
 * @param nData number of data bytes to read
 * @return 0 on success
 */
int VL6180x_ReadMulti(uint16_t index, uint8_t *data, uint8_t nData)
{

    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.endTransmission();

    Wire1.requestFrom(_i2caddr, (uint8_t)nData);
    for (int i = 0; i < nData; i++)
    {
        *(data+i) |= Wire1.read();
    }
    
    return 0;
}

/**
 * Write VL6180x single byte register
 * @param index The register index
 * @param data  8 bit register data
 * @return 0 success
 */
int VL6180x_writeByte(uint16_t index, uint8_t data)
{
    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.write(data);  
    Wire1.endTransmission();
    return 0;
}

/**
 * Thread safe VL6180x Update (rd/modify/write) single byte register
 *
 * Final_reg = (Initial_reg & and_data) |or_data
 *
 * @param index The register index
 * @param AndData  8 bit and data
 * @param OrData   8 bit or data
 * @return 0 on success
 */
int VL6180x_UpdateByte(uint16_t index, uint8_t AndData, uint8_t OrData)
{
    uint8_t data;

    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);  
    Wire1.endTransmission();

    Wire1.requestFrom(_i2caddr, (uint8_t)1);
    data = Wire1.read();

    data = (data&AndData)|OrData;

    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.write(data);  
    Wire1.endTransmission();

    return 0;
}


/**
 * Write VL6180x word register
 * @param index The register index
 * @param data  16 bit register data
 * @return  0 on success
 */
int VL6180x_writeWord(uint16_t index, uint16_t data)
{
    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.write(data>>8);
    Wire1.write(data&0xFF);
    Wire1.endTransmission();
    return 0;
}


/**
 * Write VL6180x double word (4 byte) register
 * @param index The register index
 * @param data  32 bit register data
 * @return  0 on success
 */
int VL6180x_writeDWord(uint16_t index, uint32_t data)
{
    Wire1.beginTransmission(_i2caddr);
    Wire1.write(index>>8);
    Wire1.write(index&0xFF);
    Wire1.write(data>>24);
    Wire1.write((data>>16)&0xFF);
    Wire1.write((data>>8)&0xFF);
    Wire1.write(data&0xFF);
    Wire1.endTransmission();
    return 0;
}

