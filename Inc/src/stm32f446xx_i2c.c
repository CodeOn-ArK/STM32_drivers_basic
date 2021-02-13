/*
 * stm32f446xx_i2c.c
 *
 *  Created on: 07-Feb-2021
 *      Author: ark
 */
#include"stm32f446xx.h"
#include"stm32f446xx_i2c.h"
#include<stdint.h>
//#include<stdio.h>

uint32_t AHB1P[]  = {2, 4, 8, 16, 64, 128, 256, 512};
uint32_t APB1p[]  =  {2, 4, 8, 16};

#define READ 		1
#define WRITE	0

static void I2C_GenerateStartCondition(I2C_RegDef_t *);
static void I2C_ExecuteAddrPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t);

/*********************************************/
void I2C_CallBack();
extern uint8_t* pRxBuffer, head;
uint8_t Length = 0;
/********************************************/
/*
void I2C_CallBack()
{
	while(Length > 0)
	{
		printf("%s", pRxBuffer++);
		Length--;
	}
}
*/
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (0x1 << I2C_CR1_START);
}


static void I2C_ExecuteAddrPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t mode)
{
	if(mode == WRITE)
	{
		pI2Cx->DR  =  ( (SlaveAddr << 1) | 0x0 );								//Shifting the slave address left by in byte bringing in a 0 from right which is the new LSB
																								//0 in LSB signifies master is going to write the data
	}
	else
	{
		pI2Cx->DR = ( (SlaveAddr << 1) |  0x1 );
	}
}

void I2C_Enable(I2C_RegDef_t *pI2Cx , uint8_t EN_DI)
{
	if(EN_DI == ENABLE)
		pI2Cx->CR1 |= ( 0x1 << I2C_CR1_PE );

	else pI2Cx->CR1 &= ~(0x1 << I2C_CR1_PE);

}
uint8_t I2C_GetFagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & (0x1 << FlagName) )
		return FLAG_SET;

	return FLAG_RESET;
}

uint32_t RCC_GetClkVal(void)
{
	uint32_t PCLK1, Clk_SCL, temp;
	uint8_t System_clk_status, AHB1_Prescalar, APB1_Prescalar;

	System_clk_status = ((RCC->CFGR >> 2 ) & (0x3));

	if(System_clk_status == 0)
	{
		//HSI
		Clk_SCL = 16000000;

	}else if(System_clk_status == 1)
	{
		//HSE
	}else if(System_clk_status == 2)
	{
		//PLL
	}else if(System_clk_status == 3)
	{
		//PLL_R
	}

	temp = ((RCC->CFGR >> 4) & (0x4));

	if(temp < 8)
	{
		AHB1_Prescalar = 1;
	}else
	{
		AHB1_Prescalar = (AHB1P[temp] - 8);
	}

	temp = ((RCC->CFGR >> 10 ) & (0x3));

	if(temp < 4)
	{
		APB1_Prescalar = 1;

	}else
	{
		APB1_Prescalar = (APB1p[temp] - 4);
	}

	PCLK1 = (Clk_SCL/ AHB1_Prescalar)/APB1_Prescalar;

	return PCLK1;
}
void I2C_PeriClkCntrl(I2C_RegDef_t *pI2Cx, uint8_t En_Di)
{
	if(En_Di  ==	 ENABLE)
	{
		if(pI2Cx == I2C1)
			I2C1_CLK_EN();

		else if(pI2Cx == I2C2)
			I2C2_CLK_EN();

		else if(pI2Cx == I2C3)
			I2C2_CLK_EN();

	}
	else
	{
		if(pI2Cx == I2C1)
			I2C1_CLK_DI();

		else if(pI2Cx == I2C2)
			I2C2_CLK_DI();

		else if(pI2Cx == I2C3)
			I2C3_CLK_DI();

	}

}

