/*
 * lcd.c
 *
 *  Created on: Apr 24, 2019
 *      Author: shahira ibrahim
 */
/*
 * lcd.c
 *
 *  Created on: Apr 23, 2019
 *      Author: shahira ibrahim
 */
#include "lcd.h"

/******************************functions definition********************************************/

/*function description:function for setting the control pins for LCD
 * Check for wether it's a 4 or 8 bit mode
 * disabling cursor
 * clearing the LCD screen
 */
void LCD_init(void)
{
	/*set lcd control pins as an output*/
	LCD_PORT_DIR =(1<<RS)|(1<<RW)|(1<<E);

/*check if data bit mode whether it's a four bit mode or eight bit mode*/
#if(DATA_BIT_MODE==4)

  #ifdef UPPER_DATA_PINS

	/* configure the highest bit in data port as an output*/
	LCD_PORT_DATA_DIR |= 0XF0;
  #else

	/* configure the lowest bit in data port as an output*/
	LCD_PORT_DATA_DIR |= 0X0F;
  #endif

	/*set the lcd on the four bit mode*/
	LCD_sendCommand(LCD_FOUR_BITS_MODE);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BIT_MODE);

#elif(DATA_BIT_MODE==8)
	LCD_PORT_DATA_DIR |= 0XFF;
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BIT_MODE);
#endif

	/*disable the cursor*/
	LCD_sendCommand(CURSOR_OFF);

	 /*at the beginning clear the lcd*/
	LCD_sendCommand(CLEAR_SCREEN);

}


/*function description:function for sending LCD commands*/
void LCD_sendCommand(uint8 command)
{
	//by clearing RS bit command register is selected
	CLEAR_BIT(LCD_PORT_OUT,RS);

	//write data to the lcd
	CLEAR_BIT(LCD_PORT_OUT,RW);

	 /* delay for processing Tas = 50ns */
	_delay_ms(1);

	//enabling the lcd
	SET_BIT(LCD_PORT_OUT,E);

	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);


 #if ( DATA_BIT_MODE == 4)
     #ifdef UPPER_DATA_PINS

	//sending the highest bits of data first through PC4-->PC7 TO PD4-->PD7
	   LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0X0F) | (command & 0XF0);
     #else

	//sending the highest bits of data first through PC0-->PC4 TO PD4-->PD7
	   LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0XF0) | ((command & 0XF0)>>4);
     #endif

	  /*delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/*disable LCD E=0 */
	CLEAR_BIT(LCD_PORT_OUT,E);

	/*delay for processing Th = 13ns */
	_delay_ms(1);


	/****************the beginning of sending the lowest bits of data***************/

	//enabling the lcd
	SET_BIT(LCD_PORT_OUT,E);

	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);


     #ifdef UPPER_DATA_PINS

	//sending the lowest bits of data first through PC4-->PC7 TO PD4-->PD7
	    LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0X0F) | ((command & 0X0F)<<4);
     #else

	//sending the lowest bits of data first through PC0-->PC4 TO PD4-->PD7
	 LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0XF0) | (command & 0X0F);
     #endif

	 /* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* disable LCD E=0 */
	CLEAR_BIT(LCD_PORT_OUT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);


#elif (DATA_BIT_MODE==8)

	//sending the whole command through PC0->PC7 TO PD0->PD7
	LCD_PORT_DATA_OUT=command;

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* disable LCD E=0 */
	CLEAR_BIT(LCD_PORT_OUT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);
#endif

}


/*function description:function for displaying one character on LCD*/
void LCD_sendCharacter(uint8 data)
{
	//by setting RS bit data register is selected
	SET_BIT(LCD_PORT_OUT,RS);

	//write data to the lcd
	CLEAR_BIT(LCD_PORT_OUT,RW);

	/* delay for processing Tas = 50ns */
	_delay_ms(1);

	//enabling the lcd
	SET_BIT(LCD_PORT_OUT,E);

	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

#if(DATA_BIT_MODE==4)
      #ifdef UPPER_DATA_PINS

	//sending the highest bits of data first through PC4-->PC7 TO PD4-->PD7
	    LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0X0F) | (data & 0XF0);
	  #else

	//sending the highest bits of data first through PC0-->PC4 TO PD4-->PD7
	    LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0XF0) | ((data & 0XF0)>>4);
	  #endif

	 /* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* disable LCD E=0 */
	CLEAR_BIT(LCD_PORT_OUT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);


	/************************the beginning of sending the lowest bits of data********************/

	//enabling the lcd
	SET_BIT(LCD_PORT_OUT,E);

	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

	 #ifdef UPPER_DATA_PINS
	//sending the lowest bits of data first through PC4-->PC7 TO PD4-->PD7
		LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0X0F) | ((data & 0X0F)<<4);
	#else
	//sending the lowest bits of data first through PC0-->PC4 TO PD4-->PD7
		LCD_PORT_DATA_OUT = (LCD_PORT_DATA_OUT & 0XF0) | (data & 0X0F);
	#endif

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* disable LCD E=0 */
	CLEAR_BIT(LCD_PORT_OUT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);

#elif(DATA_BIT_MODE==8)

	//sending the whole command through PC0->PC7 TO PD0->PD7
	LCD_PORT_DATA_OUT=data;

	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* disable LCD E=0 */
	CLEAR_BIT(LCD_PORT_OUT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);
#endif

}


/*function description: function for commanding the LCD to start on specific row and column location*/
void LCD_goTo_Location(uint8 row,uint8 col)
{
	uint8 address;
	switch (row)
	{
	case 0:
	    address=col;
		break;
	case 1:
		/*(0x40) is the address of the second row*/
		address=col+(0x40);
		break;
	case 2:
		/*(0x10) is the address of the  third row*/
		address=col+(0x10);
		break;
	case 4:
		/*(0x50) is the address of the fourth row*/
		address=col+(0x50);
		break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(address | SET_COUSOR_LOCATION);
}



/*function decription:function for printing a whole string on LCD*/
void LCD_sendString(const char * string){
	uint8 i=0;

	/*loop through the whole string until it hit the null terminator*/
	while(string[i] != '\0'){

		//sending string character by character
		LCD_sendCharacter(string[i]);
		i++;
	}
}


/*function description: function for clearing LCD screen*/
void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_SCREEN);
}


/*function description:function for printing a string in a specific row and column location on LCD screen*/
void LCD_display_In_Location(const char *data,uint8 row,uint8 col){
	LCD_goTo_Location( row,col);
	LCD_sendString(data);
}


/*function description:function for transforming an integer to array of characters then printing it on LCD*/
void LCD_interToString(int num)
{
	 char buffer[16];
	itoa(num,buffer,10);
	LCD_sendString(buffer);

}


