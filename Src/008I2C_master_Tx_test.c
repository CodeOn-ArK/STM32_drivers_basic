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
void I2C1_GPIOInits();
void I2C1_Inits();

#define MASTERS_ADDRESS 	 0x38
#define SLAVE_ADDR  0x68

uint8_t data[] = "Testing I2C @#??";

I2C_Handle_t I2C1Handle;

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
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	//SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber  =  GPIO_PIN_9;
	GPIO_Init(&I2CPins);

	//SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber  =  GPIO_PIN_6;
	GPIO_Init(&I2CPins);



}

void I2C1_Inits()
{

	I2C1Handle.pI2Cx  = I2C1;
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
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIO_Init(&GPIOBtn);

	//GPIO LED config
	GPIOLed.pGPIOx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GPIOLed);

}
int main()
{

	//GPIO Button Init
	GPIO_BtnLedInit();

	//I2C pin initsI2C1Handle
	I2C1_GPIOInits();

	//I2C peripheral config
	I2C1_Inits();

	I2C_Enable( I2C1 , ENABLE);
	while(1)
	{
		if( !GPIO_ReadIPin(GPIOA, GPIO_PIN_10) )
		{//Send data
			delay();

			I2C_MasterSendData( &I2C1Handle, data, strlen((char*)data), SLAVE_ADDR );

			GPIO_ToggleOPin(GPIOA, GPIO_PIN_5);
		}
	}
}
#endif
