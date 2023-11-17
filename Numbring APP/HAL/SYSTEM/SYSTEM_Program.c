/*=================================================================================*/
/*  File        : SYSTEM Program.c                                                 */
/*  Description : This Program file includes SYSTEM program                        */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/


#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/STK/STK_interface.h"
#include "SYSTYM_Interface.h"

void SYSTEM_Init(void)
{
	STK_u8Init(STK_u8_AHB);
	RCC_u8InitSysClk();
}
