/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Dio_Types.h
 *  Module:  	  Dio_Types
 *
 *  Description:  Header file for Dio Module's Types
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Mohamed Abdelnasser
 *	Date:		  5/12/2022
 *********************************************************************************************************************/
#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* Type definition for Dio_Channel_t used by the DIO APIs */
typedef uint8_t Dio_Channel_t;

/* Type definition for Dio_Pin_t used by the DIO APIs */
typedef Port_PinType Dio_Pin_t;

/* Type definition for Dio_Port_t used by the DIO APIs */
typedef Port_PortType Dio_Port_t;

/* Type definition for Dio_ChannelConfig_t used by the DIO APIs */
typedef struct
{
	Dio_Port_t portId;
	Dio_Pin_t pinId;
} Dio_ChannelConfig_t;

/* Type definition for Dio_Level_t used by the DIO APIs */
typedef enum
{
	DIO_LEVEL_ERROR = -1,
	DIO_LEVEL_LOW = 0,
	DIO_LEVEL_HIGH = 1
} Dio_Level_t;

/* Type definition for Dio_PortLevel_t used by the DIO APIs */
typedef uint8_t Dio_PortLevel_t;

#endif  /* DIO_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Dio_Types.h
 *********************************************************************************************************************/
