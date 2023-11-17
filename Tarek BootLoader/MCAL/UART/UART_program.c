/*=================================================================================*/
/*  File        : UART_Program.c                                                   */
/*  Description : This Program file includes UART program for STM32f103C8T6        */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 21/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
/*******************************************************************************
 *                        		Inclusions                                     *
 *******************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/stm32f103xx.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/STK/STK_interface.h"
#include "UART_interface.h"
#include "UART_private.h"

/*******************************************************************************
 *                      Private Variables	                                   *
 *******************************************************************************/
static u8 Global_UARTEND_STRING[3] = {'#','#','#'};

typedef void(*fptr_t)(void);
static fptr_t Global_pfArr[3] = {NULL,NULL,NULL};

UART_RegDef_t * UART_Astr[3] = {UART1,UART2,UART3};

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		UART_u8Init
 ********************************************************************************/
u8 UART_u8Init(u8 Copy_u8UartNumber, UART_configStruct_t * Copy_PstrUARTConfig)
{
	u8 Local_ErrorState = STD_TYPES_OK;
	u16 Local_Mantissa,Local_Fraction;
	u32 Baud = Copy_PstrUARTConfig->UART_u32_BAUD_RATE;

	switch (Copy_u8UartNumber)
	{
	case UART_u8_1:
		RCC_u8EnableDisablPeripheralClk(RCC_u8_AFIO, RCC_u8_Enable);
		RCC_u8EnableDisablPeripheralClk(RCC_u8_USART1, RCC_u8_Enable);
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOA, RCC_u8_Enable);
		GPIO_u8SetPinMode(GPIO_u8_GPIOA,GPIO_u8_PIN9, GPIO_u8_OUTPUT_AF_PP_10MHZ);
		GPIO_u8SetPinMode(GPIO_u8_GPIOA,GPIO_u8_PIN10, GPIO_u8_INPUT_FLOATING);
		break;
	case UART_u8_2:
		RCC_u8EnableDisablPeripheralClk(RCC_u8_AFIO, RCC_u8_Enable);
		RCC_u8EnableDisablPeripheralClk(RCC_u8_USART2, RCC_u8_Enable);
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOA, RCC_u8_Enable);
		GPIO_u8SetPinMode(GPIO_u8_GPIOA,GPIO_u8_PIN2, GPIO_u8_OUTPUT_AF_PP_10MHZ);
		GPIO_u8SetPinMode(GPIO_u8_GPIOA,GPIO_u8_PIN3, GPIO_u8_INPUT_FLOATING);
		break;
	case UART_u8_3:
		RCC_u8EnableDisablPeripheralClk(RCC_u8_AFIO, RCC_u8_Enable);
		RCC_u8EnableDisablPeripheralClk(RCC_u8_USART3, RCC_u8_Enable);
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOB, RCC_u8_Enable);
		GPIO_u8SetPinMode(GPIO_u8_GPIOB,GPIO_u8_PIN10, GPIO_u8_OUTPUT_AF_PP_10MHZ);
		GPIO_u8SetPinMode(GPIO_u8_GPIOB,GPIO_u8_PIN11, GPIO_u8_INPUT_FLOATING);
		break;
	default:
		break;
	}

	if(Copy_PstrUARTConfig != NULL)
	{
		UART_Astr[Copy_u8UartNumber]->CR1 = 0;
		UART_Astr[Copy_u8UartNumber]->CR2 = 0;
		UART_Astr[Copy_u8UartNumber]->CR1 |= ((Copy_PstrUARTConfig->UART_u8_DATA_SIZE & 0b1) << 12);
		UART_Astr[Copy_u8UartNumber]->CR1 |= ((Copy_PstrUARTConfig->UART_u8_PARTIY & 0b11) << 9);
		/* First bit indicates the receive is interrupt or polling */
		UART_Astr[Copy_u8UartNumber]->CR1 |= ((Copy_PstrUARTConfig->UART_u8_RECEIVE_METHOD & 0b1) << 5);
		/* Second and third bit indicates the DMA Configuration */
		UART_Astr[Copy_u8UartNumber]->CR3 |= (((Copy_PstrUARTConfig->UART_u8_RECEIVE_METHOD>>1) & 0b11) << 6);
		UART_Astr[Copy_u8UartNumber]->CR2 |= ((Copy_PstrUARTConfig->UART_u8_STOP_BIT&0b11) << 12);
		Global_UARTEND_STRING[Copy_u8UartNumber] = Copy_PstrUARTConfig->UART_u8_END_STRING ;

		/* Baud Rate Calculations */
		Local_Mantissa = (F_CPU/(16*Baud));
		Local_Fraction = ((F_CPU%(16*Baud)) / Baud );
		f32 Reminder = (F_CPU - Local_Mantissa*16*Baud)/(float)Baud ;

		if( ((Reminder - (int)Reminder)*10)  >= 5 )
		{
			Local_Fraction ++;
			if(Local_Fraction > 15)
			{
				Local_Fraction = 0;
				Local_Mantissa ++;
			}
		}
		UART_Astr[Copy_u8UartNumber]->BRR = ((Local_Mantissa & 0xFFF) << 4) | (Local_Fraction & 0xF);

		SET_BIT(UART_Astr[Copy_u8UartNumber]->CR1,3); /* Transmit Enable */
		SET_BIT(UART_Astr[Copy_u8UartNumber]->CR1,2); /* Receive Enable */
		SET_BIT(UART_Astr[Copy_u8UartNumber]->CR1,13); /* Enable the UART */
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	STK_u8SetmSBusyWait(1000);
	return Local_ErrorState;
}

