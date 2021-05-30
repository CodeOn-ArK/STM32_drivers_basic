/*
 * 005spi_Tx_only.c
 *
 *  Created on: 11-Jan-2021
 *      Author: ArK
 */
#if 0
#include "stm32f446xx.h"
#include <string.h>
#include"main.h"

/*
 * PB12 -->	SPI2_NSS
 * PB13 --> SPI2_SCK
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 *
 * AF MODE 5
 * PORT B
 */
void SPI2_GPIOInits()
{

	//GPIO Handle for initializing the SPI pins
	GPIO_handle_t SPI_pin ;
	memset(&SPI_pin, 	0,	sizeof(SPI_pin));

	SPI_pin.pGPIOx = GPIOB;
	SPI_pin.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI_pin.GPIO_PinConfig.GPIO_PinMode = GPIO_ALT_FN;
	SPI_pin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI_pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;				//Always keep it low
	SPI_pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//NSS
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	GPIO_Init(&SPI_pin);

	//SCK
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	GPIO_Init(&SPI_pin);

	//MISO
	//SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
	//GPIO_Init(&SPI_pin);

	//MOSI
	SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
	GPIO_Init(&SPI_pin);

}

void SPI2_Inits()
{
	//SPI handle to initiate the SPI peripheral conencted to the corresponding GPIOs
	SPI_Handle_t SPI2Handle;
	memset(&SPI2Handle, 0, sizeof(SPI2Handle));

	SPI2Handle.pSPIx = SPI2;

	SPI2Handle.SPIConfig.SPI_BusConfig 	= SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_DFF 		= SPI_DFF_8;
	SPI2Handle.SPIConfig.SPI_SclkSpeed 	= SPI_SCLK_SPEED_DIV16;
	SPI2Handle.SPIConfig.SPI_SSM 		= SPI_SSM_EN;
	SPI2Handle.SPIConfig.SPI_CPOL       = SPI_CPOL_LOW;

	SPI_Init(&SPI2Handle);

}

int main()
{
	char user_data[] = "Hello World How are you";

	GPIO_ButtonConfig();

	//Set GPIO to use SPI peripherals
	SPI2_GPIOInits();

	//Initialize the SPI peripheral
	SPI2_Inits();

	//This is required for SSM, makes the NSS pin HIGH while inactive and not floating state
	SSI_Config(SPI2, ENABLE);						//If SSM is not used and slave is managed through Hardware than disable this

	//Start the SPI peripheral
	SPI_Enable(SPI2, ENABLE);

	//Hang in here until button is pressed; done to eliminate noise due to RESET
	while( GPIO_ReadIPin(GPIOC, GPIO_PIN_12) == GPIO_PIN_SET );

	//Send data
	SPI_SendData(SPI2, (uint8_t *)user_data, sizeof(user_data));

	//lets confirm SPI is not busy
	while( SPI_GetFagStatus(SPI2,SPI_BUSY_FLAG) );

	//Disable the SPI2 peripheral
	SPI_Enable(SPI2,DISABLE);

	//Hang in here forever
	while(1);

}
#endif
