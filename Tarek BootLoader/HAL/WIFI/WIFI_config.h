/*=================================================================================*/
/*  File        : Wifi Config.h                                                    */
/*  Description : This Header file includes Wifi Config                            */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

/**************************************************************************************************************************************
 * MACRO	: 	To Configure WIFI_UART																			         		      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define WIFI_UART 					        						UART_u8_1
/**************************************************************************************************************************************
 * MACRO	: 	To Configure RECORD_CHAR_NU																			         	      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define RECORD_CHAR_NUM 											100
/**************************************************************************************************************************************
 * MACRO	: 	To Configure SSID																					                  *
 * options	:																														  *
 **************************************************************************************************************************************/
#define SSID 														""
/**************************************************************************************************************************************
 * MACRO	: 	To Configure WIFI_PASSWORD																			       		      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	WIFI_PASSWORD												""
/**************************************************************************************************************************************
 * MACRO	: 	To Configure Server DOMAIN																			       		      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define DOMAIN 														""
/**************************************************************************************************************************************
 * MACRO	: 	To Configure Server PORT																			       		      *
 * options	:																													      *
 **************************************************************************************************************************************/
#define	PORT														"80"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure DATA_LENGHT_HEX																		         	      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	DATA_LENGHT_HEX												"AT+CIPSEND=56\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure SERVER_LINK_HEX																		         	      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	SERVER_LINK_HEX												"GET http://otaupdatesolutions.orgfree.com/Hex_file.txt\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure DATA_LENGHT_UPDATE																		         	      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	DATA_LENGHT_UPDATE											"AT+CIPSEND=54\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure SERVER_LINK_UPDATE								    										         	  *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	SERVER_LINK_UPDATE 											"GET http://********Update.txt\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure DATA_LENGHT_RECORD																		         	      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	DATA_LENGHT_RECORD											"AT+CIPSEND=59\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure SERVER_LINK_RECORDS								    										          *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	SERVER_LINK_RECORD 											"GET http://********/Record_line.txt\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure DATA_LENGHT_RESPONSE_OK																		          *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	DATA_LENGHT_RESPONSE_OK										"AT+CIPSEND=74\r\n"
/**************************************************************************************************************************************
 * MACRO	: 	To Configure SERVER_LINK_RESPONSE_OK								    										      *
 * options	:																														  *
 **************************************************************************************************************************************/
#define	SERVER_LINK_RESPONSE_OK										"GET http://********/Receive_record.php?response=ok\r\n"

#endif /*WIFI_CONFIG_H*/  