/*
 * 011I2C_Slave_Tx_string.c
 *
 *  Created on: Feb 21, 2021
 *      Author: ark
 */


#if 1

#include"stm32f446xx.h"

#include<string.h>
#include<stdint.h>
#include<stdio.h>

//extern void initialise_monitor_handles();
/*
 * I2C peripheral initialization:
 *
 *We will be using **I2C2**
 *
 * SDA: PB3
 * SCL: PB10
 *
* AF: 4
 */
void delay();
void I2C2_GPIOInits();
void I2C2_Inits();

I2C_Handle_t I2C2Handle;
uint8_t pTxBuffer[] = "STM32_SLaVe 04588\n";
uint8_t cmnd_code = 0, Cnt = 0;

#define SLAVE_ADDR  0x68
#define MY_ADDR		SLAVE_ADDR

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
	I2C2Handle.I2C_Config.I2C_DeviceAddress  =  MY_ADDR;
	I2C2Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C2Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
	I2C2Handle.TxRxState = I2C_READY;

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

	//initialise_monitor_handles();

	//printf("Application is Running!\n");

	//GPIO Button Init
	GPIO_BtnLedInit();

	//I2C pin inits
	I2C2_GPIOInits();

	//I2C peripheral config
	I2C2_Inits();

	//I2C IRQ config
	I2C_IRQ_ITConfig(IRQ_NO_I2C2_EV, ENABLE);
	I2C_IRQ_ITConfig(IRQ_NO_I2C2_ER, ENABLE);

	I2C_SlaveEnDiCallBackEvents(I2C2, ENABLE );

	I2C_Init(&I2C2Handle);

	I2C2Handle.pI2Cx->CR1 |= (0x1 << I2C_CR1_ACK);

	while(1){}
}

void I2C2_EV_IRQHandler()
{
	I2C_EV_IRQHandling(&I2C2Handle);
}

void I2C2_ER_IRQHandler()
{
	I2C_ER_IRQHandling(&I2C2Handle);
}


void I2C_AppEventCallback(I2C_Handle_t *pI2CHandle, uint8_t I2C_Event)
{
	if(I2C_Event == I2C_EV_DATA_REQUEST)
	{
		//Master wants data, Slave has to send it
		if(cmnd_code == 0x51)
		{
			//send the length to master
			//printf("CMND 51 received sending length to master\n");
			I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char *)pTxBuffer));
		}else if(cmnd_code == 0x52)
		{
			//Send the contents of Tx buffer
			//printf("CMND 52 received sending data to master\n");
			I2C_SlaveSendData(pI2CHandle->pI2Cx, pTxBuffer[Cnt++] );
		}
	}else if(I2C_Event == I2C_EV_DATA_RECEIVE)
	{
		//Data is waiting for the slave to read, slave has to read it
			//printf("SLAVE reads data here\n");
		cmnd_code = I2C_SlaveReceiveData(pI2CHandle->pI2Cx);
		//if(cmnd_code == 0x52) delay();
	}else if(I2C_Event == I2C_ERROR_AF)
	{
		//This happens only in slave Tx
		//Master has send NACK , So Slave shld stop Tx more data
			//printf("SLAVE receives nack here \n");
		cmnd_code = 0xff;
		Cnt = 0;
	}else if(I2C_Event == I2C_EV_STOP)
	{
		//This happens only during slave reception
		//Master has ended the I2C comm. with the slave
	}
}

#endif
