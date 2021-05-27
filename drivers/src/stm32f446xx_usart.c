/*
 * stm32f446xx_usart.c
 *
 *  Created on: Feb 1, 2021
 *      Author: ark
 */


#include"stm32f446xx.h"

extern USART_Handle_t usart2_handle;

/*********************************************************************
 * @fn      		  - void USART_PeriClkCntrl(USART_RegDef_t *pUSARTx, uint8_t ENDI)
 *
 * @brief             - Sets the peripheral clock of the corresponding USART peripheral mentioned
 * 						in the USART_RegDef_t instance
 *
 * @param[in]         - USART_RegDef_t *pUSARTx; Instance to Hold the USART peripheral
 * @param[in]         - uint8_t ENDI; Enable/Disable the corresponding peripheral clock
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_PeriClkCntrl(USART_RegDef_t *pUSARTx, uint8_t ENDI)
{
	if(ENDI == ENABLE)
	{
		if( (pUSARTx == USART1) )
		{
			USART1_CLK_EN();
		}else if( (pUSARTx == USART2) )
		{
			USART2_CLK_EN();
		}else if( (pUSARTx == USART3) )
		{
			USART3_CLK_EN();
		}else if( (pUSARTx == UART4) )
		{
			UART4_CLK_EN();
		}else if( (pUSARTx == UART5) )
		{
			UART5_CLK_EN();
		}else if( (pUSARTx == USART6) )
		{
			USART6_CLK_EN();
		}
	}

	if(ENDI == DISABLE)
		{
			if( (pUSARTx == USART1) )
			{
				USART1_CLK_DI();
			}else if( (pUSARTx == USART2) )
			{
				USART2_CLK_DI();
			}else if( (pUSARTx == USART3) )
			{
				USART3_CLK_DI();
			}else if( (pUSARTx == UART4) )
			{
				UART4_CLK_DI();
			}else if( (pUSARTx == UART5) )
			{
				UART5_CLK_DI();
			}else if( (pUSARTx == USART6) )
			{
				USART6_CLK_DI();
			}
		}
}

/*********************************************************************
 * @fn      		  - USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
 *
 * @brief             - Sets baud rate of the corresponding USART peripheral according to
 * 						the specified BaudRate
 *
 * @param[in]         - USART_RegDef_t *pUSARTx; Instance to Hold the USART peripheral
 * @param[in]         - uint32_t BaudRate; Any of the predefined baud rates ref @USART_Baud
 *
 * @return            - void
 *
 * @Note              -

 */
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{

	//Variable to hold the APB clock
	uint32_t PCLKx;
	uint32_t usartdiv;

	//variables to hold Mantissa and Fraction values
	uint32_t M_part,F_part;
	uint32_t tempreg=0;

  //Get the value of APB bus clock in to the variable PCLKx
  if(pUSARTx == USART1 || pUSARTx == USART6)
  {
	   //USART1 and USART6 are hanging on APB2 bus
	   PCLKx = RCC_GetPCLK2Value();
  }else
  {
	   PCLKx = RCC_GetPCLK1Value();
  }

  //Check for OVER8 configuration bit
  if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
  {
	   //OVER8 = 1 , over sampling by 8
	   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
  }else
  {
   //over sampling by 16
	  usartdiv = ((25*PCLKx) / (4*BaudRate));
  }

  //Calculate the Mantissa part
  M_part = usartdiv/100;

  //Place the Mantissa part in appropriate bit position . refer USART_BRR
  tempreg |= M_part << 4;

  //Extract the fraction part
  F_part = (usartdiv - (M_part* 100));

  //Calculate the final fractional
  if(pUSARTx->CR1 & ( 1 << USART_CR1_OVER8))
   {
	  //OVER8 = 1 , over sampling by 8
	  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);

   }else
   {
	   //over sampling by 16
	   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

   }

  //Place the fractional part in appropriate bit position . refer USART_BRR
  tempreg |= F_part;

  //copy the value of tempreg in to BRR register
  pUSARTx->BRR = tempreg;
}


