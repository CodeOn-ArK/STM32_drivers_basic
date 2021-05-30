/*
 * 012UART_Tx.c
 *
 *  Created on: 25-Feb-2021
 *      Author: ArK
 */

#if 0

#include<stdio.h>
#include<string.h>
#include "stm32f446xx.h"
#include "main.h"

USART_Handle_t usart2_handle;

void USART2_Init(void)
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_9600;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_2;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle);
}

void 	USART2_GPIOInit(void)
{
	GPIO_handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_ALT_FN;
	usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

	//USART2 TX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_2;
	GPIO_Init(&usart_gpios);

	//USART2 RX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
	GPIO_Init(&usart_gpios);

	//USART@ CLK
	//usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
	//GPIO_Init(&usart_gpios);


}


int main(void)
{

	GPIO_ButtonConfig();

	USART2_GPIOInit();

    USART2_Init();

    USART_PeripheralControl(USART2,ENABLE);

    uint8_t pRxBuffer[10] = "Hello\n\r";

    while(1)
    {
       	//wait till button is pressed
		while(  GPIO_ReadIPin(GPIOC, GPIO_PIN_12) != GPIO_PIN_RESET );

		delay();
		USART_SendData(&usart2_handle, (uint8_t *)pRxBuffer, strlen((char *)pRxBuffer));

    }
}

#endif
