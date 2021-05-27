/*
 * 002led_button.c
 *
 *  Created on: 04-Jan-2021
 *      Author: KIIT
 */
#if 0
#include"stm32f446xx.h"

void delay(int x)
{
	for(uint32_t i = 0; i < x*100000; i++);
}

int main()
{
	//Defined Handle variables to contain GPIO configs for button and LED
	GPIO_handle_t ledPin, buttonPin;

	//Structure configuration for the LED pin
	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	ledPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//Structure configuration for the button pin
	buttonPin.pGPIOx = GPIOA;
	buttonPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	buttonPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	buttonPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	buttonPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	buttonPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//Enabling the clock
	GPIO_PeriClkCntrl(GPIOA, ENABLE);

	//Initialize the GPIOs with the corresponding structures
	GPIO_Init(&ledPin);
	GPIO_Init(&buttonPin);

	//while loop to poll the input pin continuously && toggle the LED when switch is pressed
	while(1)
	{
		//read PA10
		if(!GPIO_ReadIPin(GPIOA, GPIO_PIN_10))
		{
			//Delay 4ms
			delay(4);
			//Toggle the O/P pin PA5
			GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
		}
	}

	return 0;
}

#endif
