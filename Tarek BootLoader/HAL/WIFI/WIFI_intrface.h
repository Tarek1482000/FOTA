/*=================================================================================*/
/*  File        : Wifi Interface.h                                                 */
/*  Description : This Header file includes Wifi Interface                         */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef WIFI_INTERFACE_H
#define WIFI_INTERFACE_H

#include "../../LIB/STD_TYPES.h"
/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/

/**************************************************************************************************************************************
 * Function Name	: WIFI_voidInit																				                  *
 * Parameters (in)	: None																						                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Initialize All Config of the wifi module										                      *
 **************************************************************************************************************************************/
void WIFI_voidInit(void);
/**************************************************************************************************************************************
 * Function Name	: HWIFI_voidConnectToWifi																		                  *
 * Parameters (in)	: None																						                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Connect to the router															                      *
 **************************************************************************************************************************************/
void WIFI_voidConnectToWifi(void);
/**************************************************************************************************************************************
 * Function Name	: void WIFI_Check_update																                          *
 * Parameters (in)	: None								           								                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None         																						              *
 * Description		: Function To Receive Extract the Data from the Record										                      *
 **************************************************************************************************************************************/
void WIFI_Check_update(void);

/**************************************************************************************************************************************
 * Function Name	: void WIFI_VoidReceiveRecords_NACK																                  *
 * Parameters (in)	: None								           								                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Receive Extract the Data from the Record										                      *
 **************************************************************************************************************************************/
void WIFI_VoidReceiveRecords_NACK(void);
/**************************************************************************************************************************************
 * Function Name	: Wifi_filter_record_NACK																	                      *
 * Parameters (in)	: *data                       																			          *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Indicate page start   								                                              *
 **************************************************************************************************************************************/
void Wifi_filter_record_NACK(u8 *data);
/**************************************************************************************************************************************
 * Function Name	: Wifi_start_page    																		                      *
 * Parameters (in)	: None                       																			          *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Indicate page start   								                                              *
 **************************************************************************************************************************************/
void Wifi_start_page(void);
/**************************************************************************************************************************************
 * Function Name	: void WIFI_VoidReceiveRecords_ACK																                  *
 * Parameters (in)	: None								           								                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Receive Extract the Data from the Record using ACK							                      *
 **************************************************************************************************************************************/
void WIFI_VoidReceiveRecords_ACK(void);
/**************************************************************************************************************************************
 * Function Name	: Wifi_filter_record_ACK																	                      *
 * Parameters (in)	: *data                       																			          *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Indicate page start   								                                              *
 **************************************************************************************************************************************/
void Wifi_filter_record_ACK(u8 *data);
/**************************************************************************************************************************************
 * Function Name	: WIFI_VoidSendHttpRequest																				          *
 * Parameters (in)	: DATA_LENGHT , SERVER_LINK	     			                                                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: Function To Send Http Request             												                      *
 **************************************************************************************************************************************/
void WIFI_VoidSendHttpRequest(u8 *DATA_LENGHT ,u8 *SERVER_LINK);
/**************************************************************************************************************************************
 * Function Name	: WIFI_VoidClearBuffer																		                  *
 * Parameters (in)	: * data																	                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None																						                      *
 * Description		: clear the array										                      *
 **************************************************************************************************************************************/
void WIFI_VoidClearBuffer(u8 *data);
/**************************************************************************************************************************************
 * Function Name	: WIFI_VoidOK_ACK																	                              *
 * Parameters (in)	: None												     					                                      *
 * Parameters (out)	: None																						                      *
 * Return value		: None												 										                      *
 * Description		: To Send Next Record                               										                      *
 **************************************************************************************************************************************/
void WIFI_VoidOK_ACK(void);

#endif /*WIFI_INTERFACE_H*/
