#include "sensor.h"

ANALOG_SENSOR_TYPE _sensorType;
struct repeating_timer timer;
AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR); //命名使用的AHT类


void SensorSysInitAllSensor(void){
  GasSensorInit();
  SysVoltageSensorInit();
  lightSensorInit();
  AhtSensorInit();
  vl6180x_Init();
  //启动定时器
  add_repeating_timer_ms(-100, ReadAllSensorsDate, NULL, &timer);
}



bool ReadAllSensorsDate(struct repeating_timer *t){
  static uint8_t times = 0;
  times++;
  if(times%2 == 1){
    Vl6180_Start_Range_Measurement();
  }else{
    Vl6180_Read_RangeData();
  }

  if(times >= 9){
    times = 0;
    ReadGasSensor();
    ReadVoltageSensor();
    ReadLightSensor();
    AhtTestUnit();
    Run_Vl6180_RW_RegisterMode();
  }
  // vl6180x_TestUnit();
  return true;
}

void sensor_update_Humidity(float humidity){
  uint16_t date = uint16_t(humidity * 100);
  sensor_WriteSingleHoldingRegister(SENSOR_READ_HUMIDITY,date);
}

void sensor_update_Temperture(float temperture){
  uint16_t date = uint16_t(temperture * 100);
  sensor_WriteSingleHoldingRegister(SENSOR_READ_TEMPERTURE,date);
}

void sensor_update_Distance(uint16_t distance){
  sensor_WriteSingleHoldingRegister(SENSOR_READ_DISTANCE,distance);
}


void sensor_update_SysVoltage(float voltage){
  uint16_t date = uint16_t(voltage * 1000);
  sensor_WriteSingleHoldingRegister(SENSOR_READ_SYS_VOLTAGE,date);
}

void sensor_update_gasDensity(uint16_t desity){
  sensor_WriteSingleHoldingRegister(SENSOR_READ_GAS_DENSITY,desity);
}

void sensor_update_lightIntensity(uint16_t intensity){
  sensor_WriteSingleHoldingRegister(SENSOR_READ_LIGHT_INTENSITY,intensity);
}

void sensor_WriteSingleHoldingRegister(uint16_t address,uint16_t date){
  SetSingleRegister(address,date);
}



/*************AHT21 sensor*********************/

/*******************************************
 * AHT温湿度传感器部分
 *******************************************/
float temperature = 0;
float humidity  = 0;
/*
 *函数功能：初始化AHT传感器 
 * 
 */
void AhtSensorInit(void){
  temperature = 0;
  humidity = 0;
  while (aht20.begin() != true)
  {

  }

  tft.drawString("temperature:", 0, 48, MYFONT);
  tft.fillRect(72,48,40,8,TFT_BLACK);
  tft.drawFloat(0.0, 2, 72, 48,MYFONT);
  tft.drawString("C", 110, 48, MYFONT);

  tft.drawString("humidity:", 0, 64, MYFONT);
  tft.fillRect(72,64,40,8,TFT_BLACK);
  tft.drawFloat(0.0, 2, 72, 64,MYFONT);
  tft.drawString("%RH", 110, 64, MYFONT);
}


/*
 *函数功能：测试AHT传感器函数
 * 
 */
void AhtTestUnit(void){
  
  temperature = aht20.readTemperature(); //read 6-bytes via I2C, takes 80 milliseconds
  humidity = aht20.readHumidity(AHTXX_USE_READ_DATA); //use 6-bytes from temperature reading, takes zero milliseconds!!!
  sensor_update_Humidity(humidity);
  sensor_update_Temperture(temperature);
  tft.drawString("temperature:", 0, 48, MYFONT);
  tft.fillRect(72,48,40,8,TFT_BLACK);
  tft.drawFloat(temperature, 2, 72, 48,MYFONT);
  tft.drawString("C", 110, 48, MYFONT);

  tft.drawString("humidity:", 0, 64, MYFONT);
  tft.fillRect(72,64,40,8,TFT_BLACK);
  tft.drawFloat(humidity, 2, 72, 64,MYFONT);
  tft.drawString("%RH", 110, 64, MYFONT);
}



/*******************************************
 * VL6180x距离传感器部分
 *******************************************/


void vl6180x_Init(void){
  Wire1.setSDA(PIN_ALX_SDA);
  Wire1.setSCL(PIN_ALX_SCL);
  Wire1.begin();
  VL6180x_HardInit();
}