/*********************************************************************
 * @fn      		  - USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
 *
 * @brief             - returns the status of flag register(SR) of the corresponding USART
 * 						peripheral
 *
 * @param[in]         - USART_RegDef_t *pUSARTx; Instance to Hold the USART peripheral
 * @param[in]         - uint8_t StatusFlagName; Flag name ,which is to be tested, in the SR
 *
 * @return            - uint8_t (SET/RESET)
 *
 * @Note              - NULL

 */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
	if( pUSARTx->SR & (0x1 << StatusFlagName) )
		return FLAG_SET;

	return FLAG_RESET;
}


/*********************************************************************
 * @fn      		  - USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
 *
 * @brief             - Clear the corresponding flag in the SR
 *
 * @param[in]         - USART_RegDef_t *pUSARTx; Instance to Hold the USART peripheral
 * @param[in]         - uint16_t StatusFlagName; Status flag name in SR of the corresponding register
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{

	pUSARTx->SR &= ~(0x1 << StatusFlagName);
}

/*********************************************************************
 * @fn      		  - USART_Init(USART_Handle_t *pUSARTHandle)
 *
 * @brief             - Initializes the defined USART peripheral with the configuration
 * 						given in USART_Handle_t structure
 *
 * @param[in]         - USART_Handle_t *pUSARTHandle; Handle structure to contain the configuration
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{

	//Temporary variable
	uint32_t tempreg=0;

/******************************** Configuration of CR1******************************************/

	//Implement the code to enable the Clock for given USART peripheral
	 USART_PeriClkCntrl(pUSARTHandle->pUSARTx, ENABLE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		//Implement the code to enable the Receiver bit field
		tempreg|= (1 << USART_CR1_RE);
	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		//Implement the code to enable the Transmitter bit field
		tempreg |= ( 1 << USART_CR1_TE );

	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		//Implement the code to enable the both Transmitter and Receiver bit fields
		tempreg |= ( ( 1 << USART_CR1_RE) | ( 1 << USART_CR1_TE) );
	}

    //Implement the code to configure the Word length configuration item
	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M ;


    //Configuration of parity control bit fields
	if ( pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		//Implement the code to enable the parity control
		tempreg |= ( 1 << USART_CR1_PCE);

		//Implement the code to enable EVEN parity
		//Not required because by default EVEN parity will be selected once you enable the parity control

	}else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD )
	{
		//Implement the code to enable the parity control
	    tempreg |= ( 1 << USART_CR1_PCE);

	    //Implement the code to enable ODD parity
	    tempreg |= ( 1 << USART_CR1_PS);

	}

   //Program the CR1 register
	pUSARTHandle->pUSARTx->CR1 = tempreg;

/******************************** Configuration of CR2******************************************/

	tempreg=0;

	//Implement the code to configure the number of stop bits inserted during USART frame transmission
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

	//Program the CR2 register
	pUSARTHandle->pUSARTx->CR2 = tempreg;

/******************************** Configuration of CR3******************************************/

	tempreg=0;

	//Configuration of USART hardware flow control
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//Implement the code to enable CTS flow control
		tempreg |= ( 1 << USART_CR3_CTSE);


	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//Implement the code to enable RTS flow control
		tempreg |= ( 1 << USART_CR3_RTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control
		tempreg |= ( 1 << USART_CR3_CTSE);
		tempreg |= ( 1 << USART_CR3_RTSE);
	}


	pUSARTHandle->pUSARTx->CR3 = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

	//Implement the code to configure the baud rate
	//We will cover this in the lecture. No action required here
	USART_SetBaudRate(pUSARTHandle->pUSARTx,pUSARTHandle->USART_Config.USART_Baud);

}


