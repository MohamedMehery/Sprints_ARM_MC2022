/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Dio_Cfg.h
 *  Module:  	  Dio_Cfg
 *
 *  Description:  Header file for Dio Module's user configurations
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Mohamed Abdelnasser
 *	Date:		  	5/12/2022
 *********************************************************************************************************************/
#ifndef Dio_CFG_H_
#define Dio_CFG_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 /* Number of the configured Dio Channels */
#define NUM_CONFIGURED_CHANNELS              		(5U)

/* Channel Index in the array of structures in Dio_Lcfg.c */
#define DIO_CONFIG_LED1_CHANNEL_ID        			(uint8_t)0x00
#define DIO_CONFIG_LED2_CHANNEL_ID        			(uint8_t)0x01
#define DIO_CONFIG_LED3_CHANNEL_ID        			(uint8_t)0x02
#define DIO_CONFIG_SWITCH1_CHANNEL_ID        		(uint8_t)0x03
#define DIO_CONFIG_SWITCH2_CHANNEL_ID        		(uint8_t)0x04

/* DIO Configured Port's ID  */
#define DIO_CONFIG_LED1_PORT                		(Dio_Port_t)PORTF
#define DIO_CONFIG_LED2_PORT                		(Dio_Port_t)PORTF
#define DIO_CONFIG_LED3_PORT                		(Dio_Port_t)PORTF
#define DIO_CONFIG_SWITCH1_PORT                 	(Dio_Port_t)PORTF
#define DIO_CONFIG_SWITCH2_PORT                 	(Dio_Port_t)PORTF

/* DIO Configured Channel's ID */
#define DIO_CONFIG_LED1_CHANNEL             		(Dio_Pin_t)PIN1
#define DIO_CONFIG_LED2_CHANNEL             		(Dio_Pin_t)PIN2
#define DIO_CONFIG_LED3_CHANNEL             		(Dio_Pin_t)PIN3
#define DIO_CONFIG_SWITCH1_CHANNEL              	(Dio_Pin_t)PIN4
#define DIO_CONFIG_SWITCH2_CHANNEL              	(Dio_Pin_t)PIN0

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/* Structure to gather the configured channels to be used and manipulated easily */
typedef struct
{
	Dio_ChannelConfig_t channels[NUM_CONFIGURED_CHANNELS];
} Dio_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
extern const Dio_ConfigType configList;

#endif  /* DIO_CFG_H_ */
/**********************************************************************************************************************
 *  END OF FILE: Dio_Cfg.h
 *********************************************************************************************************************/
