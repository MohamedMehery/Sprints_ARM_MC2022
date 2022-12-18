/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Service_Types.h
 *  Module:  	  Service_Types
 *  Description:  Header file for Service's types
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	Mohamed Abdelnasser
 *	Date:		  15/12/2022
 *********************************************************************************************************************/
#ifndef SERVICE_TYPES_H_
#define SERVICE_TYPES_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Std_Types.h"
#include "Led.h"
#include "Button.h"
#include "Dio.h"
#include "Gpt.h"

/**********************************************************************************************************************
*  GLOBAL DATA PROTOTYPES
*********************************************************************************************************************/
typedef Led_LedChannelType Service_DeviceChannel; /* Can be used as Button_ButtonChannel_t too */

typedef uint16_t Service_TimeType;

typedef uint8_t Service_HighPeriodType;

typedef uint8_t Service_LowPeriod_t;

typedef Gpt_Channel_t Service_TimerChannel_t;
 
 
#endif /* SERVICE_TYPES_H_ */
/**********************************************************************************************************************
*  END OF FILE: Service_Types.h
*********************************************************************************************************************/