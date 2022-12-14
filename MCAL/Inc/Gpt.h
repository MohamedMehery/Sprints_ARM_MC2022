/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Gpt.h
 *  Module:  	  Gpt
 *
 *  Description:  Header file for TM4C123GH6PM MCU - Gpt Module
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Mohamed Abdelnasser
 *	Date:		  5/12/2022
 *********************************************************************************************************************/
#ifndef Gpt_H_
#define Gpt_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"
/**********************************************************************************************************************
 * GLobal variables
 *********************************************************************************************************************/
typedef void (* timer_cb_t)(void) ;
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/
/*******************************************************************************
* Service Name: Gpt_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build (Linking) configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Initialize the hardware time module according to config.
*              - Disable all interrupts notifications
*              - Set the operation mode of GPT to ONESHOT or CONTINOUS Mode
*              - Start all the enabled GPT Predefined timers at value = 0
*******************************************************************************/
void Gpt_Init(Gpt_Channel_Config_t* ConfigPtr ,timer_cb_t tm_cb);

/*******************************************************************************
* Service Name: Gpt_DisableNotification
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Pointer to Gpt_Channel_t data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable the notification when the dedicated timer hits the target
*******************************************************************************/
void Gpt_DisableNotification(Gpt_Channel_t ChannelId);

/*******************************************************************************
* Service Name: Gpt_EnableNotification
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Pointer to Gpt_Channel_t data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable the notification when the dedicated timer hits the target
*******************************************************************************/
void Gpt_EnableNotification(Gpt_Channel_t ChannelId);

/*******************************************************************************
* Service Name: Gpt_StartTimer
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Pointer to Gpt_Channel_t data, Value - the timer value in microseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to make the dedicated timer start counting
*******************************************************************************/
void Gpt_StartTimer(Gpt_Channel_t ChannelId, Gpt_ValueType Value);

/*******************************************************************************
* Service Name: Gpt_StopTimer
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Pointer to Gpt_Channel_t data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to make the dedicated timer stop counting
*******************************************************************************/
void Gpt_StopTimer(Gpt_Channel_t ChannelId);

/*******************************************************************************
* Service Name: Gpt_GetTimepassed_
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Pointer to Gpt_Channel_t data
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType
* Description: Function to get the counted time until the call's moment
*******************************************************************************/
Gpt_ValueType Gpt_GetTimepassed_(Gpt_Channel_t ChannelId);

/*******************************************************************************
* Service Name: Gpt_GetTimeRemaining
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Pointer to Gpt_Channel_t data
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType
* Description: Function to get the remaining time to hit the target from the calling's moment
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_Channel_t ChannelId);


#endif  /* Gpt_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Gpt.h
 *********************************************************************************************************************/
