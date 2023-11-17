/*=================================================================================*/
/*  File        : KEYPAD Interface.h                                               */
/*  Description : This Header file includes KEYPAD Interface                       */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "KEYPAD_config.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
void KEYPAD_Init(void);
u8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_INTERFACE_H_ */
