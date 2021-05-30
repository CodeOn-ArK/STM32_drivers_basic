/*
 * 005spi_Tx_only.c
 *
 *  Created on: 11-Jan-2021
 *      Author: ArK
 */
#if 0
#include "stm32f446xx.h"
#include "stm32f446xx_spi.h"
#include "stm32f446xx_gpio.h"
#include <string.h>
#include "main.h"

/*
 * PB12 -->	SPI2_NSS
 * PB13 --> SPI2_SCK
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 *
 * AF MODE 5
 * PORT B
 */
//command codes
#define COMMAND_LED_CTRL      		0x50
#define COMMAND_SENSOR_READ      	0x51
#define COMMAND_LED_READ      		0x52
#define COMMAND_PRINT      			0x53
#define COMMAND_ID_READ      		0x54

#define LED_ON     1
#define LED_OFF    0

//arduino analog pins
#define ANALOG_PIN0 	0
#define ANALOG_PIN1 	1
#define ANALOG_PIN2 	2
#define ANALOG_PIN3 	3
#define ANALOG_PIN4 	4

//arduino led

#define LED_PIN  9


uint8_t SPI_Verify(int response);
void delay(int i);
void SPI2_GPIOInits();
void SPI2_Inits();

void delay(int i)
{
	for( int x = i; i < x*100000 ; i ++);
}

void SPI2_GPIOInits()
{

	GPIO_handle_t SPI_pin ;
	memset(&SPI_pin, 	0,	sizeof(SPI_pin));

	SPI_pin.pGPIOx = GPIOB;
	SPI_pin.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI_pin.GPIO_PinConfig.GPIO_PinMode = GPIO_ALT_FN;
	SPI_pin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI_pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	SPI_pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//NSS
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GPIO_Init(&SPI_pin);

	//SCK
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	GPIO_Init(&SPI_pin);

	//MISO
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
	GPIO_Init(&SPI_pin);

	//MOSI
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
	GPIO_Init(&SPI_pin);

}

void SPI2_Inits()
{
	SPI_Handle_t SPI2Handle;
	memset(&SPI2Handle, 0, sizeof(SPI2Handle));

	SPI2Handle.pSPIx = SPI2;

	SPI2Handle.SPIConfig.SPI_BusConfig 	= SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_DFF 		= SPI_DFF_8;
	SPI2Handle.SPIConfig.SPI_SclkSpeed 	= SPI_SCLK_SPEED_DIV8;
	SPI2Handle.SPIConfig.SPI_SSM 		= SPI_SSM_DI;
	SPI2Handle.SPIConfig.SPI_CPOL       = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA		= SPI_CPHA_LOW;

	SPI_Init(&SPI2Handle);

}

uint8_t SPI_Verify(int response)
{
	if(response == 0xF5)
	{
		//ACK
		return 1;
	}
	else{
		//NACK
		return 0;
	}
}

