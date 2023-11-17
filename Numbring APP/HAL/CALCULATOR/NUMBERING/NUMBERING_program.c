/*=================================================================================*/
/*  File        : NUMBERING Program.c                                              */
/*  Description : This Program file includes NUMBERING program                     */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

#include "../../../MCAL/STK/STK_interface.h"
#include "../../../HAL/LCD/LCD_interface.h"
#include "../../../HAL/KEYPAD/KEYPAD_interface.h"

#include "NUMBERING_Interface.h"
#include "NUMBERING_Private.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

u8  keyy=0,      //Store keyypad value
num_counter=0,  //number counter store digits
num[10] = {0},
oper=0;      //Store operation type
u16 full_num = 0;


/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/


void Numbering_Init(void)
{
	LCD_init();
	KEYPAD_Init();
	LCD_displayStringRowColumn(0, 0, "APP2 NUMBERING");
	LCD_displayStringRowColumn(1, 0, "A D>B B D>X");
	while(keyy != 'c')
	{
		keyy=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}

/*
 * Description :
 * Get the first number and operation of calculation
 */
void getFirstNumberAndOperation(void)
{
	num_counter = 0;  // Start from digit 1
	while (1)
	{
		keyy = KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);

		/*
		 * Break loop when user completes entering the first number and operation
		 */
		if (keyy == '+' || keyy == '-')
		{
			oper = keyy;
			LCD_displayString("  D>");
			if (oper == '+')
				LCD_displayCharacter('B');
			else if (oper == '-')
				LCD_displayCharacter('X');
			break;
		}

		/*
		 * Store all digits of the first number and display the number on LCD
		 */
		num[num_counter] = keyy;
		num_counter++;
		LCD_intgerToString(keyy);

		// Define a constant for the maximum number of digits
		const u8 MAX_DIGITS = 11;
		if (num_counter == MAX_DIGITS)
			break;
	}

	// Convert the stored digits to a full number
	full_num = num[0];
	for (u8 counter = 1; counter < num_counter; counter++)
	{
		full_num = full_num * 10 + num[counter];
	}
}



/*
 * Description :
 *  Get two number and operation and do operation and display it on screen
 */
void Numbering_Start(void)
{

	/*
	 * Get number and operation
	 */
	getFirstNumberAndOperation();

	/*
	 * Do operation calculation
	 */
	switch(oper)
	{
	case '+':
		Numbering_DEC_BIN(full_num);
		break;
	case '-':
		Numbering_DEC_HEX(full_num);
		break;
	}

}

void Numbering_DEC_BIN(u16 num)
{

	LCD_moveCursor(1, 0);
	for (int i = 15; i >= 0; i--)
	{
		LCD_intgerToString((num >> i) & 1);
	}
	while(keyy != 'c')
	{
		keyy=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}


void Numbering_DEC_HEX(u16 num)
{
	u8 hex[5];  // Assuming a 16-bit integer, so at most 4 hexadecimal digits
	u8 index = 0;

	// Convert decimal to hexadecimal
	do
	{
		s32 remainder = num % 16;
		hex[index++] = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		num /= 16;
	} while (num > 0);

	// Display the hexadecimal representation
	LCD_moveCursor(1, 0);
	LCD_displayString("0x");
	for (s8 i = index - 1; i >= 0; i--)
	{
		LCD_displayCharacter(hex[i]);
	}

	while(keyy != 'c')
	{
		keyy=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}
