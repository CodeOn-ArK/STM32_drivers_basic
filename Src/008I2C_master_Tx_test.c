/*
 * 008I2C_master_Tx_test.c
 *
 *  Created on: 11-Feb-2021
 *      Author: ark
 */

#if 1
#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"
#include"stm32f446xx_i2c.h"
#include"string.h"
#include"stdint.h"

/*
 * I2C peripheral initialization:
 *
 * SDA: PB9
 * SCL: PB6
 *
 * AF: 4
 */
void delay();
void I2C2_GPIOInits();
void I2C2_Inits();

I2C_Handle_t I2C2Handle;
#define MASTERS_ADDRESS 	 0x38
#define SLAVE_ADDR  0x68

uint8_t data[] = "Testing I2C @#??";

void delay()
{
	for(uint32_t i=0; i<300000; i++);
}

void I2C2_GPIOInits()
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

void I2C2_Inits()
{

	I2C2Handle.pI2Cx  = I2C2;
	I2C2Handle.I2C_Config.I2C_ACKControl = I2C_ACK_EN;
	I2C2Handle.I2C_Config.I2C_DeviceAddress  =  MASTERS_ADDRESS;
	I2C2Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C2Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C2Handle);
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
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIO_Init(&GPIOBtn);

	//GPIO LED config
	GPIOLed.pGPIOx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIO_Init(&GPIOLed);

}
int main()
{

	//GPIO Button Init
	GPIO_BtnLedInit();

	//I2C pin inits
	I2C2_GPIOInits();

	//I2C peripheral config
	I2C2_Inits();

	void I2C_Enable( I2C2Handle, ENABLE);
	while(1)
	{
		if( !GPIO_ReadIPin(GPIOA, GPIO_PIN_10) )
		{//Send data
			delay();
			I2C_MasterSendData( &I2C2Handle, data, strlen((char*)data), SLAVE_ADDR );
		}
	}
}
#endif