void Vl6180_Start_Range_Measurement(void)
{
  VL6180x_StartDistanceMeasurement();
}

void Vl6180_Read_RangeData(void)
{
  uint8_t range = 0;
  range = VL6180x_Read_Distance();
  sensor_update_Distance(range);
  tft.drawString("distance:", 0, 80, MYFONT);
  tft.fillRect(72,80,40,8,TFT_BLACK);
  tft.drawNumber(range, 90, 80, MYFONT);
  tft.drawString("mm", 110, 80, MYFONT);
}

void Run_Vl6180_RW_RegisterMode(void)
{

  if(VL6180x_RW_IsReadEnable())
  {
    VL6180x_ReadAll_RW_Registers();
    dPara.coil[VL_READ_RW_ENABLE] = 0;
  }

  if(VL6180x_RW_IsWriteEnable())
  {
    VL6180x_WriteAll_RW_Registers();
    dPara.coil[VL_WRITE_RW_ENABLE] = 0;
  }

  if(VL6180x_R_IsReadResultEnable()){
    VL6180x_ReadOnly_R_Registers();
    dPara.coil[VL_READ_RESULT_ENABLE] = 0;
  }

}


bool VL6180x_RW_IsReadEnable(void)
{

    if (dPara.coil[VL_READ_RW_ENABLE])
    {
        return 1;
    }else{
        return 0;
    }
    
}


bool VL6180x_RW_IsWriteEnable(void)
{
    
    if (dPara.coil[VL_WRITE_RW_ENABLE])
    {
        return 1;
    }else{
        return 0;
    }
    
}

bool VL6180x_R_IsReadResultEnable(void)
{
    
    if (dPara.coil[VL_READ_RESULT_ENABLE])
    {
        return 1;
    }else{
        return 0;
    }
    
}


void VL6180x_ReadOnly_R_Registers(void)
{

  uint32_t data = 0;
  aPara.holdingRegister[VL_RESULT_RANGE_STATUS] = VL6180x_Read_RESULT__RANGE_STATUS();
  aPara.holdingRegister[VL_RESULT_ALS_STATUS] = VL6180x_Read_RESULT__ALS_STATUS();
  aPara.holdingRegister[VL_RESULT_INTERRUPT_STATUS_GPIO] = VL6180x_Read_RESULT__INTERRUPT_STATUS_GPIO();
  aPara.holdingRegister[VL_RESULT_ALS_VAL] = VL6180x_Read_RESULT__ALS_VAL();
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_0] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(0);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_1] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(1);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_2] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(2);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_3] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(3);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_4] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(4);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_5] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(5);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_6] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(6);
  aPara.holdingRegister[VL_RESULT_HISTORY_BUFFER_7] = VL6180x_Read_RESULT__HISTORY_BUFFER_x(7);
  aPara.holdingRegister[VL_RESULT_RANGE_VAL] = VL6180x_Read_RESULT__RANGE_VAL();
  aPara.holdingRegister[VL_RESULT_RANGE_RAW] = VL6180x_Read_RESULT__RANGE_RAW();
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_RATE] = VL6180x_Read_RESULT__RANGE_RETURN_RATE();
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_RATE] = VL6180x_Read_RESULT__RANGE_REFERENCE_RATE();
  data = VL6180x_Read_RESULT__RANGE_RETURN_SIGNAL_COUNT();
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_SIGNAL_COUNT_H] = data>>16;
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_SIGNAL_COUNT_L] = data&0xffff;
  data = VL6180x_Read_RESULT__RANGE_REFERENCE_SIGNAL_COUNT();
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_SIGNAL_COUNT_H] = data>>16;
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_SIGNAL_COUNT_L] = data&0xffff;
  data = VL6180x_Read_RESULT__RANGE_RETURN_AMB_COUNT();
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_AMB_COUNT_H] = data>>16;
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_AMB_COUNT_L] = data&0xffff;
  data = VL6180x_Read_RESULT__RANGE_REFERENCE_AMB_COUNT();
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_AMB_COUNT_H] = data>>16;
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_AMB_COUNT_L] = data&0xffff;
  data = VL6180x_Read_RESULT__RANGE_RETURN_CONV_TIME();
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_CONV_TIME_H] = data>>16;
  aPara.holdingRegister[VL_RESULT_RANGE_RETURN_CONV_TIME_L] = data&0xffff;
  data = VL6180x_Read_RESULT__RANGE_REFERENCE_CONV_TIME();
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_CONV_TIME_H] = data>>16;
  aPara.holdingRegister[VL_RESULT_RANGE_REFERENCE_CONV_TIME_L] = data&0xffff;


}


