/*
 * keypad.c
 *
 *  Created on: Apr 24, 2019
 *      Author: shahira ibrahim
 */

/*
 * keypad.c
 *
 *  Created on: Apr 23, 2019
 *      Author: shahira ibrahim
 */

#include "keypad.h"

/***********************************function prototypes*************************************************/
#if (NUM_COL==4)
static uint8 adjust_keypad_4x4_number(uint8 keyPressed);

#elif (NUM_COL==3)
static uint8 adjust_keypad_4x3_number(uint8 keyPressed);

#endif




/********************************functions definitions*******************************************/


/*function description:function for returning the pressed switch on keypad*/
uint8 Keypad_getKeyPressed(void)
{
	uint8 row=0,col=0;
	while(1)
	{
		for(col=0;col<NUM_COL;col++)
		{
			//set one column as an output each time
			KEYPAD_PORT_DIR =(0b00010000<<col);

			//enabling the pull up resistors on rows and clear the output column
			KEYPAD_PORT_OUT =(~(0b00010000<<col));

			//knowing which switch got pressed by looping through rows
			for(row=0;row<NUM_ROW;row++)
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
                    #if (NUM_COL==4)
					  return adjust_keypad_4x4_number(((row*NUM_COL)+col+1));
                    #elif (NUM_COL==3)
					  return adjust_keypad_4x3_number(((row*NUM_COL)+col+1));
                    #endif
				}

			}
		}

	}
}


/*function description:function for manipulating the returning numbers from Keypad_getKeyPressed
 * to return the corresponding actual numbers and characters on the 4X3keypad
 */
#if (NUM_COL==3)
static uint8 adjust_keypad_4x3_number(uint8 keyPressed)
{
	switch(keyPressed)
	{
	case 10:
		return '*';
		break;
	case 11:
		return 0;
		break;
	case 12:
		return '#';
		break;
	default:
		return  keyPressed;

	}
}

/*function description:function for manipulating the returning numbers from Keypad_getKeyPressed
 * to return the corresponding actual numbers and characters on the 4X4keypad
 */
#elif (NUM_COL==4)
static uint8 adjust_keypad_4x4_number(uint8 keyPressed)
{
	switch(keyPressed)
	{
	case 1:
		return 7;
		break;
	case 2:
		return 8;
		break;
	case 3:
		return 9;
		break;
	case 4:
		return '/';
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 5;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return '*';
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 2;
		break;
	case 11:
		return 3;
		break;
	case 12:
		return '-';
		break;
	case 13:
		return 13;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return '=';
		break;
	case 16:
		return '+';
		break;

	default:
		return  keyPressed;

	}
}
#endif

