/*=================================================================================*/
/*  File        : main.c                                                           */
/*  Description : This Program file  For Numbering Application                    */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 15/11/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/

#include "HAL/CALCULATOR/NUMBERING/NUMBERING_Interface.h"
#include "HAL/SYSTEM/SYSTYM_Interface.h"
int main(void)
{
	SYSTEM_Init();

	Numbering_Init();

	for(;;)
	{
		Numbering_Start();
	}
}