int main()
{
	uint8_t dummy_write = 0xff, dummy_read, analog_read;
	uint8_t rec_byte;
	uint8_t args[2];

	GPIO_ButtonConfig();

	SPI2_GPIOInits();
	SPI2_Inits();

	/*
	* making SSOE 1 does NSS output enable.
	* The NSS pin is automatically managed by the hardware.
	* i.e when SPE=1 , NSS will be pulled to low
	* and NSS pin will be high when SPE=0
	*/
	SSOE_Config(SPI2, ENABLE);

	while(1)
	{
		//WAIT TILL BUTTON IS PRESSED
		while( (GPIO_ReadIPin(GPIOC, GPIO_PIN_12)) );

		//DELAY TO COMPENSATE BUTTON DEBOUNCING
		delay(5);

		//ENABLE THE SPI2 PERIPHERAL
		SPI_Enable(SPI2, ENABLE);

		//1. CMD_LED_CTRL  <PIN_NO>		<VALUE>
		uint8_t CmndCode = COMMAND_LED_CTRL;

		//SEND THE DATA TO THE ARDUINO SLAVE
		SPI_SendData(SPI2, &CmndCode, 1);

		//READ THE DUMMY VAR RECEIVED -- IF NOT READ IT WILL SET THE RXNE BIT
		SPI_RecieveData(SPI2, &dummy_read, 1);

		//SEND DUMMY DATA TO FETCH THE RESPONSE FROM THE SLAVE -- THE SLAVE WILL NOT INITIATE DATA TRANSFER THE MASTER HAS TO FETCH
		//BY SENDING DUMMY DATA
		SPI_SendData(SPI2, &dummy_write, 1);

		//AFTER SENDING DUMMY DATA THE MASTER WOULD HAVE RECIEVED THE SLAVE RESPONSE
		//THE RESPONSE HAS TO BE READ NOW
		SPI_RecieveData(SPI2, &rec_byte, 1);

		if( SPI_Verify(rec_byte))
		{
			//SEND ARGS
			args[0] = LED_PIN;
			args[1] = LED_ON;
			SPI_SendData(SPI2, args, 2);
		}

		/* CMD <SENSOR READ> */

		//WAIT TILL BUTTON IS PRESSED
	while( (GPIO_ReadIPin(GPIOC, GPIO_PIN_12)) ){};

		//DELAY TO COMPENSATE BUTTON DEBOUNCING
		delay(5);

		CmndCode = COMMAND_SENSOR_READ;

		//SEND THE DATA TO THE ARDUINO SLAVE
		SPI_SendData(SPI2, &CmndCode, 1);

		//READ THE DUMMY VAR RECEIVED -- IF NOT READ IT WILL SET THE RXNE BIT
		SPI_RecieveData(SPI2, &dummy_read, 1);

		//SEND DUMMY DATA TO FETCH THE RESPONSE FROM THE SLAVE -- THE SLAVE WILL NOT INITIATE DATA TRANSFER THE MASTER HAS TO FETCH
		//BY SENDING DUMMY DATA
		SPI_SendData(SPI2, &dummy_write, 1);

		//AFTER SENDING DUMMY DATA THE MASTER WOULD HAVE RECIEVED THE SLAVE RESPONSE
		//THE RESPONSE HAS TO BE READ NOW
		SPI_RecieveData(SPI2, &rec_byte, 1);

		if( SPI_Verify(rec_byte))
		{
			//SEND ARGS
			args[0] = ANALOG_PIN0;
			SPI_SendData(SPI2, args, 1);

			//READ THE DUMMY VAR RECEIVED -- IF NOT READ IT WILL SET THE RXNE BIT
			SPI_RecieveData(SPI2, &dummy_read, 1);

			//INSERT DELAY SUCH THAT ADC IS READY WITH THE CONVERSION
			delay(1);

			//SEND DUMMY DATA TO FETCH THE RESPONSE FROM THE SLAVE -- THE SLAVE WILL NOT INITIATE DATA TRANSFER THE MASTER HAS TO FETCH
			//BY SENDING DUMMY DATA
			SPI_SendData(SPI2, &dummy_write, 1);

			//READ THE RECIEVED DATA INPUT
			SPI_RecieveData(SPI2, &analog_read, 1);
		}

		/*
		 * 3. COMMAND_LED_READ  <send_PIN_NO> <rec_VALUE>
		 */

		//WAIT TILL BUTTON IS PRESSED
	while( (GPIO_ReadIPin(GPIOC, GPIO_PIN_12)) ){};

		//DELAY TO COMPENSATE BUTTON DEBOUNCING
		delay(5);

		CmndCode = COMMAND_LED_READ;

		SPI_SendData(SPI2, &CmndCode, 1);

		SPI_RecieveData(SPI2, &dummy_read, 1);

		SPI_SendData(SPI2, &dummy_write, 1);

		SPI_RecieveData(SPI2, &rec_byte, 1);

		if( SPI_Verify(rec_byte))
		{
			args[0] = LED_PIN;

			SPI_SendData(SPI2, args, 1);

			SPI_RecieveData(SPI2, &dummy_read, 1);

			SPI_SendData(SPI2, &dummy_write, 1);

			SPI_RecieveData(SPI2, &rec_byte, 1);
		}

		/*
		 * 4. COMMAND_PRINT  <send_ID>
		 */

		//WAIT TILL BUTTON IS PRESSED
	while( (GPIO_ReadIPin(GPIOC, GPIO_PIN_12)) ){};

		//DELAY TO COMPENSATE BUTTON DEBOUNCING
		delay(5);

		CmndCode = COMMAND_PRINT;

		SPI_SendData(SPI2, &CmndCode, 1);

		SPI_RecieveData(SPI2, &dummy_read, 1);

		SPI_SendData(SPI2, &dummy_write, 1);

		SPI_RecieveData(SPI2, &rec_byte, 1);

		if( SPI_Verify(rec_byte))
		{
			char message[] = "Hello ! How are you ??";

			args[0] = strlen(message);

			//send arguments
			SPI_SendData(SPI2,args,1); //sending length

			//send message
			SPI_SendData(SPI2,(uint8_t *)message,args[0]);
		}

		/*
		 * 5. COMMAND_ID_READ  <rec_ID>
		 */
		//WAIT TILL BUTTON IS PRESSED
	while( (GPIO_ReadIPin(GPIOC, GPIO_PIN_12)) ){};

		//DELAY TO COMPENSATE BUTTON DEBOUNCING
		delay(5);

		CmndCode = COMMAND_ID_READ;

		SPI_SendData(SPI2, &CmndCode, 1);

		SPI_RecieveData(SPI2, &dummy_read, 1);

		SPI_SendData(SPI2, &dummy_write, 1);

		SPI_RecieveData(SPI2, &rec_byte, 1);

		if( SPI_Verify(rec_byte))
		{
			char *RecieveByte;

			for(uint8_t i=0; i<10; i++)
			{
				SPI_SendData(SPI2, &dummy_write, 1);
				SPI_RecieveData(SPI2, &rec_byte, 1);

				*(RecieveByte++) = (char)rec_byte;
			}
		}

		//CONFIRM SPI IS NOT BUSY
	    while( !SPI_GetFagStatus(SPI2, SPI_SR_BSY) );

	    //DISABLE THE SPI PERIPHERAL
	    SPI_Enable(SPI2, DISABLE);
	}

}
#endif
