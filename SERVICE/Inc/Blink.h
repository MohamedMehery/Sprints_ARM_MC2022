/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Blink.h
 *  Module:  	  Blink
 *  Description:  Header file for Blink Service
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	Mohamed Abdelnasser
 *	Date:		  15/12/2022
 *********************************************************************************************************************/
#ifndef BLINK_H_
#define BLINK_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Service_Types.h"
#define TIMEOUT 200
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/
/*******************************************************************************
* Service Name: led_blink
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): TimerChannle - The Timer used for blinking timing
*				   DeviceChannel - The device which will blink
*				   Time - How long the blinking should be,
*				   HighPeriod - How long to stay high
*				   LowPeriod - How long to stay low
* Return value: void
* Description: Function to initialize and start blinking service
*******************************************************************************/
void led_blink(Service_TimerChannel_t TimerChannle, Service_Device_Channel DeviceChannel, Service_TimeType Time, Service_HighPeriodType HighPeriod, Service_LowPeriod_t LowPeriod);
 
/*******************************************************************************
* Service Name: Blink_Stop
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): DeviceChannel - The device which is blinking
* Return value: void
* Description: Function to stop blinking
*******************************************************************************/
void Blink_Stop(Service_Device_Channel DeviceChannel);
 
#endif /* LED_H_ */
/**********************************************************************************************************************
*  END OF FILE: Led.h
*********************************************************************************************************************/