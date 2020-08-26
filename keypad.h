/*
 * keypad.h
 *
 *  Created on: Apr 23, 2019
 *      Author: shahira ibrahim
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/**************************************************preprocessors*******************************************/
#define NUM_COL 3   /* number of columns of keypad*/
#define NUM_ROW 4   /* number of rows of keypad*/

//KeyPad hardware registers
#define KEYPAD_PORT_DIR  DDRA
#define KEYPAD_PORT_OUT  PORTA
#define KEYPAD_PORT_IN   PINA
/**************************************************************************************************/



/*******************************************function prototype*********************************/
/*function description:function for returning the pressed switch on keypad*/
uint8 Keypad_getKeyPressed(void);

#endif /* KEYPAD_H_ */
