#ifndef visualSTATE_CARSYS_H
#define visualSTATE_CARSYS_H

/*
 * Id:        carSys.h
 *
 * Function:  Contains definitions needed for API functions.
 *
 * This is an automatically generated file. It will be overwritten by the Coder.
 *
 * DO NOT EDIT THE FILE!
 */


#include <stddef.h>


#include "Car_sys.h"
#include <Arduino.h>

/*
 * SEM Variable Types.
 */
typedef uint8_t   SEM_EVENT_TYPE;
typedef uint8_t   SEM_ACTION_EXPRESSION_TYPE;
typedef uint8_t   SEM_GUARD_EXPRESSION_TYPE;
typedef uint8_t   SEM_EXPLANATION_TYPE;
typedef uint8_t   SEM_STATE_TYPE;
typedef uint8_t   SEM_STATE_MACHINE_TYPE;
typedef uint8_t   SEM_INSTANCE_TYPE;
typedef uint8_t   SEM_RULE_INDEX_TYPE;
typedef uint8_t   SEM_INTERNAL_TYPE;
typedef uint8_t   SEM_SIGNAL_QUEUE_TYPE;
typedef uint8_t   SEM_ACTION_FUNCTION_TYPE;
typedef uint8_t   SEM_EVENT_GROUP_TYPE;
typedef uint8_t   SEM_EGTI_TYPE;
typedef uint8_t   SEM_RULE_TABLE_INDEX_TYPE;


/*
 * Number of Identifiers.
 */
#define VS_NOF_ACTION_FUNCTIONS          10U
#define VS_NOF_EVENTS                    17U
#define VS_NOF_INSTANCES                 1U
#define VS_NOF_STATE_MACHINES            9U
#define VS_NOF_STATES                    18U


/*
 * Undefined State.
 */
#define STATE_UNDEFINED                  255U


/*
 * Undefined Event.
 */
#define EVENT_UNDEFINED                  255U


/*
 * Undefined Event Group.
 */
#define EVENT_GROUP_UNDEFINED            255U


/*
 * Event Termination ID.
 */
#define EVENT_TERMINATION_ID             255U


/*
 * Event Identifier Definitions.
 */
#define SE_RESET 0U
#define eCarLocked 1U
#define eCarUnlock 2U
#define eChangeSwitchOff 3U
#define eChangeSwitchOn 4U
#define eCloseDoor1 5U
#define eCloseDoor2 6U
#define eCloseDoor3 7U
#define eCloseDoor4 8U
#define eLockDoor 9U
#define eOpenDoor1 10U
#define eOpenDoor2 11U
#define eOpenDoor3 12U
#define eOpenDoor4 13U
#define eSysClose 14U
#define eSysOpen 15U
#define eUnLockDoor 16U


/*
 * Name        : carSysVSInitAll
 *
 * Description : The function is a wrapper to all initialization functions.
 *               The function calls the following functions in the listed
 *               order (provided the specific function exists):
 *                 SEM_Init
 *                 SEM_InitExternalVariables
 *                 SEM_InitInternalVariables
 *                 SEM_InitSignalQueue
 *                 SEM_InitInstances
 *
 * Argument    : None.
 *
 * Return      : None.
 */
void carSysVSInitAll (void);


/*
 * Name        : SEM_Init
 *
 * Description : Before calling any other functions this function must be
 *               called to initialize the VS System. In addition it is
 *               possible to call the initialization functions for the
 *               signal queue, internal variables and external variables.
 *
 * Argument    : None.
 *
 * Return      : None.
 */
void carSysSEM_Init (void);


/*
 * Name        : SEM_InitSignalQueue
 *
 * Description : This function initializes the signal queue in a VS System.
 *               This function must be called together with the SEM_Init
 *               function. The function will only be avaliable if the signal
 *               queue is enabled and the VS System contains signals.
 *
 * Argument    : None.
 *
 * Return      : None.
 */
void carSysSEM_InitSignalQueue (void);


