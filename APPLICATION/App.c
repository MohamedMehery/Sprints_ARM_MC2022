#include "App.h"
#include "Input.h"
#include "Blink.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
void Blinking_led(void)
{
	Led_Toggle(deviceChannel);
	flag = 1;
}

void set_call_back(timer_cb_t* tm_cb)
{
	*tm_cb = Blinking_led;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
int main(void)
{
	uint8_t on_period = 0, off_period = 0; 
	timer_cb_t tm_cb ;
	set_call_back(&tm_cb);

	while(1)
	{
		on_period = get_pulse_timing(button1, LED_2, button2, LED_3, PULL_UP);
		off_period = get_pulse_timing(button1, LED_2, button2, LED_3, PULL_UP);		
		led_blink(BLINKING_GPTM, LED_1, TIMEOUT, on_period, off_period, tm_cb);
	}

	return 0;
}