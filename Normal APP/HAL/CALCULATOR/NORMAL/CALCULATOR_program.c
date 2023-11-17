/*=================================================================================*/
/*  File        : CALCULATOR Program.c                                             */
/*  Description : This Program file includes CALCULATOR program                    */
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
#include "CALCULATOR_config.h"
#include "CALCULATOR_interface.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/



u8  key=0,      //Store Keypad value
num1_counter=0,  //number1 counter store digits
num2_counter=0,  //number2 counter store digits
opration=0;      //Store operation type

f32 number1[10]={0}, //First Number
		number2[10]={0}, //Second NumberS
		result=0;        //Calculation Result


void Caculator_Init(void)
{
	LCD_init();
	KEYPAD_Init();
	LCD_displayStringRowColumn(0, 0, "APP1 Calculator");
	LCD_displayStringRowColumn(1, 0, "A + B - C * D /");
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}

/*
 * Description :
 * Get the first number and operation of calculation
 */
void First_NUM(void)
{
	num1_counter=0;//start from digit 1
	while(1)
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);

		/*
		 * Break loop when user complete entering first number and operation
		 */
		if(key == '+' || key == '-' || key == '/' || key == '*')
		{
			opration=key;
			LCD_displayCharacter(opration);
			break;
		}
		/*
		 * Store all digits of first number and display number on LCD
		 */
		number1[num1_counter]=key;
		num1_counter++;
		LCD_intgerToString(key);
	}
}


/*
 * Description :
 * Get the first number and operation of calculation
 */
void Second_NUM(void)
{
	num2_counter=0;
	while(1)
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);

		/*
		 * Break loop when user complete entering second number
		 */
		if(key == '=')
		{
			LCD_displayCharacter(key);
			break;
		}

		/*
		 * Store all digits of second number and display number on LCD
		 */
		number2[num2_counter]=key;
		num2_counter++;
		LCD_intgerToString(key);
	}
}




/*
 * Description :
 * Concatenate all digits of two number then display result of sum on LCD
 */
void calc_sum(f32 *first_num,f32*second_num,u8 digit1,u8 digit2)
{
	f32 num1=first_num[0];
	f32 num2=second_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(u8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(u8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1, 0);
	LCD_intgerToString(num1+num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}


/*
 * Description :
 * Concatenate all digits of two number then display result of sub on LCD
 */
void calc_sub(f32 *first_num,f32*second_num,u8 digit1,u8 digit2)
{
	u16 num1=first_num[0];
	u16 num2=second_num[0];
	/*
	 *  Concatenate all digits of first number
	 */
	for(u8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(u8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1,0);
	LCD_intgerToString(num1-num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}


/*
 * Description :
 * Concatenate all digits of two number then display result of multi on LCD
 */
void calc_multi(f32 *first_num,f32*second_num,u8 digit1,u8 digit2)
{
	f32 num1=first_num[0];
	f32 num2=second_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(u8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(u8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1, 0);
	LCD_intgerToString(num1*num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}



/*
 * Description :
 * Concatenate all digits of two number then display result of div on LCD
 */
void calc_div(f32 *first_num,f32*second_num,u8 digit1,u8 digit2)
{
	f32 num1=first_num[0];
	f32 num2=second_num[0];

	/*
	 *  Concatenate all digits of first number
	 */
	for(u8 counter=1;counter<digit1;counter++)
	{
		num1 = num1*10 +first_num[counter];
	}
	/*
	 *  Concatenate all digits of second number
	 */
	for(u8 counter=1;counter<digit2;counter++)
	{
		num2= num2*10 +second_num[counter];
	}


	/*
	 *  Display result on LCD and wait until enter c
	 */
	LCD_moveCursor(1,0);
	LCD_intgerToString(num1/num2);
	while(key != 'c')
	{
		key=KEYPAD_getPressedKey();
		STK_u8SetmSBusyWait(200);
	}
	LCD_clearScreen();
}



/*
 * Description :
 *  Get two number and operation and do operation and display it on screen
 */
void Caculator_Start(void)
{

	/*
	 * Get first number and operation
	 */
	First_NUM();

	/*
	 * Get first number and operation
	 */
	Second_NUM();

	/*
	 * Do operation calculation
	 */
	switch(opration)
	{
	case '+':
		calc_sum(number1, number2, num1_counter, num2_counter);
		break;
	case '-':
		calc_sub(number1, number2, num1_counter, num2_counter);
		break;
	case '*':
		calc_multi(number1, number2, num1_counter, num2_counter);
		break;
	case '/':
		calc_div(number1, number2, num1_counter, num2_counter);
		break;
	}

}
