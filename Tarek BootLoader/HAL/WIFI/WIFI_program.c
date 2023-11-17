/*=================================================================================*/
/*  File        : Wifi Program.c                                                   */
/*  Description : This Program file includes Wifi program                          */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/

/**************************************************** Library Inclusions *************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include"../../MCAL/UART/UART_interface.h"
#include"../../MCAL/STK/STK_interface.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/HexParser/Parse.h"
/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/
#include"WIFI_intrface.h"
#include"WIFI_private.h"
#include"WIFI_config.h"

/***************************************************** Global Variables **************************************************************/

static volatile u8 g_FlashingDoneFlag = 0;
static volatile u8 g_BufferEmpty = 0;
extern volatile u8 g_update_Found;
/*************************************************************************************************************************************/
/***************************************************** Functions Definition **********************************************************/
/*************************************************************************************************************************************/


/**************************************************************************************************************************************
 * Function Name	: WIFI_voidInit																				                  *
 * Parameters (in)	: None																						                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Initialize All Config of the wifi module										                      *
 **************************************************************************************************************************************/
void WIFI_voidInit(void)
{
	UART_configStruct_t ESP_UARTConfig = { 115200,'#', UART_u8_STOP_1_BIT, UART_u8_8_BITS, UART_u8_PARITY_DISABLED, UART_u8_POLLING};

	UART_u8Init(WIFI_UART, &ESP_UARTConfig);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "WIFI Init");
	UART_u8SendString(WIFI_UART, (u8*) "ATE0\r\n");
	STK_u8SetmSBusyWait(3500);
	UART_u8SendString(WIFI_UART, (u8*) "AT+CWMODE=1\r\n");
	STK_u8SetmSBusyWait(3500);
	LCD_clearScreen();
	//	WIFI_voidConnectToWifi();
}

/**************************************************************************************************************************************
 * Function Name	: HWIFI_voidConnectToWifi																		                  *
 * Parameters (in)	: None																						                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Connect to the router															                      *
 **************************************************************************************************************************************/
void WIFI_voidConnectToWifi(void)
{
	u8 buffer[50];
	LCD_displayStringRowColumn(0, 0, "Connect to Wifi...");
	sprintf(buffer,"AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, WIFI_PASSWORD);
	UART_u8SendString(WIFI_UART, (u8*) buffer);
	STK_u8SetmSBusyWait(10000);
	LCD_clearScreen();
}


/**************************************************************************************************************************************
 * Function Name	: void WIFI_Check_update																                          *
 * Parameters (in)	: None								           								                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None         																						              *
 * Description		: Function To Receive Extract the Data from the Record										                      *
 **************************************************************************************************************************************/
void WIFI_Check_update(void)
{
	u8 data[10] , i=0;
	LCD_displayStringRowColumn(0, 0, "Checking Update");

	WIFI_VoidSendHttpRequest((u8*)DATA_LENGHT_UPDATE,(u8*)SERVER_LINK_UPDATE);

	Wifi_start_page();

	UART_u8ReceiveByte(WIFI_UART, &data[i]);
	while(data [i] != 'C')
	{
		i++;
		UART_u8ReceiveByte(WIFI_UART, &data[i]);
	}
	if(data[0] == 'E' && data[1] == 'A' && data[2] == 'F' && data[3] == '1')
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "New Update Found");
		g_update_Found = 1;
		STK_u8SetmSBusyWait(1000);
	}
	else
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "No Update Found");
		STK_u8SetmSBusyWait(500);
		LCD_clearScreen();
	}
}

/**************************************************************************************************************************************
 * Function Name	: HWIFI_VoidReceiveRecord																		                  *
 * Parameters (in)	: None																	                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Recieve Extract the Data from the Record										                      *
 **************************************************************************************************************************************/
void WIFI_VoidReceiveRecords_NACK(void)
{
	u8 data[RECORD_CHAR_NUM] ;
	WIFI_VoidSendHttpRequest((u8*)DATA_LENGHT_HEX,(u8*)SERVER_LINK_HEX);
	LCD_displayStringRowColumn(0, 0,"Receive Records ");
	Wifi_start_page();

	while(!g_FlashingDoneFlag)
	{
		Wifi_filter_record_NACK(data);
		if(g_BufferEmpty == 1)
		{
			g_BufferEmpty = 0;
			continue;
		}
		Parser_voidParseRecord(data);
	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"Flashing Done");
	STK_u8SetmSBusyWait(300);
	LCD_clearScreen();
}

/**************************************************************************************************************************************
 * Function Name	: Wifi_start_page    																		                      *
 * Parameters (in)	: None                       																			          *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Indicate page start   								                                              *
 **************************************************************************************************************************************/
void Wifi_start_page(void)
{
	u8 data = 0;
	UART_u8ReceiveByte(WIFI_UART, &data);
	while(data != '+')
		UART_u8ReceiveByte(WIFI_UART, &data);
	while(data != ':')
		UART_u8ReceiveByte(WIFI_UART, &data);
}

/**************************************************************************************************************************************
 * Function Name	: Wifi_collect_record_NACK																	                      *
 * Parameters (in)	: *data                       																			          *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Indicate page start   								                                              *
 **************************************************************************************************************************************/
