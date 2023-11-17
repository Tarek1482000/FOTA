/*=================================================================================*/
/*  File        : LCD Interface.h                                                  */
/*  Description : This Header file includes LCD Interface                          */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

void LCD_sendCommand(u8 command);

void LCD_init(void);

void LCD_displayCharacter(u8 data);

void LCD_displayString(char * string);

void LCD_clearScreen();

void LCD_moveCursor(u8 row,u8 column);

void LCD_displayStringRowColumn(u8 row , u8 column , char * string);

void LCD_intgerToString(long number);

#endif /* LCD_INTERFACE_H_ */
