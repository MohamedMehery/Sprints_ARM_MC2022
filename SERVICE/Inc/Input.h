/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Input.h
 *  Module:  	  Input
 *  Description:  Header file for Input Service
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	Mohamed Abdelnasser
**	Date:		  5/12/2022
 *********************************************************************************************************************/
#ifndef Input_H_
#define Input_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Service_Types.h"
#include "Button.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/
/*******************************************************************************
* Service Name: get_pulse_timing
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): MasterDeviceChannel - The device which will start listening to the input pulses
*				   MasterStatusChannel - The device will make a slight response for the master to give the app some interactivity
*				   SlaveDeviceChannel - The device which will trigger the input pulses
*				   SlaveStatusChannel - The device will make a response for the slave to give the app some interactivity
* 				   ButtonAttach  - Identification for the connection type (PULL_UP or PULL_DOWN)
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description: Function to initialize the connected devices and get the number of pulses as input
*******************************************************************************/
uint8_t get_pulse_timing(Service_Device_Channel MasterDeviceChannel, Service_Device_Channel MasterStatusChannel,\
							Service_Device_Channel SlaveDeviceChannel, Service_Device_Channel SlaveStatusChannel,\
							Button_ButtonAttach_t ButtonAttach);
 
#endif /* Input_H_ */
/**********************************************************************************************************************
*  END OF FILE: Input.h
*********************************************************************************************************************/