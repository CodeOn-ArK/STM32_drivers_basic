/*
 * 008I2C_master_Tx_test.c
 *
 *  Created on: 11-Feb-2021
 *      Author: ArK
 */

#if 0
#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"
#include"stm32f446xx_i2c.h"
#include"string.h"
#include"stdint.h"
#include "main.h"

/*
 * I2C peripheral initialization:
 *
 * SDA: PB9
 * SCL: PB6
 *
 * AF: 4
 */
void delay();
void I2C1_GPIOInits();
void I2C1_Inits();

#define MASTERS_ADDRESS 	 0x38		//Set the master address here
#define SLAVE_ADDR  		0x68		//Set the slave address here

uint8_t data[] = "Testing I2C @#??";

//global I2C handle variable
I2C_Handle_t I2C1Handle;


void I2C1_GPIOInits()
{
	//Initialize the GPIO pins to be used with I2C peripheral
	GPIO_handle_t 	I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_ALT_FN;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;			//Always keep this pulled up

	//SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber  =  GPIO_PIN_3;
	GPIO_Init(&I2CPins);

	//SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber  =  GPIO_PIN_10;
	GPIO_Init(&I2CPins);



}

void I2C1_Inits()
{

	//Initiliaze the I2C peripheral
	I2C1Handle.pI2Cx  = I2C2;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_EN;
	I2C1Handle.I2C_Config.I2C_DeviceAddress  =  MASTERS_ADDRESS;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}

int main()
{

	//GPIO Button Init
	GPIO_ButtonConfig();

	//I2C pin initsI2C1Handle
	I2C1_GPIOInits();

	//I2C peripheral config
	I2C1_Inits();

	//Enable the Peripheral
	I2C_Enable( I2C2 , ENABLE);

	while(1)
	{
		if( GPIO_ReadIPin(GPIOC, GPIO_PIN_12) == GPIO_PIN_SET)
		{//Send data
			delay();

			I2C_MasterSendData( &I2C1Handle, data, strlen((char*)data), SLAVE_ADDR );

			GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
		}
	}
}
#endif
