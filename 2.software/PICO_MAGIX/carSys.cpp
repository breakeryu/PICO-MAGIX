/*
 * Id:        carSys.c
 *
 * Function:  Contains all API functions.
 *
 * This is an automatically generated file. It will be overwritten by the Coder.
 *
 * DO NOT EDIT THE FILE!
 */


#include "carSys.h"
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)


#include <stdint.h>
#endif


enum carSysDeductIterationEnum
{
  kDIOriginalEvent = 0U,
  kDITakeSignalOut = 5U
};


/*
 * Used internally in the API
 */
enum carSysSEMStateEnum
{
  STATE_SEM_NOT_INITIALIZED = 0U,
  STATE_SEM_INITIALIZED     = 1U,
  STATE_SEM_PREPARE         = 2U,
  STATE_SEM_OKAY            = 3U
};


/*
 * SEM Library Datatype Definition.
 */
struct carSysSEMDATA
{
  enum carSysSEMStateEnum                       State;
  SEM_EVENT_TYPE                                EventNo;
  uint8_t                                       Chg;
  SEM_STATE_TYPE                                CSV[VS_NOF_STATE_MACHINES];
  SEM_STATE_TYPE                                WSV[VS_NOF_STATE_MACHINES];
  SEM_EVENT_TYPE                                SQueue[1];
  SEM_SIGNAL_QUEUE_TYPE                         SPut;
  SEM_SIGNAL_QUEUE_TYPE                         SGet;
  SEM_SIGNAL_QUEUE_TYPE                         SUsed;
};


/*
 * VS System Datatype Definition.
 */
struct VSDATAcarSys
{
  uint8_t        StateMachineIndex[0X012];
  uint8_t        RuleData[0X0b4];
  uint8_t        RuleIndex[0X016];
  uint8_t        RuleTableIndex[0X016];
};


/*
 * SEM Library data definition.
 */
struct carSysSEMDATA SEMcarSys;


/*
 * VS System data definition and initialization. Rule data format number: 1
 */
struct VSDATAcarSys const carSys = 
{
  {
    0x00U, 0x00U, 0x01U, 0x01U, 0x02U, 0x02U, 0x03U, 0x03U, 
    0x04U, 0x04U, 0x05U, 0x05U, 0x06U, 0x06U, 0x07U, 0x07U, 
    0x08U, 0x08U
  },
  {
    0x00U, 0x90U, 0x05U, 0x01U, 0x02U, 0x04U, 0x06U, 0x09U, 
    0x0AU, 0x0CU, 0x0EU, 0x10U, 0x02U, 0x03U, 0x04U, 0x05U, 
    0x00U, 0x01U, 0x10U, 0x10U, 0x00U, 0x01U, 0x11U, 0x01U, 
    0x20U, 0x00U, 0x01U, 0x00U, 0x04U, 0x02U, 0x10U, 0x10U, 
    0x00U, 0x05U, 0x08U, 0x14U, 0x02U, 0x10U, 0x10U, 0x00U, 
    0x05U, 0x09U, 0x13U, 0x00U, 0x10U, 0x10U, 0x09U, 0x13U, 
    0x01U, 0x10U, 0x01U, 0x02U, 0x03U, 0x01U, 0x01U, 0x10U, 
    0x01U, 0x03U, 0x02U, 0x00U, 0x02U, 0x20U, 0x10U, 0x00U, 
    0x04U, 0x00U, 0x05U, 0x12U, 0x02U, 0x20U, 0x10U, 0x00U, 
    0x05U, 0x00U, 0x04U, 0x11U, 0x03U, 0x50U, 0x00U, 0x00U, 
    0x05U, 0x06U, 0x07U, 0x0AU, 0x0CU, 0x0EU, 0x10U, 0x01U, 
    0x50U, 0x00U, 0x06U, 0x07U, 0x0AU, 0x0CU, 0x0EU, 0x10U, 
    0x01U, 0x10U, 0x04U, 0x07U, 0x06U, 0x02U, 0x03U, 0x04U, 
    0x05U, 0x03U, 0x10U, 0x04U, 0x00U, 0x05U, 0x07U, 0x06U, 
    0x02U, 0x03U, 0x04U, 0x05U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x0AU, 0x07U, 0x0BU, 0x06U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x0BU, 0x07U, 0x0AU, 0x02U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x0CU, 0x07U, 0x0DU, 0x08U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x0DU, 0x07U, 0x0CU, 0x04U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x0EU, 0x07U, 0x0FU, 0x07U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x0FU, 0x07U, 0x0EU, 0x03U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x10U, 0x07U, 0x11U, 0x09U, 0x02U, 0x20U, 0x01U, 0x07U, 
    0x11U, 0x07U, 0x10U, 0x05U
  },
  {
    0x00U, 0x44U, 0x3CU, 0x24U, 0x1DU, 0x7CU, 0x9CU, 0x8CU, 
    0xACU, 0x69U, 0x74U, 0x94U, 0x84U, 0xA4U, 0x11U, 0x17U, 
    0x4CU, 0x2BU, 0x60U, 0x57U, 0x36U, 0x30U
  },
  {
    0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 
    0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU, 
    0x10U, 0x11U, 0x13U, 0x14U, 0x15U, 0x16U
  }
};


