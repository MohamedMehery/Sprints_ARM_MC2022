/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Dio.h
 *  Module:  	  Dio
 *
 *  Description:  Header file for Dio Module
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Mohamed Abdelnasser
 *	Date:		  	5/12/2022
 *********************************************************************************************************************/
#ifndef DIO_H_
#define DIO_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/
/*******************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Dio_Channel_t
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_Level_t
* Description: Function for DIO read Channel API
*******************************************************************************/
Dio_Level_t Dio_ReadChannel(Dio_Channel_t ChannelId);

/*******************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Dio_Channel_t, Level - Dio_Level_t
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function for DIO write Channel API
*******************************************************************************/
void Dio_WriteChannel(Dio_Channel_t ChannelId, Dio_Level_t Level);

/*******************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - Dio_Channel_t
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_Level_t
* Description: Function for DIO flip Channel, then read Channel API
*******************************************************************************/
Dio_Level_t Dio_FlipChannel(Dio_Channel_t ChannelId);

/*******************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - Dio_Port_t
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevel_t
* Description: Function for DIO read Port API
*******************************************************************************/
Dio_PortLevel_t Dio_ReadPort(Dio_Port_t PortId);

/*******************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - Dio_Port_t, Level - Dio_PortLevel_t
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function for DIO write Port API
*******************************************************************************/
void Dio_WritePort(Dio_Port_t PortId, Dio_PortLevel_t Level);
 
#endif  /* DIO_H_ */
/**********************************************************************************************************************
 *  END OF FILE: Dio.h
 *********************************************************************************************************************/
