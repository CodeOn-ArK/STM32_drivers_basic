/*
 * 005spi_Tx_only.c
 *
 *  Created on: 11-Jan-2021
 *      Author: KIIT
 */
#if 0
#include "stm32f446xx.h"
#include "stm32f446xx_spi.h"
#include "stm32f446xx_gpio.h"
#include <string.h>

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

	GPIO_handle_t SPI_pin ;
	memset(&SPI_pin, 	0,	sizeof(SPI_pin));

	SPI_pin.pGPIOx = GPIOB;
	SPI_pin.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI_pin.GPIO_PinConfig.GPIO_PinMode = GPIO_ALT_FN;
	SPI_pin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI_pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	SPI_pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//NSS
	//SPI_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	//GPIO_Init(&SPI_pin);

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
	SPI_Handle_t SPI2Handle;
	memset(&SPI2Handle, 0, sizeof(SPI2Handle));

	SPI2Handle.pSPIx = SPI2;

	SPI2Handle.SPIConfig.SPI_BusConfig 	= SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_DFF 		= SPI_DFF_8;
	SPI2Handle.SPIConfig.SPI_SclkSpeed 	= SPI_SCLK_SPEED_DIV8;
	SPI2Handle.SPIConfig.SPI_SSM 		= SPI_SSM_EN;
	SPI2Handle.SPIConfig.SPI_CPOL       = SPI_CPOL_LOW;

	SPI_Init(&SPI2Handle);

}

int main()
{
	char user_data[] = "Hello World How are you";

	SPI2_GPIOInits();

	SPI2_Inits();

	SPI_Enable(SPI2, ENABLE);

	SPI_SendData(SPI2, (uint8_t *)user_data, sizeof(user_data));

	while(1);
}
#endif
