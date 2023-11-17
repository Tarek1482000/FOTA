/*=================================================================================*/
/*  File        : SWITCH Program.c                                                 */
/*  Description : This Header file includes LCD SWITCH Program                     */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
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
#include "SWITCH_Interface.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:		SWITCH_init
 ********************************************************************************/
u8 SWITCH_init(SWITCH_NUM SWITCH, SWITCH_EDGE edge_state)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(SWITCH>= SA0 && SWITCH <= SA15)
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOA, RCC_u8_Enable);

		if(edge_state==SW_PULLDOWN)
			GPIO_u8SetPinMode(GPIO_u8_GPIOA,SWITCH % 16, GPIO_u8_INPUT_PULL_DOWN);
		else if (edge_state==SW_PULLUP)
			GPIO_u8SetPinMode(GPIO_u8_GPIOA,SWITCH % 16, GPIO_u8_INPUT_PULL_UP);
		else if (edge_state==SW_FLOATING)
			GPIO_u8SetPinMode(GPIO_u8_GPIOA,SWITCH % 16, GPIO_u8_INPUT_FLOATING);
	}
	else if(SWITCH>= SB0 && SWITCH <= SB15)
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOB, RCC_u8_Enable);
		if(edge_state==SW_PULLDOWN)
			GPIO_u8SetPinMode(GPIO_u8_GPIOB,SWITCH % 16, GPIO_u8_INPUT_PULL_DOWN);
		else if (edge_state==SW_PULLUP)
			GPIO_u8SetPinMode(GPIO_u8_GPIOB,SWITCH % 16, GPIO_u8_INPUT_PULL_UP);
		else if (edge_state==SW_FLOATING)
			GPIO_u8SetPinMode(GPIO_u8_GPIOB,SWITCH % 16, GPIO_u8_INPUT_FLOATING);
	}
	else if(SWITCH>= SC13 && SWITCH <= SC15)
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOC, RCC_u8_Enable);
		if(edge_state==SW_PULLDOWN)
			GPIO_u8SetPinMode(GPIO_u8_GPIOC,SWITCH % 16, GPIO_u8_INPUT_PULL_DOWN);
		else if (edge_state==SW_PULLUP)
			GPIO_u8SetPinMode(GPIO_u8_GPIOC,SWITCH % 16, GPIO_u8_INPUT_PULL_UP);
		else if (edge_state==SW_FLOATING)
			GPIO_u8SetPinMode(GPIO_u8_GPIOC,SWITCH % 16, GPIO_u8_INPUT_FLOATING);
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
 * Function Name:		SWITCH_FALLIG
 ********************************************************************************/
u8 SWITCH_FALLIG(SWITCH_NUM SWITCH)
{
	u8 data = 0;
	if(SWITCH>= SA0 && SWITCH <= SA15)
	{
		GPIO_u8GetPinValue(GPIO_u8_GPIOA,SWITCH % 16, &data);
	}
	else if(SWITCH>= SB0 && SWITCH <= SB15)
	{
		GPIO_u8GetPinValue(GPIO_u8_GPIOB,SWITCH % 16, &data);
	}
	else if(SWITCH>= SC13 && SWITCH <= SC15)
	{
		GPIO_u8GetPinValue(GPIO_u8_GPIOC,SWITCH % 16,& data);
	}
	if(data == 0)
		return 1;
	else
		return 0;
}


/*******************************************************************************
 * Function Name:		SWITCH_RAISING
 ********************************************************************************/
u8 SWITCH_RAISING(SWITCH_NUM SWITCH)
{
	u8 data = 0;
	if(SWITCH>= SA0 && SWITCH <= SA15)
	{
		GPIO_u8GetPinValue(GPIO_u8_GPIOA,SWITCH % 16, &data);
	}
	else if(SWITCH>= SB0 && SWITCH <= SB15)
	{
		GPIO_u8GetPinValue(GPIO_u8_GPIOB,SWITCH % 16, &data);
	}
	else if(SWITCH>= SC13 && SWITCH <= SC15)
	{
		GPIO_u8GetPinValue(GPIO_u8_GPIOC,SWITCH % 16, &data);
	}
	if(data == 1)
		return 1;
	else
		return 0;
}
