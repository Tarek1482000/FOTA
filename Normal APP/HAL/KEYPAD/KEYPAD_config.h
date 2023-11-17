/*=================================================================================*/
/*  File        : KEYPAD_Config.h                                                  */
/*  Description : This Header file includes KEYPAD Config                          */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*******************************************************************************
*                        		Configurations                                 *
*******************************************************************************/

//#define STANDARD_KEYPAD

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                GPIO_u8_GPIOA
#define KEYPAD_FIRST_ROW_PIN_ID           GPIO_u8_PIN4

#define KEYPAD_COL_PORT_ID                GPIO_u8_GPIOA
#define KEYPAD_FIRST_COL_PIN_ID           GPIO_u8_PIN0

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            GPIO_u8_LOW
#define KEYPAD_BUTTON_RELEASED           GPIO_u8_HIGH


#endif /* KEYPAD_CONFIG_H_ */
