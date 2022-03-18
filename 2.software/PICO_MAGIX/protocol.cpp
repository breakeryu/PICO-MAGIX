#include "protocol.h"


AnalogParaTypeDef aPara;
DigitalParaTypeDef dPara;

uint16_t localStation=1;
uint16_t mcudRxLength=0;
uint8_t mcudRxBuffer[MCUDRECEIVELENGTH];


void modbusSlave_Init(void){
  Serial1.begin(9600);
  slaveDataInit();
}


void deviceProcessCmd(void){
  ledStrip_ParasCmd();
}


bool modbusSlave_poll(void){
  bool pollOk = false;
  uint16_t respondLength=0;
  if(mcudRxLength>=8)
  {
    uint8_t respondBytes[MCUDRECEIVELENGTH];
    
    respondLength=ParsingMasterAccessCommand(mcudRxBuffer,respondBytes,mcudRxLength,localStation);
    if(respondLength!=65535)
    {
        /* USART1数据发送函数 */
        mcudRxLength=0;
        Serial1.write(respondBytes,respondLength);
        pollOk = true;
    }
  }
  return pollOk;
}

//单独线圈驱动完成
//todo 模拟量，测试输出

void slaveDataInit(void){


  dPara.coil[0] = 1;
  dPara.coil[1] = 1;
  dPara.coil[3] = 1;
  dPara.coil[4] = 1;

}


/*
串口的接收中断函数
*/
void serialEvent1(void){

    if(mcudRxLength>=MCUDRECEIVELENGTH)
    {
        mcudRxLength=0;
    }

    uint8_t rData = Serial1.read();

    if((0!=mcudRxLength)||(localStation==rData))
    {
        mcudRxBuffer[mcudRxLength++] = rData;
    }

}





/*获取想要读取的Coil量的值*/
void GetCoilStatus(uint16_t startAddress,uint16_t quantity,bool *statusList)
{
  uint16_t start;
  uint16_t count;
  /*先判断地址是否处于合法范围*/
  start=(startAddress>CoilStartAddress)?((startAddress<=CoilEndAddress)?startAddress:CoilEndAddress):CoilStartAddress;
  count=((start+quantity-1)<=CoilEndAddress)?quantity:(CoilEndAddress-start);
  
  for(int i=0;i<count;i++)
  {
    statusList[i]=dPara.coil[start+i];
  }
}

/*获取想要读取的保持寄存器的值*/
void GetHoldingRegister(uint16_t startAddress,uint16_t quantity,uint16_t *registerValue)
{
  uint16_t start;
  uint16_t count;
  /*先判断地址是否处于合法范围*/
  start=(startAddress>HoldingRegisterStartAddress)?((startAddress<=HoldingRegisterEndAddress)?startAddress:HoldingRegisterEndAddress):HoldingRegisterStartAddress;
  count=((start+quantity-1)<=HoldingRegisterEndAddress)?quantity:(HoldingRegisterEndAddress-start);
  
  for(int i=0;i<count;i++)
  {
    registerValue[i]=aPara.holdingRegister[start+i];
  }
}

/*设置单个线圈的值*/
void SetSingleCoil(uint16_t coilAddress,bool coilValue)
{
  /*先判断地址是否处于合法范围*/
  bool noError = (coilAddress>=CoilStartAddress)?((coilAddress<=CoilEndAddress)?true:false):false;

  if(noError)
  {
    dPara.coil[coilAddress]=coilValue;
  }
}

/*设置多个线圈的值*/
void SetMultipleCoil(uint16_t startAddress,uint16_t quantity,bool *statusValue)
{
  uint16_t endAddress=startAddress+quantity-1;
  
  bool noError=((startAddress>=CoilStartAddress)?((startAddress<=CoilEndAddress)?true:false):false)
                &&((endAddress>=CoilStartAddress)?((endAddress<=CoilEndAddress)?true:false):false);
  
  if(noError)
  {
    for(int i=0;i<quantity;i++)
    {
      dPara.coil[i+startAddress]=statusValue[i];
    }
  }
}

/*设置单个寄存器的值*/
void SetSingleRegister(uint16_t registerAddress,uint16_t registerValue)
{
  bool noError=(registerAddress>=HoldingRegisterStartAddress)?((registerAddress<=HoldingRegisterEndAddress)?true:false):false;

  if(noError)
  {
    aPara.holdingRegister[registerAddress]=registerValue;
  }
  
}


/*设置多个寄存器的值*/
void SetMultipleRegister(uint16_t startAddress,uint16_t quantity,uint16_t *registerValue)
{
  uint16_t endAddress=startAddress+quantity-1;
  
  bool noError=((startAddress>=HoldingRegisterStartAddress)?((startAddress<=HoldingRegisterEndAddress)?true:false):false)
                &&((endAddress>=HoldingRegisterStartAddress)?((endAddress<=HoldingRegisterEndAddress)?true:false):false);

  if(noError)
  {
    for(int i=0;i<quantity;i++)
    {
      aPara.holdingRegister[startAddress+i]=registerValue[i];
    }
  }

}


