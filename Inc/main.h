/*
 * main.h
 *
 *  Created on: 29-May-2021
 *      Author: root
 */

#ifndef MAIN_H_
#define MAIN_H_

#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"

void delay()
{
	for(uint32_t i=0; i<300000; i++);
}

void GPIO_ButtonConfig()
{
	GPIO_handle_t led, button;

	led.pGPIOx = GPIOA;
	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIOA_CLK_EN();
	GPIO_Init(&led);

	button.pGPIOx = GPIOC;
	button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIOC_CLK_EN();
	GPIO_Init(&button);
}


#endif /* MAIN_H_ */
