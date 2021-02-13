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
	GPIO_handle_t ledPin, buttonPin;

	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	ledPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	buttonPin.pGPIOx = GPIOA;
	buttonPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	buttonPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	buttonPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	buttonPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_PeriClkCntrl(GPIOA, ENABLE);

	GPIO_Init(&ledPin);
	GPIO_Init(&buttonPin);

	while(1)
	{
		if(!GPIO_ReadIPin(GPIOA, GPIO_PIN_10))
		{
			delay(4);
			GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
		}
	}

	return 0;
}

#endif
