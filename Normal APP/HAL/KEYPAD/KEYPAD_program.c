/*=================================================================================*/
/*  File        : KEYPAD Program.c                                                 */
/*  Description : This Program file includes KEYPAD program                        */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/STK/STK_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static u8 KEYPAD_4x3_adjustKeyNumber(u8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void KEYPAD_Init(void)
{
	if(KEYPAD_ROW_PORT_ID == GPIO_u8_GPIOA || KEYPAD_COL_PORT_ID == GPIO_u8_GPIOA )
	{
		RCC_u8EnableDisablPeripheralClk(RCC_u8_GPIOA ,RCC_u8_Enable);
	}
	if(KEYPAD_ROW_PORT_ID == GPIO_u8_GPIOB || KEYPAD_COL_PORT_ID == GPIO_u8_GPIOB )
	{
		RCC_u8EnableDisablPeripheralClk(GPIO_u8_GPIOB ,RCC_u8_Enable);
	}
	if(KEYPAD_ROW_PORT_ID == GPIO_u8_GPIOC || KEYPAD_COL_PORT_ID == GPIO_u8_GPIOC )
	{
		RCC_u8EnableDisablPeripheralClk(GPIO_u8_GPIOC ,RCC_u8_Enable);
	}
}


u8 KEYPAD_getPressedKey(void)
{
	u8 col = 0,row = 0,data = 0;

	GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID,   GPIO_u8_INPUT_PULL_UP);
	GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, GPIO_u8_INPUT_PULL_UP);
	GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, GPIO_u8_INPUT_PULL_UP);
	GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, GPIO_u8_INPUT_PULL_UP);

	GPIO_u8SetPinMode(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID,   GPIO_u8_INPUT_PULL_UP);
	GPIO_u8SetPinMode(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, GPIO_u8_INPUT_PULL_UP);
	GPIO_u8SetPinMode(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, GPIO_u8_INPUT_PULL_UP);

#if(KEYPAD_NUM_COLS == 4)
	GPIO_u8SetPinMode(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, GPIO_u8_INPUT_PULL_UP);
#endif

	while(1)
	{
		STK_u8SetmSBusyWait(50);
		for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,GPIO_u8_OUTPUT_GP_PP_50MHZ);

			/* Set/Clear the row output pin */
			GPIO_u8WritePinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				GPIO_u8GetPinValue(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col,&data);
				if( data == KEYPAD_BUTTON_PRESSED)
				{
#if (KEYPAD_NUM_COLS == 3)
#ifdef STANDARD_KEYPAD
					return ((row*KEYPAD_NUM_COLS)+col+1);
#else
					return KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
#endif
#elif (KEYPAD_NUM_COLS == 4)
#ifdef STANDARD_KEYPAD
					return ((row*KEYPAD_NUM_COLS)+col+1);
#else
					return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
#endif
#endif
				}
			}
			GPIO_u8SetPinMode(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,GPIO_u8_INPUT_PULL_UP);
		}
	}
}

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static u8 KEYPAD_4x3_adjustKeyNumber(u8 button_number)
{
	u8 keypad_button = 0;
	switch(button_number)
	{
	case 10: keypad_button = '*'; // ASCII Code of *
	break;
	case 11: keypad_button = 0;
	break;
	case 12: keypad_button = '#'; // ASCII Code of #
	break;
	default: keypad_button = button_number;
	break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number)
{
	u8 keypad_button = 0;
	switch(button_number)
	{
	case 1: keypad_button = 1;
	break;
	case 2: keypad_button = 2;
	break;
	case 3: keypad_button = 3;
	break;
	case 4: keypad_button = '+'; // ASCII Code of A
	break;
	case 5: keypad_button = 4;
	break;
	case 6: keypad_button = 5;
	break;
	case 7: keypad_button = 6;
	break;
	case 8: keypad_button = '-'; /* ASCII Code of 'B' */
	break;
	case 9: keypad_button  = 7;
	break;
	case 10: keypad_button = 8;
	break;
	case 11: keypad_button = 9;
	break;
	case 12: keypad_button = '*'; /* ASCII Code of 'C' */
	break;
	case 13: keypad_button = 'c';  /* ASCII Code of '*' */
	break;
	case 14: keypad_button = 0;
	break;
	case 15: keypad_button = '='; /* ASCII Code of '#' */
	break;
	case 16: keypad_button = '/'; /* ASCII Code of '+' */
	break;
	default: keypad_button = button_number;
	break;
	}
	return keypad_button;
}

#endif

#endif /* STANDARD_KEYPAD */
