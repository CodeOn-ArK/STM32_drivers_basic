/*
 * 004Interrupt.c
 *
 *  Created on: 06-Jan-2021
 *      Author: KIIT
 */

#if 0
#include<stdint.h>
#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"
#include<string.h>

static volatile int count =0;
void GPIO_IRQHandling(uint8_t);

void delay(uint32_t x)
{
	for(uint32_t t = 0; t < x*100000; t++);
}

int main()
{
	//Defining Handle structure variables for button && led
	GPIO_handle_t led, button;

	//Init the structures to 0
	memset(&led, 0, sizeof(led));
	memset(&button, 0, sizeof(button));

	//Structure configuration for the LED pin
	led.pGPIOx = GPIOA;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//Enabling the clock
	GPIO_PeriClkCntrl(GPIOA, ENABLE);
	//Initialize the GPIOs with the corresponding structures
	GPIO_Init(&led);

	//Structure configuration for the BUTTON pin
	button.pGPIOx = GPIOA;
	button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//Initialize the GPIOs with the corresponding structures
	GPIO_Init(&button);

	//Configuring the IRQ line for PA10; setting the IRQ priority
	GPIO_IRQConfig(IRQ_NO_EXTI15_10, 2);		//LOWER THE IRQ NUMBER HIGHER THE PRIORITY
	//Enabling the IRQ line
	GPIO_IRQ_ITConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1)
	{
		switch(count)
		{
			case 0:	GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
					delay(1);
					break;

			case 1:	GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
					delay(5);
					break;

			case 2:	GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
					delay(10);
					break;
		};
	}
}

void EXTI15_10_IRQHandler(void)
{
	//GPIO IRQ Handler; This is used for clearing the IRQ pending register bit
	GPIO_IRQHandling(GPIO_PIN_10);

	count++;
	if(count > 2) count = 0;
}

#endif