void I2C_Init(I2C_Handle_t *pI2CHandle)				//INITIALIZES I2C PORT
{
	uint32_t tempreg = 0;

	//Enable the I2Cx peripheral clock
	I2C_PeriClkCntrl(pI2CHandle->pI2Cx , ENABLE);

	//ack control bit
	tempreg = (pI2CHandle->I2C_Config.I2C_ACKControl << 10);
	pI2CHandle->pI2Cx->CR1 |= tempreg;

	//prog the device own address
	tempreg = pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (0x1 << 14);
	pI2CHandle->pI2Cx->OAR1 |= tempreg;

	//config the FREQ field of CR2
	tempreg = RCC_GetClkVal()/1000000U;
	pI2CHandle->pI2Cx->CR2 |= (tempreg & ( 0x3F));
/*
 * Configuring I2C SCL :
 *
 * For SM mode;
 * 1) Config the mode in CCR reg
 * 2) prog FREQ field of CR2 with the value of PCLK1 (The APB to which the I2C is connected)
 * 3) Calc && prog the CCR value in CCr field of CCR reg
 *
 * {T refers to time period}
 *
 * T(high(SCL)) = CCR * T(PCLK1)
 * T(low(SCL)  = CCR *T(PLCK1)
 *
 *For FM mode;
 *1) Config the mode in CCR reg
 *2)Select the duty cycle of Fast mode SCL in CCR reg(14th bit)
 *3) Prog FREQ field of CR2 with the value of PCLK1
 *4) Calc and prog CCR value in CCr in CCR field of CCR reg
 *
 *if DUTY=0
 * T(HIGH)   =   CCR  *  T(PCLK1)
 * T(LOW)		=  2 * CCR  * T(PCLK1)
 *
 * if DUTY=1
 * T(HIGH)	=  9 * CCR * T(PCLK1)
 * T(HIGH)	=	16 * CCR  *  T(PCLK1)
 *
 *
 */

	//CCR Calculations
	uint16_t ccr_value = 0;
	tempreg = 0;

	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		ccr_value =  (RCC_GetClkVal() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg = (ccr_value & (0xFFF));

		pI2CHandle->pI2Cx->CCR |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14 );
		pI2CHandle->pI2Cx->CCR &= ~(0x1 << 15);
		pI2CHandle->pI2Cx->CCR |= (tempreg);

	}else
	{
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = (RCC_GetClkVal())/(3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
			tempreg = (ccr_value & (0xFFF));

			pI2CHandle->pI2Cx->CCR |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14 );
			pI2CHandle->pI2Cx->CCR |= (0x1 << 15);
			pI2CHandle->pI2Cx->CCR |= (tempreg);

		}else
		{
			ccr_value = (RCC_GetClkVal())/(25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
			tempreg = (ccr_value & (0xFFF));

			pI2CHandle->pI2Cx->CCR |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14 );
			pI2CHandle->pI2Cx->CCR |= (0x1 << 15);
			pI2CHandle->pI2Cx->CCR |= (tempreg);

		}
	}

	uint32_t temp = 0;

	//TRISE Configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		temp = ((( RCC_GetClkVal()*1 )/1000000U ) + 1);
	}else
	{
		temp = ((( RCC_GetClkVal()*300 )/1000000000U ) + 1);
	}

	pI2CHandle->pI2Cx->TRISE |= ((temp) & (0x3F));
	(void)temp;

}


