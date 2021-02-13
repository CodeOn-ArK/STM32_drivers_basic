/*
 * 001ToggleLed.c
 *
 *  Created on: Feb 1, 2021
 *      Author: ark
 */
#if 0
#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"

void delay()
{
	for(uint32_t i = 0; i < 500000 ;i++ );
}
int main()
{
	GPIO_handle_t ledPin;

	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	ledPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_PeriClkCntrl(GPIOA, ENABLE);
	GPIO_Init(&ledPin);

	while(1)
	{
		GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
		delay();
	}
	return 0;
}

#endif


