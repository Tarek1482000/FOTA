/*=================================================================================*/
/*  File        : Parser Program.c                                                 */
/*  Description : This Program file includes Parser program                        */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/FPEC/FPEC_interface.h"

u16 Data[100] = {0};
u32 FLASH_ADDRESS= 0x08000000;

static u8 AsciToHex(u8 Ascii)
{
	u8 Result = 0;

	if(Ascii >= '0' && Ascii <= '9')
	{
		Result = Ascii - '0' ;
	}
	else if(Ascii >= 'A' && Ascii <='F')
	{
		Result = Ascii - 55 ; // 55 ='A'- 10
	}
	return Result;
}

void ParseData(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[0]);
	DigitLow  = AsciToHex (Copy_u8BufData[1]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get FLASH_ADDRESS */
	DataDigit0 = AsciToHex (Copy_u8BufData[2]);
	DataDigit1 = AsciToHex (Copy_u8BufData[3]);
	DataDigit2 = AsciToHex (Copy_u8BufData[4]);
	DataDigit3 = AsciToHex (Copy_u8BufData[5]);

	/* Clear Low Part of FLASH_ADDRESS */
	FLASH_ADDRESS = FLASH_ADDRESS & 0xFFFF0000;
	FLASH_ADDRESS = FLASH_ADDRESS |
			(DataDigit3)      |
			(DataDigit2 << 4) |
			(DataDigit1 << 8) |
			(DataDigit0 <<12);

	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+8 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+9]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+11]);

		/*
		 * 0 4 0 F 4 0 0 0 DATA=>9 F 4 F
		 * DataDigit0 = 9
		 * DataDigit1 = F
		 * DataDigit2 = 4
		 * DataDigit3 = F
		 */

		Data[DataCounter] =	(DataDigit3 << 8)  | (DataDigit2 << 12) |(DataDigit1) |	(DataDigit0<<4);
		DataCounter++;
	}

//	FLASH_ADDRESS = 0x00003A00;
	FPEC_voidFlashWrite(FLASH_ADDRESS,Data,CC/2);
}

void ParseUpperAddress(u8* Copy_u8BufData)
{
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;

	/* Get FLASH_ADDRESS */
	DataDigit0 = AsciToHex (Copy_u8BufData[2]);
	DataDigit1 = AsciToHex (Copy_u8BufData[3]);
	DataDigit2 = AsciToHex (Copy_u8BufData[4]);
	DataDigit3 = AsciToHex (Copy_u8BufData[5]);

	/*
	 * 020000040800F2
	 * 0 2 Address =>> 0 0 0 0 0 4 DATA=>0 8 0 0 F2
	 * DataDigit0 = 0
	 * DataDigit1 = 0
	 * DataDigit2 = 0
	 * DataDigit3 = 0
	 * FLASH_ADDRESS = 0x0800 0000 & (u32)0x0000 FFFF;
	 * FLASH_ADDRESS = 0x0000 FFFF | (u32)0x0000 0000;
	 */

	/* Clear Low Part of FLASH_ADDRESS */
	FLASH_ADDRESS = FLASH_ADDRESS & (u32)0x0000FFFF;
	FLASH_ADDRESS = FLASH_ADDRESS | (u32)(
			(u32)(DataDigit3 << 28) |
			(u32)(DataDigit2 << 24) |
			(u32)(DataDigit1 << 20) |
			(u32)(DataDigit0 << 16));
}

void Parser_voidParseRecord(u8* Copy_u8BufData)
{
	switch (Copy_u8BufData[7])
	{
	case '0': ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); break;
	}
}