/* Core model logic struct name */
#define VS carSys


/* SEM data struct name */
#define SEM SEMcarSys


/* Signal queue function prototypes */
static SEM_EVENT_TYPE SEM_SignalQueueGet (void);
static VSResult SEM_SignalQueuePut (SEM_EVENT_TYPE SignalNo);


/*
 * Guard expression type definition
 */
typedef _Bool (* carSysVS_GUARDEXPR_TYPE) (void);


static void carSysDeductChangeState (void);


static VSResult carSysSEM_GetOutput (void);



/*
 * Action expressions wrapper function implementation.
 */
static void carSysVSAction (SEM_ACTION_EXPRESSION_TYPE i)
{
  switch (i)
  {
  case 0:
    aTurnLightOff();
    break;
  case 1:
    aTurnLightOn();
    break;
  case 2:
    aTurnOffDoor1();
    break;
  case 3:
    aTurnOffDoor2();
    break;
  case 4:
    aTurnOffDoor3();
    break;
  case 5:
    aTurnOffDoor4();
    break;
  case 6:
    aTurnOnDoor1();
    break;
  case 7:
    aTurnOnDoor2();
    break;
  case 8:
    aTurnOnDoor3();
    break;
  case 9:
    aTurnOnDoor4();
    break;

  default:
    break;
  }
}


void carSysSEM_InitSignalQueue (void)
{
  SEM.SPut = 0U;
  SEM.SGet = 0U;
  SEM.SUsed = 0U;
}


static VSResult SEM_SignalQueuePut (SEM_EVENT_TYPE SignalNo)
{
  VSResult result;

  if (SEM.SUsed == 1U)
  {
    result = SES_SIGNAL_QUEUE_FULL;
  }
  else
  {
    ++SEM.SUsed;
    SEM.SQueue[SEM.SPut] = SignalNo;
    ++SEM.SPut;
    if (SEM.SPut == 1U)
    {
      SEM.SPut = 0U;
    }
    result = SES_OKAY;
  }
  return (result);
}


static SEM_EVENT_TYPE SEM_SignalQueueGet (void)
{
  SEM_EVENT_TYPE SignalNo = EVENT_UNDEFINED;

  if (SEM.SUsed != 0U)
  {
    SEM.SUsed--;
    SignalNo = SEM.SQueue[SEM.SGet];
    ++SEM.SGet;
    if (SEM.SGet == 1U)
    {
      SEM.SGet = 0U;
    }
  }
  return (SignalNo);
}





void carSysVSInitAll (void)
{
  carSysSEM_Init();
  carSysSEM_InitSignalQueue();
}


void carSysSEM_Init (void)
{
  {
    SEM_STATE_MACHINE_TYPE i;
    for (i = 0U; i < 9U; ++i)
    {
      SEM.WSV[i] = STATE_UNDEFINED;
      SEM.CSV[i] = STATE_UNDEFINED;
    }
  }
  SEM.Chg = 0U;
  SEM.State = STATE_SEM_INITIALIZED;
}


static void carSysDeductChangeState (void)
{
  SEM_STATE_MACHINE_TYPE i;
  for (i = 0U; i < 9U; ++i)
  {
    if (SEM.WSV[i] != STATE_UNDEFINED)
    {
      if (SEM.CSV[i] != SEM.WSV[i])
      {
        SEM.Chg = 1U;
      }
      SEM.CSV[i] = SEM.WSV[i];
      SEM.WSV[i] = STATE_UNDEFINED;
    }
  }
}


VSResult carSysVSDeductEx (SEM_EVENT_TYPE EventNo)
{
  VSResult cc;
  if (SEM.State == STATE_SEM_NOT_INITIALIZED)
  {
    return (SES_NOT_INITIALIZED);
  }
  if (17U <= EventNo)
  {
    return (SES_RANGE_ERR);
  }
  SEM.EventNo = EventNo;
  SEM.State = STATE_SEM_PREPARE;
  cc = carSysSEM_GetOutput();
  if (cc == SES_OKAY)
  {
    carSysDeductChangeState();
    SEMcarSys.State = STATE_SEM_INITIALIZED;
    if (SEMcarSys.Chg == 1U)
    {
      SEMcarSys.Chg = 0U;
      cc = SES_FOUND;
    }
    else
    {
      cc = SES_OKAY;
    }
  }
  return cc;
}