/*********************************************************************
 * @fn      		  - USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Cmd)
 *
 * @brief             - Enables the given USART peripheral by setting the UE bit in CR1 to 1
 *
 * @param[in]         - USART_RegDef_t *pUSARTx; Instance to Hold the USART peripheral
 * @param[in]         - uint8_t Cmd; Enable/Disable
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Cmd)
{
	if(Cmd == ENABLE)
	{
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else
	{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}

}


/*********************************************************************
 * @fn      		  - USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
 *
 * @brief             - Transmits data contained in pTxBuffer from the corresponding USART peripheral
 *
 * @param[in]         - USART_Handle_t *pUSARTHandle; Handle structure of the corresponding USART
 * @param[in]         - uint8_t *pTxBuffer; Buffer to contain the data to be sent
 * @param[in]         - uint32_t Len; No. of bytes ot be sent
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

	uint16_t *pdata;


   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,  USART_SR_TXE));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & 0xff);

			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TC));
}


/*********************************************************************
 * @fn      		  - USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
 *
 * @brief             - Receives data in the pRxBuffer from the corresponding USART peripheral
 *
 * @param[in]         - USART_Handle_t *pUSARTHandle; Handle structure of the corresponding USART
 * @param[in]         - uint8_t *pRxBuffer; Buffer to contain the data to be Received
 * @param[in]         - uint32_t Len; No. of bytes to be received
 *
 * @return            - void
 *
 * @Note              - NULL

 */

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
   //Loop over until "Len" number of bytes are transferred
	uint8_t* head;

	for(uint32_t i = 0 ; i <  (Len+1) ; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,  USART_SR_RXNE));

		if(pUSARTHandle->pUSARTx->DR == '\n' || pUSARTHandle->pUSARTx->DR == '\r')
			continue;
		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x1FF);

				//Now increment the pRxBuffer two times
				pRxBuffer += 2;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);

				 //Increment the pRxBuffer
				 pRxBuffer++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = pUSARTHandle->pUSARTx->DR;
			}else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR) & (0x007F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

	if(i == (Len + 1))pRxBuffer = head;

	(void)head;
}

/*********************************************************************
 * @fn      		  - USART_SendDataWithIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs

 */
/*
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle->TODO;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TODO = Len;
		pUSARTHandle->pTxBuffer = TODO;
		pUSARTHandle->TxBusyState = TODO;

		//Implement the code to enable interrupt for TXE
		TODO


		//Implement the code to enable interrupt for TC
		TODO


	}

	return txstate;

}


/*********************************************************************
 * @fn      		  - USART_ReceiveDataIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs

 *
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->TODO;

	if(rxstate != TODO)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = TODO;
		pUSARTHandle->RxBusyState = TODO;

		//Implement the code to enable interrupt for RXNE
		TODO

	}

	return rxstate;

}

*/

/*********************************************************************
 * @fn      		  - USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENDI)
 *
 * @brief             - Enables the IRQ line of the corresponding IRQNumber
 *
 * @param[in]         - uint8_t IRQNumber; IRQ number of the Peripheral whose Interrupt line is to
 * 						be enabled/disabled
 * @param[in]         - uint8_t ENDI; Enable/Disable
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENDI)
{
	if( ENDI == ENABLE )
	{

		if(IRQNumber < 32)
		{
				*NVIC_ISER0 = (0x1 << IRQNumber);
		}else if( (IRQNumber < 64) && (IRQNumber > 31))
		{
				*NVIC_ISER1 |= (0x1 << (IRQNumber%32));
		}else if( (IRQNumber < 96) && (IRQNumber > 63) )
		{
				*NVIC_ISER2 |= (0x1 << (IRQNumber%96));
		}

	}else if( ENDI == DISABLE )
	{

		if(IRQNumber < 32)
		{
				*NVIC_ICER0 &= ~(0x1 << (IRQNumber));
		}else if( (IRQNumber < 64) && (IRQNumber > 31))
		{
				*NVIC_ICER0 &= ~(0x1 << (IRQNumber%32));
		}else if( (IRQNumber < 96) && (IRQNumber > 63) )
		{
				*NVIC_ICER0 &= ~(0x1 << (IRQNumber%96));
		}
	}

}

/*********************************************************************
 * @fn      		  - USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
 *
 * @brief             - Configures the priority level of the corresponding IRQNumber
 *
 * @param[in]         - uint8_t IRQNumber; IRQNumber whose priority isto be configured
 * @param[in]         - uint32_t IRQPriority); IRQ priority level, can be any number between 0 - 15
 *
 * @return            - void
 *
 * @Note              - NULL

 */
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t iprx 		= IRQNumber / 4;
	uint8_t ipr_section = IRQNumber % 4;

	uint8_t shift_amnt  = ((8 * ipr_section) + (8 - NO_PRIORITY_BITS));
	*( NVIC_IPR_BA + (iprx) ) |= (IRQPriority << shift_amnt);

}

