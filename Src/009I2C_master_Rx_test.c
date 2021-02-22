/*
 * 009I2C_master_Rx_test.c
 *
 *  Created on: 12-Feb-2021
 *      Author: ark
 */
#if 0

#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"
#include"stm32f446xx_i2c.h"

#include<string.h>
#include<stdint.h>

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

I2C_Handle_t I2C1Handle;
uint8_t pRxBuffer[40];

#define MASTERS_ADDRESS 	 0x38
#define SLAVE_ADDR  0x68

void delay()
{
	for(uint32_t i=0; i<300000; i++);
}

void I2C1_GPIOInits()
{
	GPIO_handle_t 	I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_ALT_FN;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	//SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber  =  GPIO_PIN_10;
	GPIO_Init(&I2CPins);

	//SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber  =  GPIO_PIN_3;
	GPIO_Init(&I2CPins);

}

void I2C1_Inits()
{

	I2C1Handle.pI2Cx  = I2C2;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_EN;
	I2C1Handle.I2C_Config.I2C_DeviceAddress  =  MASTERS_ADDRESS;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}

void GPIO_BtnLedInit(void)
{
	GPIO_handle_t GPIOBtn, GPIOLed;

	//GPIO btn conifg
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIOBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GPIO_Init(&GPIOBtn);

	//GPIO LED config
	GPIOLed.pGPIOx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GPIO_Init(&GPIOLed);

}
int main()
{

	//GPIO Button Init
	GPIO_BtnLedInit();

	//I2C pin inits
	I2C1_GPIOInits();

	//I2C peripheral config
	I2C1_Inits();

	uint8_t cmnd_send, cmnd_read;

	I2C_Init(&I2C1Handle);
	I2C_Enable(I2C1Handle.pI2Cx, ENABLE);

	while(1)
	{
		cmnd_send = (uint8_t)0x51;
		cmnd_read = (uint8_t)0x52;

		if( !GPIO_ReadIPin(GPIOA, GPIO_PIN_10) )
		{
			delay();
			I2C_MasterSendData( &I2C1Handle, &cmnd_send, 1,SLAVE_ADDR ); // Send Command to Arduino to instruct it to send the length of the information

			I2C_MasterRecieveData(&I2C1Handle, pRxBuffer, 1, SLAVE_ADDR); //Recieve Command from Arduino

			I2C_MasterSendData(&I2C1Handle, &cmnd_read, 1, SLAVE_ADDR);

			I2C_MasterRecieveData(&I2C1Handle, pRxBuffer, I2C1Handle.RxSize, SLAVE_ADDR);

		}
	}
}


#endif