void VL6180x_ReadAll_RW_Registers(void)
{
    
    aPara.holdingRegister[      VL_MODEL_ID                           ] = VL6180x_Read_IDENTIFICATION__MODEL_ID();
    aPara.holdingRegister[      VL_MODEL_REV_MAJOR                    ] = VL6180x_Read_IDENTIFICATION__MODEL_REV_MAJOR();
    aPara.holdingRegister[      VL_MODEL_REV_MINOR                    ] = VL6180x_Read_IDENTIFICATION__MODEL_REV_MINOR();
    aPara.holdingRegister[      VL_MODULE_REV_MAJOR                   ] = VL6180x_Read_IDENTIFICATION__MODULE_REV_MAJOR();
    aPara.holdingRegister[      VL_MODULE_REV_MINOR                   ] = VL6180x_Read_IDENTIFICATION__MODULE_REV_MINOR();
    aPara.holdingRegister[      VL_DATE_HI                            ] = VL6180x_Read_IDENTIFICATION__DATE() >> 8;
    aPara.holdingRegister[      VL_DATE_LO                            ] = VL6180x_Read_IDENTIFICATION__DATE() & 0xff;
    aPara.holdingRegister[      VL_TIME                               ] = VL6180x_Read_IDENTIFICATION__TIME();
    aPara.holdingRegister[      VL_MODE_GPIO0                         ] = VL6180x_Read_SYSTEM__MODE_GPIO0();
    aPara.holdingRegister[      VL_MODE_GPIO1                         ] = VL6180x_Read_SYSTEM__MODE_GPIO1();
    aPara.holdingRegister[      VL_HISTORY_CTRL                       ] = VL6180x_Read_SYSTEM__HISTORY_CTRL();
    aPara.holdingRegister[      VL_INTERRUPT_CONFIG_GPIO              ] = VL6180x_Read_SYSTEM__INTERRUPT_CONFIG_GPIO();
    aPara.holdingRegister[      VL_INTERRUPT_CLEAR                    ] = VL6180x_Read_SYSTEM__INTERRUPT_CLEAR();
    aPara.holdingRegister[      VL_FRESH_OUT_OF_RESET                 ] = VL6180x_Read_SYSTEM__FRESH_OUT_OF_RESET();
    aPara.holdingRegister[      VL_GROUPED_PARAMETER_HOLD             ] = VL6180x_Read_SYSTEM__GROUPED_PARAMETER_HOLD();
    aPara.holdingRegister[      VL_RANGE_START                        ] = VL6180x_Read_SYSRANGE__START();
    
    aPara.holdingRegister[      VL_RANGE_THRESH_HIGH                  ] = VL6180x_Read_SYSRANGE__THRESH_HIGH();
    aPara.holdingRegister[      VL_RANGE_THRESH_LOW                   ] = VL6180x_Read_SYSRANGE__THRESH_LOW();
    aPara.holdingRegister[      VL_RANGE_INTERMEASUREMENT_PERIOD      ] = VL6180x_Read_SYSRANGE__INTERMEASUREMENT_PERIOD();
    aPara.holdingRegister[      VL_RANGE_MAX_CONVERGENCE_TIME         ] = VL6180x_Read_SYSRANGE__MAX_CONVERGENCE_TIME();
    aPara.holdingRegister[      VL_RANGE_CROSSTALK_COMPENSATION_RATE  ] = VL6180x_Read_SYSRANGE__CROSSTALK_COMPENSATION_RATE();
    aPara.holdingRegister[      VL_RANGE_CROSSTALK_VALID_HEIGHT       ] = VL6180x_Read_SYSRANGE__CROSSTALK_VALID_HEIGHT();
    aPara.holdingRegister[      VL_RANGE_EARLY_CONVERGENCE_ESTIMATE   ] = VL6180x_Read_SYSRANGE__EARLY_CONVERGENCE_ESTIMATE();
    aPara.holdingRegister[      VL_RANGE_PART_TO_PART_RANGE_OFFSET    ] = VL6180x_Read_SYSRANGE__PART_TO_PART_RANGE_OFFSET();
    aPara.holdingRegister[      VL_RANGE_RANGE_IGNORE_VALID_HEIGHT    ] = VL6180x_Read_SYSRANGE__RANGE_IGNORE_VALID_HEIGHT();
    aPara.holdingRegister[      VL_RANGE_RANGE_IGNORE_THRESHOLD       ] = VL6180x_Read_SYSRANGE__RANGE_IGNORE_THRESHOLD();
    aPara.holdingRegister[      VL_RANGE_MAX_AMBIENT_LEVEL_MULT       ] = VL6180x_Read_SYSRANGE__MAX_AMBIENT_LEVEL_MULT();
    aPara.holdingRegister[      VL_RANGE_RANGE_CHECK_ENABLES          ] = VL6180x_Read_SYSRANGE__RANGE_CHECK_ENABLES();
    aPara.holdingRegister[      VL_RANGE_VHV_RECALIBRATE              ] = VL6180x_Read_SYSRANGE__VHV_RECALIBRATE();
    aPara.holdingRegister[      VL_RANGE_VHV_REPEAT_RATE              ] = VL6180x_Read_SYSRANGE__VHV_REPEAT_RATE();
    aPara.holdingRegister[      VL_ALS_START                          ] = VL6180x_Read_SYSALS__START();
    aPara.holdingRegister[      VL_ALS_THRESH_HIGH                    ] = VL6180x_Read_SYSALS__THRESH_HIGH();
    
    aPara.holdingRegister[      VL_ALS_THRESH_LOW                     ] = VL6180x_Read_SYSALS__THRESH_LOW();
    aPara.holdingRegister[      VL_ALS_INTERMEASUREMENT_PERIOD        ] = VL6180x_Read_SYSALS__INTERMEASUREMENT_PERIOD();
    aPara.holdingRegister[      VL_ALS_ANALOGUE_GAIN                  ] = VL6180x_Read_SYSALS__ANALOGUE_GAIN();
    aPara.holdingRegister[      VL_ALS_INTEGRATION_PERIOD             ] = VL6180x_Read_SYSALS__INTEGRATION_PERIOD();
    aPara.holdingRegister[      VL_READOUT__AVERAGING_SAMPLE_PERIOD   ] = VL6180x_Read_READOUT__AVERAGING_SAMPLE_PERIOD();
    aPara.holdingRegister[      VL_FIRMWARE__BOOTUP                   ] = VL6180x_Read_FIRMWARE__BOOTUP();
    aPara.holdingRegister[      VL_FIRMWARE__RESULT_SCALER            ] = VL6180x_Read_FIRMWARE__RESULT_SCALER();
    aPara.holdingRegister[      VL_I2C_SLAVE__DEVICE_ADDRESS          ] = VL6180x_Read_I2C_SLAVE__DEVICE_ADDRESS();
    aPara.holdingRegister[      VL_INTERLEAVED_MODE__ENABLE           ] = VL6180x_Read_INTERLEAVED_MODE__ENABLE();
    

}

