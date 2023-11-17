/*=================================================================================*/
/*  File        : LCD Program.c                                                    */
/*  Description : This Program file includes LCD program                           */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/stm32f103xx.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/STK/STK_interface.h"
#include "stdlib.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		LCD_init
********************************************************************************/

void LCD_init(void)
{
	RCC_u8EnableDisablPeripheralClk(LCD_u8_RS_RCC_BUS, RCC_u8_Enable);
	RCC_u8EnableDisablPeripheralClk(LCD_u8_E_RCC_BUS, RCC_u8_Enable);
	RCC_u8EnableDisablPeripheralClk(LCD_u8_RCC_BUS, RCC_u8_Enable);

	GPIO_u8SetPinMode(LCD_u8_RS_PORT_ID, LCD_u8_RS_PIN_ID, GPIO_u8_OUTPUT_GP_PP_2MHZ);
	GPIO_u8SetPinMode(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_OUTPUT_GP_PP_2MHZ);

	STK_u8SetmSBusyWait(20); /* Delay For 20 ms */

#if(LCD_u8_DATA_BITS_MODE == 8)
	u8 i ;
	for(i = 0 ; i < 8 ; i++)
	{
		GPIO_u8SetPinMode(LCD_u8_DATA_PORT_ID, LCD_u8_PORT_START_PIN+i, GPIO_u8_OUTPUT_GP_PP_2MHZ);
	}
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#elif(LCD_u8_DATA_BITS_MODE == 4)

	GPIO_u8SetPinMode(LCD_u8_DATA_PORT_ID, LCD_u8_DB4_PIN_ID, GPIO_u8_OUTPUT_GP_PP_2MHZ);
	GPIO_u8SetPinMode(LCD_u8_DATA_PORT_ID, LCD_u8_DB5_PIN_ID, GPIO_u8_OUTPUT_GP_PP_2MHZ);
	GPIO_u8SetPinMode(LCD_u8_DATA_PORT_ID, LCD_u8_DB6_PIN_ID, GPIO_u8_OUTPUT_GP_PP_2MHZ);
	GPIO_u8SetPinMode(LCD_u8_DATA_PORT_ID, LCD_u8_DB7_PIN_ID, GPIO_u8_OUTPUT_GP_PP_2MHZ);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */

	STK_u8SetmSBusyWait(10);
}

/*******************************************************************************
* Function Name:		LCD_sendCommand
********************************************************************************/

void LCD_sendCommand(u8 command)
{
	GPIO_u8WritePinValue(LCD_u8_RS_PORT_ID, LCD_u8_RS_PIN_ID, GPIO_u8_LOW);
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_HIGH);
	STK_u8SetmSBusyWait(1);

#if(LCD_u8_DATA_BITS_MODE == 8)

	for(u8 i = 0 ; i < 7 ; i++)
	{
		GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_PORT_START_PIN, GET_BIT(command,i));
	}
	STK_u8SetmSBusyWait(1);
	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_LOW); /* Enable = 1 */
	STK_u8SetmSBusyWait(1);

#elif(LCD_u8_DATA_BITS_MODE == 4)

	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB4_PIN_ID, GET_BIT(command,4));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB5_PIN_ID, GET_BIT(command,5));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB6_PIN_ID, GET_BIT(command,6));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB7_PIN_ID, GET_BIT(command,7));
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_LOW);
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_HIGH);
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB4_PIN_ID, GET_BIT(command,0));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB5_PIN_ID, GET_BIT(command,1));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB6_PIN_ID, GET_BIT(command,2));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB7_PIN_ID, GET_BIT(command,3));
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_LOW);
	STK_u8SetmSBusyWait(1);

#endif
}

/*******************************************************************************
* Function Name:		LCD_displayCharacter
********************************************************************************/

void LCD_displayCharacter(u8 data)
{
	GPIO_u8WritePinValue(LCD_u8_RS_PORT_ID, LCD_u8_RS_PIN_ID, GPIO_u8_HIGH); /* Rs = 0 */
	STK_u8SetmSBusyWait(1);
	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_HIGH); /* Enable = 1 */
	STK_u8SetmSBusyWait(1);

#if(LCD_u8_DATA_BITS_MODE == 8)

	for(u8 i = 0 ; i < 7 ; i++)
	{
		GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_PORT_START_PIN, GET_BIT(data,i));
	}
	STK_u8SetmSBusyWait(1);
	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_LOW); /* Enable = 1 */
	STK_u8SetmSBusyWait(1);

#elif(LCD_u8_DATA_BITS_MODE == 4)

	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB4_PIN_ID, GET_BIT(data,4));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB5_PIN_ID, GET_BIT(data,5));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB6_PIN_ID, GET_BIT(data,6));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB7_PIN_ID, GET_BIT(data,7));
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_LOW);
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_HIGH);
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB4_PIN_ID, GET_BIT(data,0));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB5_PIN_ID, GET_BIT(data,1));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB6_PIN_ID, GET_BIT(data,2));
	GPIO_u8WritePinValue(LCD_u8_DATA_PORT_ID, LCD_u8_DB7_PIN_ID, GET_BIT(data,3));
	STK_u8SetmSBusyWait(1);

	GPIO_u8WritePinValue(LCD_u8_E_PORT_ID, LCD_u8_E_PIN_ID, GPIO_u8_LOW);
	STK_u8SetmSBusyWait(1);

#endif
}

/*******************************************************************************
* Function Name:		LCD_displayString
********************************************************************************/

void LCD_displayString(char * string)
{
	for(u8 i = 0 ; string[i]!='\0' ; i++)
	{
		LCD_displayCharacter(string[i]);
	}
}

/*******************************************************************************
* Function Name:		LCD_clearScreen
********************************************************************************/

void LCD_clearScreen()
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*******************************************************************************
* Function Name:		LCD_moveCursor
********************************************************************************/

void LCD_moveCursor(u8 row,u8 column)
{
	u8 LCD_cursorAdress = 0;
	switch(row)
	{
	case 0:
		LCD_cursorAdress = column;
		break;
	case 1:
		LCD_cursorAdress = 0x40 + column;
		break;
	case 2:
		LCD_cursorAdress = 0x10 + column;
		break;
	case 3:
		LCD_cursorAdress = 0x50 + column;
		break;
	}
	LCD_cursorAdress |= LCD_SET_CURSOR_LOCATION ;
	LCD_sendCommand(LCD_cursorAdress);
}

/*******************************************************************************
* Function Name:		LCD_displayStringRowColumn
********************************************************************************/

void LCD_displayStringRowColumn(u8 row , u8 column , char * string)
{
	LCD_moveCursor(row,column);
	LCD_displayString(string);
}

/*******************************************************************************
* Function Name:		LCD_intgerToString
********************************************************************************/

void LCD_intgerToString(long number)
{
	char buffer[16];
	itoa(number,buffer,10);
	LCD_displayString(buffer);
}