/*******************************************************************************
 * Function Name:		UART_u8SendByte
 ********************************************************************************/
u8 UART_u8SendByte(u8 Copy_u8UartNumber, u8 Copy_u8DataByte)
{
	u8 Local_ErrorState = STD_TYPES_OK;

	CLR_BIT(UART_Astr[Copy_u8UartNumber]->SR,6);
	UART_Astr[Copy_u8UartNumber]->DR = Copy_u8DataByte; /* The flag is cleared when we write to the data register */
	while(GET_BIT(UART_Astr[Copy_u8UartNumber]->SR,6) == 0); /* Wait if the previous Transmission isn't completed */

	return Local_ErrorState;
}
/*******************************************************************************
 * Function Name:		UART_u8SendString
 ********************************************************************************/
u8 UART_u8SendString(u8 Copy_u8UartNumber, u8* Copy_Pu8DataString)
{
	u8 Local_ErrorState = STD_TYPES_OK;

	if(Copy_Pu8DataString != NULL)
	{
		u16 i ;
		for(i = 0 ; Copy_Pu8DataString[i] != '\0'&& Copy_Pu8DataString[i] != Global_UARTEND_STRING[Copy_u8UartNumber] ; i++)
		{
			UART_u8SendByte(Copy_u8UartNumber,Copy_Pu8DataString[i]);
		}
		UART_u8SendByte(Copy_u8UartNumber,'\0');
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}


/*******************************************************************************
 * Function Name:		UART_u8SendStream
 ********************************************************************************/
u8 UART_u8SendStream(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte, u16 Copy_u8DataSize)
{
	u8 Local_ErrorState = STD_TYPES_OK;

	if(Copy_pu8DataByte != NULL)
	{
		while(Copy_u8DataSize --)
		{
			UART_u8SendByte(Copy_u8UartNumber,*Copy_pu8DataByte);
			Copy_pu8DataByte++;
		}
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}

/*******************************************************************************
 * Function Name:		UART_u8ReceiveByte
 ********************************************************************************/
u8 UART_u8ReceiveByte(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte)
{
	u8 Local_ErrorState = STD_TYPES_OK;
	u32 time_error = 0;
	if(Copy_pu8DataByte != NULL)
	{
		while(GET_BIT(UART_Astr[Copy_u8UartNumber]->SR,5) == 0)
		{
			time_error++;
			if(time_error == 65000)
			{
				*Copy_pu8DataByte = 255;
				break;
			}
		}
		*Copy_pu8DataByte = UART_Astr[Copy_u8UartNumber]->DR;
		CLR_BIT(UART_Astr[Copy_u8UartNumber]->SR,5); /* Clear the flag */
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}

/*******************************************************************************
 * Function Name:		UART_u8ReceiveString
 ********************************************************************************/
u8 UART_u8ReceiveString(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte)
{
	u8 Local_ErrorState = STD_TYPES_OK;

	if(Copy_pu8DataByte != NULL)
	{
		u16 i = 0;
		UART_u8ReceiveByte(Copy_u8UartNumber,Copy_pu8DataByte+i);
		while(Copy_pu8DataByte[i] != Global_UARTEND_STRING[Copy_u8UartNumber] && Copy_pu8DataByte[i] != '\0')
		{
			i++;
			UART_u8ReceiveByte(Copy_u8UartNumber,Copy_pu8DataByte+i);
		}
		Copy_pu8DataByte[i] = '\0';
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}

/*******************************************************************************
 * Function Name:		UART_u8ReceiveStream
 ********************************************************************************/
u8 UART_u8ReceiveStream(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte, u16 Copy_u8DataSize)
{
	u8 Local_ErrorState = STD_TYPES_OK;

	if(Copy_pu8DataByte != NULL)
	{
		while(Copy_u8DataSize--)
		{
			UART_u8ReceiveByte(Copy_u8UartNumber,Copy_pu8DataByte++);
		}
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}

/*******************************************************************************
 * Function Name:		UART_u8SetCallBack
 ********************************************************************************/
u8 UART_u8SetCallBack(u8 Copy_u8UartNumber,  void(*Copy_pfCallback)(void))
{
	u8 Local_ErrorState = STD_TYPES_OK;

	if(Copy_pfCallback != NULL)
	{
		Global_pfArr[Copy_u8UartNumber] = Copy_pfCallback;
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
void USART1_IRQHandler(void)
{
	CLR_BIT(UART1->SR,5); /* Clear the flag */
	if(Global_pfArr[0] != NULL)
	{
		Global_pfArr[0]();
	}
}

void USART2_IRQHandler(void)
{
	CLR_BIT(UART2->SR,5); /* Clear the flag */
	if(Global_pfArr[1] != NULL)
	{
		Global_pfArr[1]();
	}
}

void USART3_IRQHandler(void)
{
	CLR_BIT(UART3->SR,5); /* Clear the flag */
	if(Global_pfArr[2] != NULL)
	{
		Global_pfArr[2]();
	}
}