void VL6180x_WriteAll_RW_Registers(void)
{
    
    VL6180x_Set_IDENTIFICATION__MODEL_ID(aPara.holdingRegister[VL_MODEL_ID]);
    VL6180x_Set_IDENTIFICATION__MODEL_REV_MAJOR(aPara.holdingRegister[VL_MODEL_REV_MAJOR]);
    VL6180x_Set_IDENTIFICATION__MODEL_REV_MINOR(aPara.holdingRegister[VL_MODEL_REV_MINOR]);
    VL6180x_Set_IDENTIFICATION__MODULE_REV_MAJOR(aPara.holdingRegister[VL_MODULE_REV_MAJOR]);
    VL6180x_Set_IDENTIFICATION__MODULE_REV_MINOR(aPara.holdingRegister[VL_MODULE_REV_MINOR]);
    VL6180x_Set_IDENTIFICATION__DATE(aPara.holdingRegister[VL_DATE_HI]<<8+aPara.holdingRegister[VL_DATE_LO]);
    VL6180x_Set_IDENTIFICATION__TIME(aPara.holdingRegister[VL_TIME]);
    VL6180x_Set_SYSTEM__MODE_GPIO0(aPara.holdingRegister[VL_MODE_GPIO0]);
    VL6180x_Set_SYSTEM__MODE_GPIO1(aPara.holdingRegister[VL_MODE_GPIO1]);
    VL6180x_Set_SYSTEM__HISTORY_CTRL(aPara.holdingRegister[VL_HISTORY_CTRL]);
    VL6180x_Set_SYSTEM__INTERRUPT_CONFIG_GPIO(aPara.holdingRegister[VL_INTERRUPT_CONFIG_GPIO]);
    VL6180x_Set_SYSTEM__INTERRUPT_CLEAR(aPara.holdingRegister[VL_INTERRUPT_CLEAR]);
    VL6180x_Set_SYSTEM__FRESH_OUT_OF_RESET(aPara.holdingRegister[VL_FRESH_OUT_OF_RESET]);
    VL6180x_Set_SYSTEM__GROUPED_PARAMETER_HOLD(aPara.holdingRegister[VL_GROUPED_PARAMETER_HOLD]);
    VL6180x_Set_SYSRANGE__START(aPara.holdingRegister[VL_RANGE_START]);

    VL6180x_Set_SYSRANGE__THRESH_HIGH(aPara.holdingRegister[VL_RANGE_THRESH_HIGH]);
    VL6180x_Set_SYSRANGE__THRESH_LOW(aPara.holdingRegister[VL_RANGE_THRESH_LOW]);
    VL6180x_Set_SYSRANGE__INTERMEASUREMENT_PERIOD(aPara.holdingRegister[VL_RANGE_INTERMEASUREMENT_PERIOD]);
    VL6180x_Set_SYSRANGE__MAX_CONVERGENCE_TIME(aPara.holdingRegister[VL_RANGE_MAX_CONVERGENCE_TIME]);
    VL6180x_Set_SYSRANGE__CROSSTALK_COMPENSATION_RATE(aPara.holdingRegister[VL_RANGE_CROSSTALK_COMPENSATION_RATE]);
    VL6180x_Set_SYSRANGE__CROSSTALK_VALID_HEIGHT(aPara.holdingRegister[VL_RANGE_CROSSTALK_VALID_HEIGHT]);
    VL6180x_Set_SYSRANGE__EARLY_CONVERGENCE_ESTIMATE(aPara.holdingRegister[VL_RANGE_EARLY_CONVERGENCE_ESTIMATE]);
    VL6180x_Set_SYSRANGE__PART_TO_PART_RANGE_OFFSET(aPara.holdingRegister[VL_RANGE_PART_TO_PART_RANGE_OFFSET]);
    VL6180x_Set_SYSRANGE__RANGE_IGNORE_VALID_HEIGHT(aPara.holdingRegister[VL_RANGE_RANGE_IGNORE_VALID_HEIGHT]);
    VL6180x_Set_SYSRANGE__RANGE_IGNORE_THRESHOLD(aPara.holdingRegister[VL_RANGE_RANGE_IGNORE_THRESHOLD]);
    VL6180x_Set_SYSRANGE__MAX_AMBIENT_LEVEL_MULT(aPara.holdingRegister[VL_RANGE_MAX_AMBIENT_LEVEL_MULT]);
    VL6180x_Set_SYSRANGE__RANGE_CHECK_ENABLES(aPara.holdingRegister[VL_RANGE_RANGE_CHECK_ENABLES]);
    VL6180x_Set_SYSRANGE__VHV_RECALIBRATE(aPara.holdingRegister[VL_RANGE_VHV_RECALIBRATE]);
    VL6180x_Set_SYSRANGE__VHV_REPEAT_RATE(aPara.holdingRegister[VL_RANGE_VHV_REPEAT_RATE]);
    VL6180x_Set_SYSALS__START(aPara.holdingRegister[VL_ALS_START]);
    VL6180x_Set_SYSALS__THRESH_HIGH(aPara.holdingRegister[VL_ALS_THRESH_HIGH]);

    VL6180x_Set_SYSALS__THRESH_LOW(aPara.holdingRegister[VL_ALS_THRESH_LOW]);
    VL6180x_Set_SYSALS__INTERMEASUREMENT_PERIOD(aPara.holdingRegister[VL_ALS_INTERMEASUREMENT_PERIOD]);
    VL6180x_Set_SYSALS__ANALOGUE_GAIN(aPara.holdingRegister[VL_ALS_ANALOGUE_GAIN]);
    VL6180x_Set_SYSALS__INTEGRATION_PERIOD(aPara.holdingRegister[VL_ALS_INTEGRATION_PERIOD]);
    VL6180x_Set_READOUT__AVERAGING_SAMPLE_PERIOD(aPara.holdingRegister[VL_READOUT__AVERAGING_SAMPLE_PERIOD]);
    VL6180x_Set_FIRMWARE__BOOTUP(aPara.holdingRegister[VL_FIRMWARE__BOOTUP]);
    VL6180x_Set_FIRMWARE__RESULT_SCALER(aPara.holdingRegister[VL_FIRMWARE__RESULT_SCALER]);
    VL6180x_Set_I2C_SLAVE__DEVICE_ADDRESS(aPara.holdingRegister[VL_I2C_SLAVE__DEVICE_ADDRESS]);
    VL6180x_Set_INTERLEAVED_MODE__ENABLE(aPara.holdingRegister[VL_INTERLEAVED_MODE__ENABLE]);

    
}