static VSResult carSysSEM_GetOutput (void)
{
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
  uint_fast8_t DIt = kDIOriginalEvent;
  uint_fast8_t iFirstR;
  uint_fast8_t iLastR;
#else
  uint8_t DIt = kDIOriginalEvent;
  SEM_RULE_TABLE_INDEX_TYPE iFirstR;
  SEM_RULE_TABLE_INDEX_TYPE iLastR;
#endif
  for(;;)
  {
    switch (SEM.State)
    {
    case STATE_SEM_PREPARE:
      switch (DIt)
      {
      case kDIOriginalEvent:
        DIt = kDITakeSignalOut;
        break;

      case kDITakeSignalOut:
        SEMcarSys.EventNo = SEM_SignalQueueGet();
        if (SEMcarSys.EventNo == EVENT_UNDEFINED)
        {
          SEMcarSys.State = STATE_SEM_OKAY;
          return (SES_OKAY);
        }
        DIt = kDITakeSignalOut;
        carSysDeductChangeState();
        break;

      }

      iFirstR = VS.RuleTableIndex[SEM.EventNo];
      iLastR = VS.RuleTableIndex[SEM.EventNo + 1U];
      while (iFirstR < iLastR)
      {
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
        uint_fast8_t i;
        uint_fast8_t nNo;
        uint_fast8_t nPos;
        uint_fast8_t nNxt;
        uint_fast8_t nSignal;
        uint_fast8_t iRI;
        uint_fast8_t nAction;
#else
        SEM_INTERNAL_TYPE i;
        uint8_t nNo;
        uint8_t nPos;
        uint8_t nNxt;
        uint8_t nSignal;
        SEM_RULE_INDEX_TYPE iRI;
        uint8_t nAction;
#endif

        iRI = VS.RuleIndex[iFirstR];
        ++iFirstR;
        i = VS.RuleData[iRI];
        ++iRI;
        nPos = (unsigned char)(i & 0x0FU);
        i = VS.RuleData[iRI];
        ++iRI;
        nNxt = (unsigned char)(i >> 4U);
        i = VS.RuleData[iRI];
        ++iRI;
        nAction = (unsigned char)(i & 0x0FU);
        nSignal = (unsigned char)(i >> 4U);

        for (nNo = 0U; nNo < nPos; ++nNo)
        {
          SEM_STATE_TYPE sa;
          sa = (SEM_STATE_TYPE)(VS.RuleData[iRI]);
          if (sa != SEM.CSV[VS.StateMachineIndex[sa]])
          {
            goto NextRule;
          }
          else
          {
            ++iRI;
          }
        }


        for (nNo = 0U; nNo < nNxt; ++nNo)
        {
          SEM_STATE_TYPE sa;
          sa = (SEM_STATE_TYPE)(VS.RuleData[iRI]);
          ++iRI;
          i = VS.StateMachineIndex[sa];
          if (SEM.WSV[i] == STATE_UNDEFINED)
          {
            SEM.WSV[i] = sa;
          }
          else if (SEM.WSV[i] != sa)
          {
            return (SES_CONTRADICTION);
          }
        }
        if (nSignal != 0U)
        {
          for (nNo = 0U; nNo < nSignal; ++nNo)
          {
            i = VS.RuleData[iRI];
            ++iRI;
            if (SEM_SignalQueuePut((SEM_EVENT_TYPE)(i)) == SES_SIGNAL_QUEUE_FULL)
            {
              return (SES_SIGNAL_QUEUE_FULL);
            }
          }
        }
        while (nAction != 0U)
        {
          SEM_ACTION_EXPRESSION_TYPE actionNo;
          actionNo = (SEM_ACTION_EXPRESSION_TYPE)(VS.RuleData[iRI]);
          ++iRI;
          nAction--;
          carSysVSAction(actionNo);
          SEMcarSys.Chg = 1U;
        }
NextRule:
        ;
      }
      break;

    case STATE_SEM_OKAY:
      return (SES_OKAY);

    default:
      return (SES_EMPTY);
    }
  }
}


VSResult carSysVSElementName (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text)
{
  VSResult ret = SES_OKAY;
  switch (IdentType)
  {
  default:
    ret = SES_TYPE_ERR;
    break;
  }
  return ret;
}


VSResult carSysVSElementExpl (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text)
{
  VSResult ret = SES_OKAY;
  switch (IdentType)
  {
  default:
    ret = SES_TYPE_ERR;
    break;
  }
  return ret;
}


VSResult carSysSEM_State (SEM_STATE_MACHINE_TYPE StateMachineNo,
  SEM_STATE_TYPE *StateNo)
{
  if (9U <= StateMachineNo)
  {
    return (SES_RANGE_ERR);
  }
  *StateNo = SEM.CSV[StateMachineNo];
  return (SES_FOUND);
}


VSResult carSysSEM_StateAll (SEM_STATE_TYPE StateVector[],
  SEM_STATE_MACHINE_TYPE MaxSize)
{
  SEM_STATE_MACHINE_TYPE i;

  if (9U > MaxSize)
  {
    return (SES_BUFFER_OVERFLOW);
  }

  for (i = 0U; i < 9U; ++i)
  {
    StateVector[i] = SEM.CSV[i];
  }
  return (SES_FOUND);
}
