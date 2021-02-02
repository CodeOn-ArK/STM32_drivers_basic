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

static int count =0;
void GPIO_IRQHandling(uint8_t);

void delay(uint32_t x)
{
	for(uint32_t t = 0; t < x*100000; t++);
}
int main()
{
	GPIO_handle_t led, button;
	memset(&led, 0, sizeof(led));
	memset(&button, 0, sizeof(button));

	led.pGPIOx = GPIOA;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_PeriClkCntrl(GPIOA, ENABLE);
	GPIO_Init(&led);

	button.pGPIOx = GPIOA;
	button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_PeriClkCntrl(GPIOB, ENABLE);
	GPIO_Init(&button);

	button.pGPIOx = GPIOA;
	button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_8;
	button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init(&button);

	GPIO_IRQConfig(IRQ_NO_EXTI15_10, 2);		//LOWER THE IRQ NUMBER HIGHER THE PRIORITY
	GPIO_IRQ_ITConfig(IRQ_NO_EXTI15_10, ENABLE);

	GPIO_IRQConfig(IRQ_NO_EXTI9_5, 4);		//IF IRQ NUMBER NOT SET IT DEFAULTS TO 0
	GPIO_IRQ_ITConfig(IRQ_NO_EXTI9_5, ENABLE);

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

			case 3: 	Reset_Handler();//GPIO_WriteOPin(GPIOA, GPIO_PIN_5, SET);
							break;
		};
	}
}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_10);
	//GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
	delay(3);
	count++;
	if(count > 2) count = 0;
}

void EXTI9_5_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_8);
	count = 3;
}


#endif