/*************Gas density sensor**************/

void GasSensorInit(void){
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Gas Sensor:", 0, 0, MYFONT);
  tft.drawString("0", 90, 0, MYFONT);
  
}


void ReadGasSensor(void){
  _sensorType = T_GAS;
  uint16_t gasValue = (uint16_t)ReadAnalogSensorType(_sensorType);
  sensor_update_gasDensity(gasValue);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Gas Sensor:", 0, 0, MYFONT);
  tft.fillRect(90,0,80,8,TFT_BLACK);
  tft.drawNumber(gasValue, 90, 0, MYFONT);
}


/*************SYS Voltage sensor**************/

void SysVoltageSensorInit(void){
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Voltage :", 0, 16, MYFONT);
  tft.drawString("0", 70, 16, MYFONT);
  tft.drawString("V", 110, 16, MYFONT);
}


void ReadVoltageSensor(void){
  _sensorType = T_VSYS;
  float sysVoltage;
  int vlotageValue = ReadAnalogSensorType(_sensorType);
  float volts = vlotageValue * 3.3 / 4095.0;
  sysVoltage = volts * 3.0;
  sensor_update_SysVoltage(sysVoltage);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Voltage :", 0, 16, MYFONT);
  tft.fillRect(70,16,30,8,TFT_BLACK);
  tft.drawFloat(sysVoltage, 2, 70, 16,MYFONT);
  tft.drawString("V", 110, 16, MYFONT);
  
}