void Wifi_filter_record_NACK(u8 *data)
{
	u16 i = 0;
	u8 flag = 0;

	if(g_FlashingDoneFlag)return;

	UART_u8ReceiveByte(WIFI_UART, &data[i]);

	if(data[i] == '\r')
	{
		UART_u8ReceiveByte(WIFI_UART, &data[i]);
		g_BufferEmpty = 1;
		return;
	}

	if(data[i] == '+')
	{
		while(data[i] != ':')
			UART_u8ReceiveByte(WIFI_UART, &data[i]);
		flag = 1;
	}


	while(data[i] != '\n')
	{
		i++;
		if(flag == 1 || data[0] == ':' )
		{
			flag = 0;
			i =  0;
		}
		UART_u8ReceiveByte(WIFI_UART, &data[i]);

	}
	if(data[i] == '\n')
	{
		data[i-1] = '\0'; /* To remove /r */
	}

	if(data[i-2] == 'F'  && data[i-3] == 'F' && data[i-4] == '1')
	{
		g_FlashingDoneFlag = 1;
	}
}



/**************************************************************************************************************************************
 * Function Name	: HWIFI_VoidReceiveRecord																		                  *
 * Parameters (in)	: None																	                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Recieve Extract the Data from the Record										                      *
 **************************************************************************************************************************************/
void WIFI_VoidReceiveRecords_ACK(void)
{
	u8 data[RECORD_CHAR_NUM] ;
	LCD_displayStringRowColumn(0, 0,"Receive Records ");
	WIFI_VoidOK_ACK();
	STK_u8SetmSBusyWait(10);
	while(!g_FlashingDoneFlag)
	{
		WIFI_VoidSendHttpRequest((u8*)DATA_LENGHT_RECORD,(u8*)SERVER_LINK_RECORD);
		Wifi_filter_record_ACK(data);
		if(g_BufferEmpty)
		{
			g_BufferEmpty = 0;
			WIFI_VoidOK_ACK();
			STK_u8SetmSBusyWait(1);
			continue;
		}
		Parser_voidParseRecord(data);
		WIFI_VoidOK_ACK();
		STK_u8SetmSBusyWait(1);
	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"Update Done");
	LCD_displayStringRowColumn(1, 0,"Successfully");
	STK_u8SetmSBusyWait(300);
	LCD_clearScreen();
}


/**************************************************************************************************************************************
 * Function Name	: Wifi_filter_record_ACK																	                      *
 * Parameters (in)	: *data                       																			          *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Indicate page start   								                                              *
 **************************************************************************************************************************************/
void Wifi_filter_record_ACK(u8 *data)
{
	u16 i = 0 ;
	u8 delay = 0;
	Wifi_start_page();
	UART_u8ReceiveByte(WIFI_UART, &data[i]);

	if(data[i] == '\r')
	{
		UART_u8ReceiveByte(WIFI_UART, &data[i]);
		g_BufferEmpty = 1;
		return;
	}

	while(data[i] != '\n')
	{
		i++;
		if(data[0] == ':' )
		{
			i =  0;
		}
		UART_u8ReceiveByte(WIFI_UART, &data[i]);

	}
	if(data[i] == '\n')
	{
		data[i-1] = '\0'; /* To remove /r */
	}

	if(data[i-2] == 'F'  && data[i-3] == 'F' && data[i-4] == '1')
	{
		g_FlashingDoneFlag = 1;
	}
	UART_u8ReceiveByte(WIFI_UART, &delay);
	while(delay != 'D')
		UART_u8ReceiveByte(WIFI_UART,  &delay);

	UART_u8ReceiveByte(WIFI_UART, &delay); /* \r */
	UART_u8ReceiveByte(WIFI_UART, &delay); /* \n */

}



/**************************************************************************************************************************************
 * Function Name	: WIFI_VoidOK_ACK																	                              *
 * Parameters (in)	: None												     					                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None												 										                      *
 * Description		: To Send Next Record                               										                      *
 **************************************************************************************************************************************/
void WIFI_VoidOK_ACK(void)
{
	u8 data = 0;
	WIFI_VoidSendHttpRequest((u8*)DATA_LENGHT_RESPONSE_OK,(u8*)SERVER_LINK_RESPONSE_OK);
	UART_u8ReceiveByte(WIFI_UART, &data);
	while(data != 'L')
		UART_u8ReceiveByte(WIFI_UART, &data);
	while(data != '\n')
		UART_u8ReceiveByte(WIFI_UART, &data);
}


/**************************************************************************************************************************************
 * Function Name	: WIFI_VoidSendHttpRequest																				          *
 * Parameters (in)	: DATA_LENGHT , SERVER_LINK	     			                                                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Send Http Request             												                      *
 **************************************************************************************************************************************/
void WIFI_VoidSendHttpRequest(u8 *DATA_LENGHT ,u8 *SERVER_LINK)
{
	u8 buffer[50] , data = 0;
	sprintf(buffer, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", DOMAIN, PORT);
	UART_u8SendString(WIFI_UART, (u8*) buffer);

	UART_u8ReceiveByte(WIFI_UART, &data);
	while(data != 'K' )
		UART_u8ReceiveByte(WIFI_UART, &data);
	UART_u8ReceiveByte(WIFI_UART, &data); /* \r */
	UART_u8ReceiveByte(WIFI_UART, &data); /* \n */

	UART_u8SendString(WIFI_UART,DATA_LENGHT);
	UART_u8ReceiveByte(WIFI_UART, &data);
	while(data != '>' )
		UART_u8ReceiveByte(WIFI_UART, &data);
	UART_u8ReceiveByte(WIFI_UART, &data); /* \r */
	UART_u8ReceiveByte(WIFI_UART, &data); /* \n */

	UART_u8SendString(WIFI_UART,SERVER_LINK);
}

/**************************************************************************************************************************************
 * Function Name	: WIFI_VoidClearBuffer																		                      *
 * Parameters (in)	: * data																	                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: clear the array										                                                          *
 **************************************************************************************************************************************/
void WIFI_VoidClearBuffer(u8 *data)
{
	for(u8 i = 0 ; i<RECORD_CHAR_NUM-1;i++)
		data[i] = 0;
}

