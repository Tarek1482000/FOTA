/*=================================================================================*/
/*  File        : LCD_Config.h                                                     */
/*  Description : This Header file includes LCD Config                             */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*******************************************************************************
*                        		Configurations                                 *
*******************************************************************************/

#define LCD_u8_DATA_BITS_MODE	4

#if((LCD_u8_DATA_BITS_MODE != 4) && (LCD_u8_DATA_BITS_MODE != 8))

#error "Number of Data bits should be 4 or 8"

#endif

#define LCD_u8_RS_PORT_ID				GPIO_u8_GPIOA
#define LCD_u8_RS_PIN_ID				GPIO_u8_PIN12
#define LCD_u8_RS_RCC_BUS				RCC_u8_GPIOA

#define LCD_u8_E_PORT_ID				GPIO_u8_GPIOB
#define LCD_u8_E_PIN_ID					GPIO_u8_PIN5
#define LCD_u8_E_RCC_BUS				RCC_u8_GPIOB

#define LCD_u8_DATA_PORT_ID				GPIO_u8_GPIOB
#define LCD_u8_RCC_BUS					RCC_u8_GPIOB

#if LCD_u8_DATA_BITS_MODE == 8

#define LCD_u8_PORT_START_PIN			GPIO_u8_PIN8

#elif (LCD_u8_DATA_BITS_MODE == 4)

#define LCD_u8_DB4_PIN_ID               GPIO_u8_PIN6
#define LCD_u8_DB5_PIN_ID               GPIO_u8_PIN7
#define LCD_u8_DB6_PIN_ID               GPIO_u8_PIN8
#define LCD_u8_DB7_PIN_ID               GPIO_u8_PIN9

#endif

#endif /* LCD_CONFIG_H_ */
