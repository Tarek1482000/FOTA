/*=================================================================================*/
/*  File        : AFIO_Interface.h                                                 */
/*  Description : This Header file includes AFIO Interface for STM32f103C8T6       */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   		AFIO PORTS                 	               *
*******************************************************************************/
#define AFIO_u8_PORTA							0
#define AFIO_u8_PORTB							1
#define AFIO_u8_PORTC							2
#define AFIO_u8_PORTD							3
#define AFIO_u8_PORTE							4

/*******************************************************************************
*                       	   		AFIO EXTI LINE                 	           *
*******************************************************************************/
#define AFIO_u8_EXTI_LINE0						0
#define AFIO_u8_EXTI_LINE1						1
#define AFIO_u8_EXTI_LINE2						2
#define AFIO_u8_EXTI_LINE3						3
#define AFIO_u8_EXTI_LINE4						4
#define AFIO_u8_EXTI_LINE5						5
#define AFIO_u8_EXTI_LINE6						6
#define AFIO_u8_EXTI_LINE7						7
#define AFIO_u8_EXTI_LINE8						8
#define AFIO_u8_EXTI_LINE9						9
#define AFIO_u8_EXTI_LINE10						10
#define AFIO_u8_EXTI_LINE11						11
#define AFIO_u8_EXTI_LINE12						12
#define AFIO_u8_EXTI_LINE13						13
#define AFIO_u8_EXTI_LINE14						14
#define AFIO_u8_EXTI_LINE15						15

/*******************************************************************************
*                       	   		AFIO UART LINE                  	       *
*******************************************************************************/
#define AFIO_u8_UART1							0
#define AFIO_u8_UART2							1
#define AFIO_u8_UART3							2

/*******************************************************************************
*                       	   		AFIO UART REMAP                  	       *
*******************************************************************************/
#define AFIO_u8_UART1_Tx_PA9_Rx_PA10			0
#define AFIO_u8_UART1_Tx_PB6_Rx_PB7				1

#define AFIO_u8_UART2_Tx_PA2_Rx_PA3				0
#define AFIO_u8_UART2_Tx_PD5_Rx_PD6				1

#define AFIO_u8_UART3_Tx_PB10_Rx_PB11			0
#define AFIO_u8_UART3_Tx_PC10_Rx_PC11			1
#define AFIO_u8_UART3_Tx_PD8_Rx_PD9				3

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		AFIO_u8SetEXTIPortSource
* Description:			Function to set the port source of EXTIx
* Parameters (in):    	The EXTI number
* 						The required Port
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 AFIO_u8SetEXTIPortSource(u8 Copy_u8EXTINumber , u8 Copy_u8PortNumber);

/*******************************************************************************
* Function Name:		AFIO_u8DisableJTAG
* Description:			Function to disable JTAG
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 AFIO_u8DisableJTAG(void);

/*******************************************************************************
* Function Name:		AFIO_u8SetUARTConfiguration
* Description:			Function to remap the UART pins
* Parameters (in):    	The UART number
* 						Re-map we want
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 AFIO_u8SetUARTConfiguration(u8 Copy_u8UARTNumber , u8 Copy_u8RemapValue);

#endif
