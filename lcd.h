/*
 * lcd.h
 *
 *  Created on: Apr 23, 2019
 *      Author: shahira ibrahim
 */

#ifndef LCD_H_
#define LCD_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/********************************************preprocessors***************************************/

//LCD hardware control  PINS
#define RS  PB4
#define RW  PB5
#define E   PB6

//LCD  control  registers
#define LCD_PORT_DIR DDRB
#define LCD_PORT_OUT PORTB

//LCD data registers
#define LCD_PORT_DATA_DIR DDRC
#define LCD_PORT_DATA_OUT PORTC

//lcd bit mode
#define DATA_BIT_MODE 8

//if 4 bit mode is enabled use the upper pins in data port
#if (DATA_BIT_MODE==4)
#define UPPER_DATA_PINS
#endif


/***********************************LCD COMMANDS***********************************************/
#define CLEAR_SCREEN 0X01
#define CURSOR_ON    0X0E
#define CURSOR_OFF   0X0C
#define SET_COUSOR_LOCATION 0X80
#define LCD_FOUR_BITS_MODE 0x02
#define LCD_TWO_LINES_EIGHT_BIT_MODE 0x38
#define LCD_TWO_LINES_FOUR_BIT_MODE  0X28
/****************************************************************************************************/

/***********************************functions prototype**********************************************/

/*function description:function for setting the control pins for LCD
 * Check for wether it's a 4 or 8 bit mode
 * disabling cursor
 * clearing the LCD screen
 */
void LCD_init(void);

/*function description:function for sending LCD commands*/
void LCD_sendCommand(uint8 command);

/*function description:function for displaying one character on LCD*/
void LCD_sendCharacter(uint8 data);

/*function decription:function for printing a whole string on LCD*/
void LCD_sendString(const char * string);

/*function description: function for clearing LCD screen*/
void LCD_clearScreen(void);

/*function description: function for commanding the LCD to start on specific row and column location*/
void LCD_goTo_Location(uint8 row,uint8 col);

/*function description:function for printing a string in a specific row and column location on LCD screen*/
void LCD_display_In_Location(const char *data,uint8 row,uint8 col);

/*function description:function for transforming an integer to array of characters then printing it on LCD*/
void LCD_interToString(int num);


#endif /* LCD_H_ */
