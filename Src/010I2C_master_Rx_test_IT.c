/*
 * 010I2C_master_Rx_test_IT.c
 *
 *  Created on: 18-Feb-2021
 *      Author: ark
 */

#if 0

#include"stm32f446xx.h"
#include"stm32f446xx_gpio.h"
#include"stm32f446xx_i2c.h"

#include<string.h>
#include<stdint.h>
#include<stdio.h>

extern void initialise_monitor_handles();
/*
 * I2C peripheral initialization:
 *
 *We will be using **I2C2**
 *
 * SDA: PB3
 * SCL: PB10
 *
 *???????????????????????????????????????????????????????????????????????????
 *							ENABLE _ SR  _ NOT _ WORKING   									?
 *???????????????????????????????????????????????????????????????????????????
 * AF: 4
 */
void delay();
void I2C2_GPIOInits();
void I2C2_Inits();

I2C_Handle_t I2C2Handle;
uint8_t pRxBuffer[40];

#define MASTERS_ADDRESS 	 0x38
#define SLAVE_ADDR  0x68

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

	initialise_monitor_handles();

	printf("Application is Running!\n");

	//GPIO Button Init
	GPIO_BtnLedInit();

	//I2C pin inits
	I2C2_GPIOInits();

	//I2C peripheral config
	I2C2_Inits();

	//I2C IRQ config
	I2C_IRQ_ITConfig(IRQ_NO_I2C2_EV, ENABLE);
	I2C_IRQ_ITConfig(IRQ_NO_I2C2_ER, ENABLE);

	uint8_t cmnd_send, cmnd_read;

	I2C_Init(&I2C2Handle);
	I2C_Enable(I2C2Handle.pI2Cx, ENABLE);

	I2C2Handle.pI2Cx->CR1 |= (0x1 << I2C_CR1_ACK);

	while(1)
	{
		cmnd_send = (uint8_t)0x51;
		cmnd_read = (uint8_t)0x52;

		if( !GPIO_ReadIPin(GPIOA, GPIO_PIN_10) )
		{
			delay();
			while(I2C_MasterSendDataIT( &I2C2Handle, &cmnd_send, 1,SLAVE_ADDR , I2C_DISABLE_SR) != I2C_READY); // Send Command to Arduino to instruct it to send the length of the information

			printf("1st MSD\n");
			while(I2C_MasterReceiveDataIT(&I2C2Handle, pRxBuffer, 1, SLAVE_ADDR, I2C_DISABLE_SR) != I2C_READY); //Receive Command from Arduino

			printf("1st MRD\n");
			while(I2C_MasterSendDataIT(&I2C2Handle, &cmnd_read, 1, SLAVE_ADDR, I2C_DISABLE_SR) != I2C_READY);

			printf("2nd MSD\n");
			while(I2C_MasterReceiveDataIT(&I2C2Handle, pRxBuffer, I2C2Handle.RxSize, SLAVE_ADDR, I2C_DISABLE_SR) != I2C_READY);

			printf("2nd MRD\n");
			delay();

			printf("Data : \t%s\n", pRxBuffer);
		}
	}
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
	if(I2C_Event == I2C_EV_Tx_COMPLETE)
	{
		printf("Tx COMPLETE\n");
	}
	else if(I2C_Event == I2C_EV_Rx_COMPLETE)
	{
		printf("Rx COMPLETE\n");
	}
	else if(I2C_Event == I2C_ERROR_AF)
	{
		printf("Error: ACK FAILURE\n");

		//In master ACK failure happens when slave fials to send ack for the byte
		//sent from the master
		I2C_CloseSendData(pI2CHandle);

		//Generate STOP condition to release the BUS
		pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_STOP);

		//Hang in Infinite Loop
		while(1);
 	}
}

#endif


#if 0
/*
 * 010i2c_master_tx_testing.c
 *
 *  Created on: Feb 24, 2019
 *      Author: admin
 */


#include<stdio.h>
#include<string.h>
#include "stm32f446xx.h"

extern void initialise_monitor_handles();

//Flag variable
uint8_t rxComplt = RESET;

#define MY_ADDR 0x61;

#define SLAVE_ADDR  0x68

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

I2C_Handle_t I2C2Handle;

//rcv buffer
uint8_t rcv_buf[32];

/*
 * PB6-> SCL
 * PB7 -> SDA
 */

void I2C2_GPIOInits(void)
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

void I2C2_Inits(void)
{
	I2C2Handle.pI2Cx  = I2C2;
	I2C2Handle.I2C_Config.I2C_ACKControl = I2C_ACK_EN;
	I2C2Handle.I2C_Config.I2C_DeviceAddress  =  MY_ADDR;
	I2C2Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C2Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
	I2C2Handle.TxRxState = I2C_READY;

	I2C_Init(&I2C2Handle);
}

void GPIO_ButtonInit(void)
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


int main(void)
{

	uint8_t commandcode;

	uint8_t len;

	initialise_monitor_handles();

	printf("Application is running\n");

	GPIO_ButtonInit();

	//i2c pin inits
	I2C2_GPIOInits();

	//i2c peripheral configuration
	I2C2_Inits();

	//I2C IRQ configurations
	I2C_IRQ_ITConfig(IRQ_NO_I2C2_EV,ENABLE);
	I2C_IRQ_ITConfig(IRQ_NO_I2C2_ER,ENABLE);

	//enable the i2c peripheral
	I2C_Enable(I2C2,ENABLE);

	//ack bit is made 1 after PE=1
	I2C2Handle.pI2Cx->CR1 |= (0x1 << I2C_CR1_ACK);

	while(1)
	{
		//wait till button is pressed
		while( GPIO_ReadIPin(GPIOA,GPIO_PIN_10) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = 0x51;


		while(I2C_MasterSendDataIT(&I2C2Handle,&commandcode,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY);

		while(I2C_MasterReceiveDataIT(&I2C2Handle,&len,1,SLAVE_ADDR,I2C_ENABLE_SR)!= I2C_READY);



		commandcode = 0x52;
		while(I2C_MasterSendDataIT(&I2C2Handle,&commandcode,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY);


		while(I2C_MasterReceiveDataIT(&I2C2Handle,rcv_buf,len,SLAVE_ADDR,I2C_ENABLE_SR)!= I2C_READY);

		rxComplt = RESET;

		//wait till rx completes
        while(rxComplt != SET)
        {

        }

		rcv_buf[len+1] = '\0';

		printf("Data : %s",rcv_buf);

		rxComplt = RESET;

	}

}


void I2C2_EV_IRQHandler (void)
{
	I2C_EV_IRQHandling(&I2C2Handle);
}


void I2C2_ER_IRQHandler (void)
{
	I2C_ER_IRQHandling(&I2C2Handle);
}



void I2C_AppEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv)
{
     if(AppEv == I2C_EV_Tx_COMPLETE)
     {
    	 printf("Tx is completed\n");
     }else if (AppEv == I2C_EV_Rx_COMPLETE)
     {
    	 printf("Rx is completed\n");
    	 rxComplt = SET;
     }else if (AppEv == I2C_ERROR_AF)
     {
    	 printf("Error : Ack failure\n");
    	 //in master ack failure happens when slave fails to send ack for the byte
    	 //sent from the master.
    	 I2C_CloseSendData(pI2CHandle);

    	 //generate the stop condition to release the bus
   		pI2CHandle->pI2Cx->CR1 &= ~(0x1 << I2C_CR1_STOP);

    	 //Hang in infinite loop
    	 while(1);
     }
}
#endif
