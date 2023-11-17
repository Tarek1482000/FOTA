/*=================================================================================*/
/*  File        : SWITCH Interface.h                                               */
/*  Description : This Header file includes LCD SWITCH Interface                   */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/

#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

typedef enum
{
	SA0,SA1,SA2,SA3,SA4,SA5,SA6,SA7,SA8,SA9,SA10,SA11,SA12,SA13,SA14,SA15,
	SB0,SB1,SB2,SB3,SB4,SB5,SB6,SB7,SB8,SB9,SB10,SB11,SB12,SB13,SB14,SB15,
	SC13=45,SC14,SC15
}SWITCH_NUM;

typedef enum
{
	SW_FLOATING,
	SW_PULLUP,
	SW_PULLDOWN
}SWITCH_EDGE;

/*******************************************************************************
 * Function Name:		SWITCH_init
 ********************************************************************************/
u8 SWITCH_init(SWITCH_NUM SWITCH , SWITCH_EDGE edge_state);
/*******************************************************************************
 * Function Name:		SWITCH_FALLIG
 ********************************************************************************/
u8 SWITCH_FALLIG(SWITCH_NUM SWITCH);
/*******************************************************************************
 * Function Name:		SWITCH_RAISING
 ********************************************************************************/
u8 SWITCH_RAISING(SWITCH_NUM SWITCH);


#endif /* SWITCH_INTERFACE_H_ */