void I2C_DeInit(I2C_RegDef_t *pI2Cx)										//DEINITIALIZES I2C PORT
{
	if(pI2Cx == I2C1)
	{
		I2C1_REG_RESET();
	}
	else if(pI2Cx == I2C2)
	{
		I2C2_REG_RESET();
	}
	else if(pI2Cx == I2C3)
	{
		I2C3_REG_RESET();
	}

}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTXBuffer, uint32_t Len, uint8_t SlaveAddr)
{

	//1. 	Generate the start condition
	pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_START);//I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2.  Confirm that start Generation is completed by checking the SB flag in the SR1
	// Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !(pI2CHandle->pI2Cx->SR1 & (0x1 << I2C_SR1_SB)) );						//Be in while loop until SBin SR is set

	//3.   Send the address of the slave with R/nW bit set to w(0) (total 8 bits)
	I2C_ExecuteAddrPhase(pI2CHandle->pI2Cx, SlaveAddr, WRITE);

	//4.   Confirm that address phase is completed by checking the ADDR flag in the SR1
	while( !(pI2CHandle->pI2Cx->SR1 & (0x1 << I2C_SR1_ADDR)) );				//wait until ADDR bit of SR1 is set indicating end of address transmission

	//5.	Clear the ADDR flag according to its s/w response
	//Note:	Until the ADDR is cleared SCL will be stretched(pulled to LOW)
	uint32_t temp;

	temp = pI2CHandle->pI2Cx->SR1;
	temp = pI2CHandle->pI2Cx->SR2;

	//6.	Send the data until Len becomes 0
	while(Len > 0)
	{
		while( !(I2C_GetFagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SR1_TxE)) );

		pI2CHandle->pI2Cx->DR  =  *(pTXBuffer);
		Length = *pTXBuffer;
		Len--;
	}

	//7.	When Len becomes zero wait for TXE = 1 && BTF = 1 before generating the STOP condition
	//Note: 	TXE=1, BTF=1 , means that both SR && DR are empty && nxt transmission should begin
	//				when BTF=1 SCL will be stretched (pulled to LOW)
	while(  !( (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_TxE  &  0x1) && (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_BTF & 0x1)  )  );


	//8.	Generate STOP condition && master need not to wait for the completion of STOP condition.
	//Note:	generating STOP, automatically clears the BTF
	pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_STOP);

	(void)temp;

}

void I2C_MasterRecieveData(I2C_Handle_t *pI2CHandle, uint8_t *pRXBuffer, uint32_t Len, uint8_t SlaveAddr)
{

	//1. Generate the START condition
	pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_START);

	//2. COnfirm that start generation is completed by checking the SB flag in the SR1
	//Note: Unitl SB is cleared SCl will be stretched (Pulled Low)
	while( !(I2C_GetFagStatus(pI2CHandle->pI2Cx, I2C_SR1_SB)) );

	//3. Send the address of the slave with R/nW  bit set to R(1) (total 8 bits)
	I2C_ExecuteAddrPhase(pI2CHandle->pI2Cx, SlaveAddr, READ);

	//4. Wait until addr phase is completed by checking the ADDR flag in the SR1
	while( !(I2C_GetFagStatus(pI2CHandle->pI2Cx, I2C_SR1_ADDR)) );

	//Procedure to read only 1 byte of data
	if(Len == 1)
	{
		// Disable Acking
		pI2CHandle->pI2Cx->CR1 &= ~(0x1 << I2C_CR1_ACK);

		// Clear the ADDR flag
		pI2CHandle->pI2Cx->SR1 &= ~(0x1 << I2C_SR1_ADDR);

		// Wait until RXNE becomes 1
		while( !(I2C_GetFagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE)) );

		//Generate STOP condition
		pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_STOP);

		// Read data in to buffer
		*pRXBuffer = pI2CHandle->pI2Cx->DR;
	}

	//procedure to READ data from Slave when Len > 1
	if(Len > 1)
	{
		//Clear the ADDR flag
		pI2CHandle->pI2Cx->SR1 &= ~(0x1 << I2C_SR1_ADDR);

		//Read the data until Len becomes Zero
		for(uint32_t i = Len; i > 0; i--)
		{
			//Wait until RXNE becomes 1
			while( !(I2C_GetFagStatus(pI2CHandle->pI2Cx, I2C_SR1_RxNE)) );

			if(i == 2)
			{
				//Clear the ACK bit
				pI2CHandle->pI2Cx->CR1 &= ~(0x1 << I2C_CR1_ACK);

				//Generate STOP condtion
				pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_STOP);
			}

			//Read the data from data reg in to buffer
			*pRXBuffer = pI2CHandle->pI2Cx->DR;

			//Increment the buffer Addr
			pRXBuffer++;
		}
	}

	//Re-enable ACKing
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_EN)
	{
		pI2CHandle->pI2Cx->CR1 |= (0x1 << I2C_CR1_ACK);
	}

	I2C_CallBack();
}

void I2C_IRQ_ITConfig(uint8_t IRQNumber, uint8_t En_Di)					//CONFIGURES IRQ
{

}


void I2C_IRQConfig(uint8_t IRQNumber,uint32_t IRQPriority)					// I2C PRIORITY HANDLER
{

}


/*
void I2C_AppEventCallback(I2C_Handle_t *, uint8_t)
{

}
*/
