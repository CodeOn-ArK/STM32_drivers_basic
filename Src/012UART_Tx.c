/*
 * 012UART_Tx.c
 *
 *  Created on: 25-Feb-2021
 *      Author: ark
 */

<<<<<<< HEAD:Src/012UART_Tx.c
#if 0
=======
#if 1
>>>>>>> 9d1a9ec7eff5dc8fb1ff5caf7b81dbb91691ab2a:Src/015uart_tx.c

#include<stdio.h>
#include<string.h>
#include "stm32f446xx.h"

<<<<<<< HEAD:Src/012UART_Tx.c
uint8_t msg[] = "UART " ;
=======
>>>>>>> 9d1a9ec7eff5dc8fb1ff5caf7b81dbb91691ab2a:Src/015uart_tx.c

USART_Handle_t usart2_handle;

void USART2_Init(void)
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_9600;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
<<<<<<< HEAD:Src/012UART_Tx.c
	usart2_handle.USART_Config.USART_Mode = USART_MODE_TXRX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
=======
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_2;
>>>>>>> 9d1a9ec7eff5dc8fb1ff5caf7b81dbb91691ab2a:Src/015uart_tx.c
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
<<<<<<< HEAD:Src/012UART_Tx.c
=======
	GPIO_Init(&usart_gpios);

	//USART@ CLK
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
>>>>>>> 9d1a9ec7eff5dc8fb1ff5caf7b81dbb91691ab2a:Src/015uart_tx.c
	GPIO_Init(&usart_gpios);

	//USART@ CLK
	//usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
	//GPIO_Init(&usart_gpios);




}

void GPIO_ButtonInit(void)
{
	GPIO_handle_t GPIOBtn,GpioLed;

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&GPIOBtn);

	//this is led gpio configuration
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClkCntrl(GPIOA,ENABLE);

	GPIO_Init(&GpioLed);

}

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}


int main(void)
{

	GPIO_ButtonInit();

	USART2_GPIOInit();

    USART2_Init();

    USART_PeripheralControl(USART2,ENABLE);

<<<<<<< HEAD:Src/012UART_Tx.c
    uint8_t pRxBuffer[10];
    while(1)
    {
       		//wait till button is pressed
		//while(  GPIO_ReadIPin(GPIOA, GPIO_PIN_10));

		char count = '1';
    	USART_ReceiveData(&usart2_handle, pRxBuffer, 5);
=======
    uint8_t msg[] = "UART ";

    while(1)
    {
		//wait till button is pressed
		while(  GPIO_ReadIPin(GPIOA, GPIO_PIN_10));
>>>>>>> 9d1a9ec7eff5dc8fb1ff5caf7b81dbb91691ab2a:Src/015uart_tx.c

    	if(!strcmp((char *)pRxBuffer, "hello"))
    	{
		//to avoid button de-bouncing related issues 200ms of delay
    		delay();

<<<<<<< HEAD:Src/012UART_Tx.c
    		USART_SendData(&usart2_handle,msg,strlen((char *)msg));
    		GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);

    		count++;

    		strcpy(pRxBuffer, "'\0''\0''\0''\0''\0''\0'");
    		//USART_SendData(&usart2_handle, (uint8_t *)count, 0);
    	}
=======
		USART_SendData(&usart2_handle,msg,strlen((char *)msg));
>>>>>>> 9d1a9ec7eff5dc8fb1ff5caf7b81dbb91691ab2a:Src/015uart_tx.c

    }

	return 0;
}

#endif