/*************Light sensor**************/

void lightSensorInit(void){
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Light Sensor:", 0, 32, MYFONT);
  tft.drawString("0", 98, 32, MYFONT);
  
}


void ReadLightSensor(void){
  _sensorType = T_LIGHT;
  uint16_t lightValue = (uint16_t)ReadAnalogSensorType(_sensorType);
  sensor_update_lightIntensity(lightValue);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Light Sensor:", 0, 32, MYFONT);
  tft.fillRect(98,32,128,8,TFT_BLACK);
  tft.drawNumber(lightValue, 98, 32, MYFONT);
}



int ReadAnalogSensorType(ANALOG_SENSOR_TYPE mysensor){

  int _pin = 0;
  int value;
  
  switch(mysensor){
    case T_LIGHT:
      _pin = PIN_LIGHT_SENSOR;
    break;
    
    case T_GAS:
      _pin = PIN_GAS_SENSOR;
    break;
    
    case T_VSYS:
      _pin = PIN_VSYS;
    break;
  }
  
  value = Filter(_pin);
  
  return value;
  
}


/*
*滤波函数
*/
int Filter(int Pin) {
  int i;
  int filter_sum = 0;
  int filter_max, filter_min;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = analogRead(Pin);
    delay(1);
  }
  filter_max = filter_buf[0];
  filter_min = filter_buf[0];
  filter_sum = filter_buf[0];
  for(i = FILTER_N - 1; i > 0; i--) {
    if(filter_buf[i] > filter_max)
      filter_max=filter_buf[i];
    else if(filter_buf[i] < filter_min)
      filter_min=filter_buf[i];
    filter_sum = filter_sum + filter_buf[i];
    filter_buf[i] = filter_buf[i - 1];
  }
  i = FILTER_N - 2;
  filter_sum = filter_sum - filter_max - filter_min + i / 2; // +i/2 的目的是为了四舍五入
  filter_sum = filter_sum / i;
  return filter_sum;
}


