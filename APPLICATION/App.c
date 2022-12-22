#include "App.h"
#include "Input.h"
#include "Blink.h"

int main(void)
{
	uint8_t on_period = get_pulse_timing(button1, LED_2, button2, LED_3, PULL_UP);
	uint8_t off_period = get_pulse_timing(button1, LED_2, button2, LED_3, PULL_UP);
	
	while(1)
	{
		led_blink(BLINKING_GPTM, LED_1, TIMEOUT, on_period, off_period);
	}

	return 0;
}