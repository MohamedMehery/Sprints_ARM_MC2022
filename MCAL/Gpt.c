/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *  File:  		  Gpt.c
 *  Module:  	  Gpt
 *  Description:  Source file for TM4C123GH6PM MCU - Gpt Module's driver
 *  -------------------------------------------------------------------------------------------------------------------
 *	Author: 	  Mohamed Abdelnasser
 *	Date:		  5/12/2022
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpt.h"
#include "IntCtrl.h"
#include "Gpt_regs.h"
#include "Mcu_Hw.h"
#include "Macros.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
void Gpt_Init(const Gpt_Channel_Config_t* ConfigPtr)
{
	if (ConfigPtr->isEnabled == DISABLED)
		return;
	
	INTERRUPTS_DISABLE
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile Gpt_TimerInterruptType interruptId = 0;
	
	/* Enable the clock to the dedicated channel */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_0A;
			SYSCTL_RCGCTIMER.R0 = 1;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_1A;
			SYSCTL_RCGCTIMER.R1 = 1;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_2A;
			SYSCTL_RCGCTIMER.R2 = 1;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_3A;
			SYSCTL_RCGCTIMER.R3 = 1;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_4A;
			SYSCTL_RCGCTIMER.R4 = 1;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_5A;
			SYSCTL_RCGCTIMER.R5 = 1;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_0A;
			SYSCTL_RCGCWTIMER.R0 = 1;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_1A;
			SYSCTL_RCGCWTIMER.R1 = 1;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_2A;
			SYSCTL_RCGCWTIMER.R2 = 1;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_3A;
			SYSCTL_RCGCWTIMER.R3 = 1;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_4A;
			SYSCTL_RCGCWTIMER.R4 = 1;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_5A;
			SYSCTL_RCGCWTIMER.R5 = 1;
			break;
		default:
			return;
	}
	
	/* Enable Interrupt for the dedicated channel from IntCtrl Module */
	IntCtrl_EnableInterrupt(interruptId, ConfigPtr->priority);
	
	/* Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes. */
	GPT_GPTMCTL(channelPtr).TAEN = 0;

	/* Choose 16bit or full 32bit timer for 16/32bit timers, and 32bit or 64bit for 32/64bit timers */
	GPT_GPTMCFG(channelPtr) = 0x00000000;
	
	/* Enable match interrupt */
	GPT_GPTMTAMR(channelPtr).TAMIE = 1;

	/* Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR) */
	/*
		a. Write a value of 0x1 for One-Shot mode.
		b. Write a value of 0x2 for Periodic mode.
	*/
	GPT_GPTMTAMR(channelPtr).TAMR = ConfigPtr->mode;
	
	/* Specify the counting direction which is up or down */
	GPT_GPTMTAMR(channelPtr).TACDIR = ConfigPtr->direction;
	
	/* Update the GPTMTAR and GPTMTAV registers with the value in the GPTMTAILR register on the next timeout. */
	GPT_GPTMTAMR(channelPtr).TAILD = 1;
	
	/* Update the GPTMTAMATCHR register and the GPTMTAPR register, if used, on the next timeout. */
	GPT_GPTMTAMR(channelPtr).TAMRSU = 1;
	
	/* Enable Timeout interrupt */
	GPT_GPTMIMR(channelPtr).TATOIM = 1;
	
	/* Should enable all the interrupts again */
	INTERRUPTS_ENABLE
}

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
void Gpt_DisableNotification(Gpt_Channel_t ChannelId)
{
	const Gpt_Channel_Config_t* ConfigPtr = &(GPT_Config.channels[ChannelId]);
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile Gpt_TimerInterruptType interruptId = 0;
	
	/* Determine the channel address and the interruptId */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_0A;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_1A;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_2A;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_3A;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_4A;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_5A;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_0A;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_1A;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_2A;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_3A;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_4A;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_5A;
			break;
		default:
			
			return;
	}
	
	/* Disable Timeout interrupt */
	GPT_GPTMIMR(channelPtr).TATOIM = 0;
	
	/* Enable Interrupt for the dedicated channel from IntCtrl Module */
	IntCtrl_DisableInterrupt(interruptId);
}

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
void Gpt_EnableNotification(Gpt_Channel_t ChannelId)
{
	const Gpt_Channel_Config_t* ConfigPtr = &(GPT_Config.channels[ChannelId]);
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile Gpt_TimerInterruptType interruptId = 0;
	
	/* Determine the channel address and the interruptId */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_0A;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_1A;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_2A;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_3A;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_4A;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_5A;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_0A;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_1A;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_2A;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_3A;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_4A;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_5A;
			break;
		default:
			
			return;
	}
	
	/* Enable Timeout interrupt */
	GPT_GPTMIMR(channelPtr).TATOIM = 1;
	
	/* Enable Interrupt for the dedicated channel from IntCtrl Module */
	IntCtrl_EnableInterrupt(interruptId, ConfigPtr->priority);
}

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
void Gpt_StartTimer(Gpt_Channel_t ChannelId, Gpt_ValueType Value)
{
	const Gpt_Channel_Config_t* ConfigPtr = &(GPT_Config.channels[ChannelId]);
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile uint8_t timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			timerWidth = 64;
			break;
		default:
			
			return;
	}
	
	Value = Value * F_CPU;		/* value = value x 16 */
	uint8_t prescaler = 0;
	switch (timerWidth)
	{
		case 32:
			/* Set the starting count value */
			GPT_GPTMTAILR(channelPtr) = Value & (0x00000000FFFFFFFF);
			
			//set prescaler

			if (Value > (uint32_t)-1)	// Overflow => 2^(32), then need prescaler
			{
				GPT_GPTMTAPR(channelPtr) = prescaler & (0x0000FFFF);
			}
			
			break;
		case 64:
			
			/* Set the starting count value */
			GPT_GPTMTBILR(channelPtr) = ((Value) & (0xFFFFFFFF00000000))>>32;
			GPT_GPTMTAILR(channelPtr) = Value & (0x00000000FFFFFFFF);
			
			//set prescaler
			if (Value > (uint64_t)-1)	// Overflow => 2^(64), then need prescaler
			{
				GPT_GPTMTAPR(channelPtr) = prescaler & (0x0000FFFF);
			}
			
			break;
	}
	
	/* Starting the timer */
	GPT_GPTMCTL(channelPtr).TAEN = 1;
}

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
void Gpt_StopTimer(Gpt_Channel_t ChannelId)
{
	const Gpt_Channel_Config_t* ConfigPtr = &(GPT_Config.channels[ChannelId]);
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile uint8_t timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			break;
		default:
			
			return;
	}
	
	/* Clear Timer enable bit in GPTM control register */
	GPT_GPTMCTL(channelPtr).TAEN = 0;
}

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
Gpt_ValueType Gpt_GetTimepassed_(Gpt_Channel_t ChannelId)
{
	const Gpt_Channel_Config_t* ConfigPtr = &(GPT_Config.channels[ChannelId]);
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile uint8_t timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			timerWidth = 64;
			break;
		default:
			
			break;
	}
	
	if (timerWidth == 32)
	{
		uint32 passed_Time = GPT_GPTMTAV(channelPtr);
		passed_Time = passed_Time / F_CPU;		/* passed_Time = passed_Time / 16 */
		
		return passed_Time;
	}
	else if (timerWidth == 64)
	{
		uint64_t passed_Time = ((uint64_t)GPT_GPTMTBV(channelPtr) & (0x00000000FFFFFFFF))<<32;
		passed_Time |= GPT_GPTMTAV(channelPtr) & (0x00000000FFFFFFFF);
		passed_Time = passed_Time / F_CPU;		/* passed_Time = passed_Time / 16 */
		
		return passed_Time;
	}
	
	/* [TODO] Find another efficient way to indicate an error */
	return 0;
}

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
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_Channel_t ChannelId)
{
	const Gpt_Channel_Config_t* ConfigPtr = &(GPT_Config.channels[ChannelId]);
	
	volatile uint8_t* channelPtr = NULL_PTR;
	volatile uint8_t timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8_t*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8_t*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			timerWidth = 64;
			break;
		default:
			
			break;
	}
	
	if (timerWidth == 32)
	{
		uint32 passed_Time = GPT_GPTMTAV(channelPtr);
		passed_Time = passed_Time / F_CPU;		/* passed_Time = passed_Time / 16 */
		
		uint32 ovf_time_cnt = GPT_GPTMTAILR(channelPtr);
		
		uint32 remainingTime = ovf_time_cnt - passed_Time;
		
		return remainingTime;
	}
	else if (timerWidth == 64)
	{
		uint64_t passed_Time = ((uint64_t)GPT_GPTMTBV(channelPtr) & (0x00000000FFFFFFFF))<<32;
		passed_Time |= GPT_GPTMTAV(channelPtr) & (0x00000000FFFFFFFF);
		passed_Time = passed_Time / F_CPU;		/* passed_Time = passed_Time / 16 */
		
		uint64_t ovf_time_cnt = ((uint64_t)GPT_GPTMTBILR(channelPtr) & (0x00000000FFFFFFFF))<<32;
		ovf_time_cnt |= GPT_GPTMTAILR(channelPtr) & (0x00000000FFFFFFFF);
		
		uint64_t remainingTime = ovf_time_cnt - passed_Time;
		
		return remainingTime;
	}
	
	/* [TODO] Find another efficient way to indicate an error */
	return 0;
}


/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/
