/*=================================================================================*/
/*  File        : UART_Interface.h                                                 */
/*  Description : This Header file includes UART Interface for STM32f103C8T6       */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 21/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
* Name: UART_configStruct_t
* Type: Structure
* Description: Data type to initialize the DMA channel
********************************************************************************/

typedef struct
{
	u32 UART_u32_BAUD_RATE;
	u8 UART_u8_END_STRING;
	u8 UART_u8_STOP_BIT;
	u8 UART_u8_DATA_SIZE;
	u8 UART_u8_PARTIY;
	u8 UART_u8_RECEIVE_METHOD;
}UART_configStruct_t;

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

extern UART_configStruct_t ESP_UARTConfig;
/*******************************************************************************
*                       	   	UART		                	        	   *
*******************************************************************************/
#define UART_u8_1								0
#define UART_u8_2								1
#define UART_u8_3								2

/*******************************************************************************
*                       	   	STOP BITS		   		                       *
*******************************************************************************/
#define UART_u8_STOP_1_BIT						0b00
#define UART_u8_STOP_0_5_BIT					0b01
#define UART_u8_STOP_2_BITS						0b10
#define UART_u8_STOP_1_5_BITS					0b11

/*******************************************************************************
*                       	   	DATA SIZE		                	           *
*******************************************************************************/
#define UART_u8_8_BITS							0
#define UART_u8_9_BITS							1

/*******************************************************************************
*                       	   	PARTIY		   		             	           *
*******************************************************************************/
#define UART_u8_PARITY_DISABLED					0b00
#define UART_u8_PARITY_EVEN						0b10
#define UART_u8_PARITY_ODD						0b11

/*******************************************************************************
*                       	   	RECEIVE METHOD		                	       *
*******************************************************************************/
#define UART_u8_POLLING							0b000 /* DMA disabled, send and receive with poling */
#define UART_u8_INTERRUP						0b001 /* DMA disabled, send with polling and receive with interrupt */
#define UART_u8_DMA_TX_POL_RX					0b100 /* Send with DMA receive with polling */
#define UART_u8_DMA_TX_INT_RX					0b101 /* Send with DMA receive with interrupt */
#define UART_u8_DMA_RX							0b010 /* Receive with DMA send with polling */
#define UART_u8_DMA_TX_RX						0b110 /* Send with DMA receive with DMA */

/*******************************************************************************
*                       Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		UART_u8Init
* Description:			Function to initialize the UART
* Parameters (in):    	Pointer to structure of type UART_RegDef_t
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8Init(u8 Copy_u8UartNumber, UART_configStruct_t * Copy_PstrUARTConfig);

/*******************************************************************************
* Function Name:		UART_u8SendByte
* Description:			Function to send one byte using the UART
* Parameters (in):    	Data Byte
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SendByte(u8 Copy_u8UartNumber, u8 Copy_u8DataByte);

/*******************************************************************************
* Function Name:		UART_u8SendString
* Description:			Function to send string using the UART
* Parameters (in):    	Data Byte
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SendString(u8 Copy_u8UartNumber, u8* Copy_Pu8DataString);

/*******************************************************************************
* Function Name:		UART_u8SendStream
* Description:			Function to send stream of data using UART
* Parameters (in):    	Pointer to variable to receive the stream on it and the data size
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SendStream(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte, u16 Copy_u8DataSize);

/*******************************************************************************
* Function Name:		UART_u8ReceiveByte
* Description:			Function to receive one byte using UART
* Parameters (in):    	Pointer to variable to save the data on it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8ReceiveByte(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte);

/*******************************************************************************
* Function Name:		UART_u8ReceiveString
* Description:			Function to receive string using UART
* Parameters (in):    	Pointer to variable to receive the string on it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8ReceiveString(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte);

/*******************************************************************************
* Function Name:		UART_u8ReceiveStream
* Description:			Function to receive string using UART
* Parameters (in):    	Pointer to variable to receive the stream on it and the data size
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8ReceiveStream(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte, u16 Copy_u8DataSize);

/*******************************************************************************
* Function Name:		UART_u8SetCallBack
* Description:			Function to set the ISR
* Parameters (in):    	Pointer to function to act as the ISR
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SetCallBack(u8 Copy_u8UartNumber, void(*Copy_pfCallback)(void));



#endif /* UART_INTERFACE_H_ */
