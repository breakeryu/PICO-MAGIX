#include "sensor.h"


AHTxx aht20(AHTXX_ADDRESS_X38, AHT2x_SENSOR); //命名使用的AHT类

MQ135 mq135_sensor = MQ135(PIN_GAS_SENSOR);


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
//    Serial.println(F("AHT2x not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
//    delay(5000);
  }
//  Serial.println(F("AHT20 OK"));
}


/*
 *函数功能：测试AHT传感器函数
 * 
 */
void AhtTestUnit(void){
  
  temperature = aht20.readTemperature(); //read 6-bytes via I2C, takes 80 milliseconds

  Serial.print(F("Temperature: "));
  
  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    Serial.print(temperature);
    Serial.println(F(" +-0.3C"));
  }
  else
  {
    printStatus(); //print temperature command status
  }

  humidity = aht20.readHumidity(AHTXX_USE_READ_DATA); //use 6-bytes from temperature reading, takes zero milliseconds!!!

  Serial.print(F("Humidity...: "));
  
  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    Serial.print(humidity);
    Serial.println(F(" +-2%"));
  }
  else
  {
    printStatus(); //print temperature command status not humidity!!! RH measurement use same 6-bytes from T measurement
  }
  
}

/**************************************************************************/
/*
    printStatus()
    Print last command status
*/
/**************************************************************************/
void printStatus()
{
  switch (aht20.getStatus())
  {
    case AHTXX_NO_ERROR:
      Serial.println(F("no error"));
      break;

    case AHTXX_BUSY_ERROR:
      Serial.println(F("sensor busy, increase polling time"));
      break;

    case AHTXX_ACK_ERROR:
      Serial.println(F("sensor didn't return ACK, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    case AHTXX_DATA_ERROR:
      Serial.println(F("received data smaller than expected, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    case AHTXX_CRC8_ERROR:
      Serial.println(F("computed CRC8 not match received CRC8, this feature supported only by AHT2x sensors"));
      break;

    default:
      Serial.println(F("unknown status"));    
      break;
  }
}

/*******************************************
 * TEMT6000光强度传感器部分
 *******************************************/
/*
 * 全局变量
 */
ANALOG_SENSOR_TYPE _sensorType;

/*
 *函数功能：初始化TEMT6000传感器 
 * 
 */
float lightIntensity = 0;//lux
int lightSourceValue = 0;

void lightSensor_Init(void){
  light_Intensity = 0;
  light_SourceValue = 0;
}

void read_LightSensor(void){
    _sensorType = T_LIGHT;
    lightSourceValue = filter(_sensorType);
    float volts = lightSourceValue * 3.3 / 4095.0;
    lightIntensity = volts * 200.0；

    /*
     * do display or serial println
     */
}

/*******************************************
 * Vsys电压模拟输入功能部分
 *******************************************/

/*
 *函数功能：初始化Vsys电压模拟输入功能
 * 
 */
float sysVoltage = 0;//volt
int Voltage_SourceValue = 0;

void sysVoltage_Init(void){
  sysVoltage = 0;
  Voltage_SourceValue = 0;
}

void read_sysVoltage(void){
    _sensorType = T_VSYS;
    Voltage_SourceValue = filter(_sensorType);
    float volts = Voltage_SourceValue * 3.3 / 4095.0;
    sysVoltage = volts * 3.0；

    /*
     * do display or serial println
     */
}


/*******************************************
 * mq135气体浓度传感器部分
 *******************************************/
 
float co2_concentration = 0;

/*
 *函数功能：初始化GAS传感器
 * 
 */
void gasTestUnit(void){
  
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

//  Serial.print("MQ135 RZero: ");
//  Serial.print(rzero);
//  Serial.print("\t Corrected RZero: ");
//  Serial.print(correctedRZero);
//  Serial.print("\t Resistance: ");
//  Serial.print(resistance);
//  Serial.print("\t PPM: ");
//  Serial.print(ppm);
//  Serial.print("\t Corrected PPM: ");
//  Serial.print(correctedPPM);
//  Serial.print("ppm @ temp/hum: ");
//  Serial.print(temperature);
//  Serial.print("/");
//  Serial.print(humidity);
//  Serial.println("%");
  
}


void read_co2_concentration(void){
    _sensorType = T_GAS;
    co2_concentration = filter(_sensorType);
    /*
     * do display or serial println
     */
}
 

int filter(ANALOG_SENSOR_TYPE mysensor){

  int _pin = 0;
  switch(mysensor){
    case T_LIGHT:
      _pin = PIN_LIGHT_SENSOR;
    break;
    
    case T_GAS:
      _pin = PIN_GAS_SENSOR;
      /*
       * do gas filter
       */
      int value = analogRead(_pin);
      return value;
    break;
    
    case T_VSYS:
      _pin = PIN_VSYS;
    break;
  }
  /*
   * some code to do filter
   */
  int value = analogRead(_pin);
  
  return value;
}

/*******************************************
 * VL6180x距离传感器部分
 *******************************************/
VL6180X distance_sensor;

void vl6180x_Init(void){
  Wire1.setSDA();
  Wire1.setSCL();
  Wire1.begin();
  distance_sensor.setBus(&Wire1);
  
}