/*
 * Name        : carSysVSDeductEx
 *
 * Description : The function prepares the reception of action expressions,
 *               that can be deduced on the basis of the given event, the
 *               internal current state vector and the rules in the VS
 *               System.
 *               All action expressions are deduced internally in VSDeduct
 *               by continuously calling the function SEM_GetOutput.
 *
 * Argument    : EventNo:
 *                 Event number to be processed.
 *
 *               Variable number of arguments:
 *                 Used if at least one event has a parameter.
 *                 The function call must include one argument for each type
 *                 name declared in the parameter list for each event.
 *                 
 *                 This sample declaration is for an event with three
 *                 parameters:
 *                 
 *                   EventName (uint8_t par1, char par2, int par3)
 *                 
 *                 How to call the VSDeduct function for the event
 *                 EventName:
 *                 
 *                   VSDeduct (EventName, par1, par2, par3);
 *
 * Return      : Completion code:
 *
 *                 SES_ACTIVE:
 *                   The function SEM_Inquiry has been called. All inquired
 *                   events have not been returned by the function
 *                   SEM_GetInput or SEM_GetInputAll. The state/event
 *                   deduction is okay, but the user should not call the
 *                   function SEM_GetInput before the functions
 *                   SEM_NextState or SEM_NextStateChg and SEM_Inquiry have
 *                   been called.
 *
 *                 SES_RANGE_ERR:
 *                   Event is out of range.
 *
 *                 SES_FOUND:
 *                   An action function was called or a state was changed.
 *
 *                 SES_OKAY:
 *                   Success.
 */
VSResult carSysVSDeductEx (SEM_EVENT_TYPE EventNo);


/*
 * Name        : carSysVSElementName
 *
 * Description : The function gets a pointer to the ASCII name of the
 *               specified identifier.
 *               The function must be enabled by its VS Coder option.
 *
 * Argument    : IdentType:
 *                 Must contain the identifier type of the identifier
 *                 number. It can be EVENT_TYPE, STATE_TYPE or ACTION_TYPE.
 *
 *               IdentNo:
 *                 Must contain the index number of an identifier.
 *
 *               Text:
 *                 Must be a pointer to a text string. If the function
 *                 terminates successfully, the text string contains the
 *                 name of the specified identifier.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   Identifier number is out of range.
 *
 *                 SES_TYPE_ERR:
 *                   The identifier type is not correct. Remember to include
 *                   the wanted text in the VS System and specify the
 *                   correct identifier type when calling this function.
 *
 *                 SES_OKAY:
 *                   Success.
 */
VSResult carSysVSElementName (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text);


/*
 * Name        : carSysVSElementExpl
 *
 * Description : The funciton gets the absolute address of an ASCII
 *               explanation of the specified identifier.
 *               The function must be enabled by its VS Coder option.
 *
 * Argument    : IdentType:
 *                 Must contain the identifier type of the identifier
 *                 number. It can be EVENT_TYPE, STATE_TYPE or ACTION_TYPE.
 *
 *               IdentNo:
 *                 Must contain the index number of an identifier.
 *
 *               Text:
 *                 Must be a pointer to a char pointer. If the function
 *                 terminates successfully, the pointer contains the
 *                 absolute address of the name of the specified identifier.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   Identifier number is out of range.
 *
 *                 SES_TYPE_ERR:
 *                   The identifier type is not correct. Remember to include
 *                   the wanted text in the VS System and specify the
 *                   correct identifier type when calling this function.
 *
 *                 SES_OKAY:
 *                   Success.
 */
VSResult carSysVSElementExpl (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text);


/*
 * Name        : SEM_State
 *
 * Description : The function will return the current state of the specified
 *               state machine.
 *               The function must be enabled by its VS Coder option.
 *
 * Argument    : StateMachineNo:
 *                 State machine number.
 *
 *               StateNo:
 *                 Pointer to store the current state of the specified state
 *                 machine.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   State machine index is out of range.
 *
 *                 SES_FOUND:
 *                   Success. State number index found.
 */
VSResult carSysSEM_State (SEM_STATE_MACHINE_TYPE StateMachineNo, SEM_STATE_TYPE *StateNo);


/*
 * Name        : SEM_StateAll
 *
 * Description : The function will return the current state of all the state
 *               machines.
 *               The function must be enabled by its VS Coder option.
 *
 * Argument    : StateVector:
 *                 Pointer to the array to store the current state vector.
 *
 *               MaxSize:
 *                 Specifies the length of the destination array. Must be
 *                 equal to or longer than the number of state machines.
 *
 * Return      : Completion code:
 *
 *                 SES_BUFFER_OVERFLOW:
 *                   The specified maxsize is insufficient. The state vector
 *                   is not valid.
 *
 *                 SES_FOUND:
 *                   Success. All state number indexes found.
 */
VSResult carSysSEM_StateAll (SEM_STATE_TYPE StateVector[], SEM_STATE_MACHINE_TYPE MaxSize);


/*
 * Action Function Prototypes.
 */
void aTurnLightOff (void);
void aTurnLightOn (void);
void aTurnOffDoor1 (void);
void aTurnOffDoor2 (void);
void aTurnOffDoor3 (void);
void aTurnOffDoor4 (void);
void aTurnOnDoor1 (void);
void aTurnOnDoor2 (void);
void aTurnOnDoor3 (void);
void aTurnOnDoor4 (void);


#endif /* ifndef visualSTATE_CARSYS_H */
