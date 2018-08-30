#include "s6e2ccxj.h"
#include "pins.h"

int io_example(void)
{
	/*
	Configure the pin of the blue LED as output by setting the corresponding
	bit in the Data Direction Register (DDR).
	*/
	LED_BLUE_DDR |= (1 << LED_BLUE_PIN);
	/*
	Set the pin to 1 by setting the corresponding bit in the Data Output
	Register (DOR). This turns the LED off.
	*/
	LED_BLUE_DOR |= (1 << LED_BLUE_PIN);

	/*
	Configure the pin of the left Joystick Button as output by clearing the corresponding
	bit in the Data Direction Register (DDR).
	*/
	BUTTON_LEFT_DDR &= ~(1 << BUTTON_LEFT_PIN);
	/*
	Enable the pull-up resistor in the pin by setting the corresponding bit
	in the Pullup Configuration Register (PCR).
	*/
	BUTTON_LEFT_PCR |= (1 << BUTTON_LEFT_PIN);

	/*
	Check the pin status by combining the Data Input Register (DIR) with the
	corresponding bitmask.
	The expression is inverted because the pin is 0 when the button is pressed.
	*/
	if(!(BUTTON_LEFT_DIR & (1 << BUTTON_LEFT_PIN))) {
		/*
		Toggle the LED when the button is pressed. Toggling is done by XORing
		the current pin state with 1.
		*/
 		LED_BLUE_DOR ^= (1 << LED_BLUE_PIN);
	}
}
