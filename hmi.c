/*
 * hmi.c
 *
 *  Created on: Feb 18, 2020
 *      Author: shahira ibrahim
 */
#include "hmi.h"
#include "lcd.h"
#include "keypad.h"

volatile uint8 DoorLocked=0;
volatile uint8 FoodIn=0;
volatile uint8 timeIsSet=0;
volatile uint8 start_Heating=0;
volatile uint8 cancelHeating=0;
volatile uint8 time[2]={0};
volatile uint32 intger_time=0;
volatile uint32 minutes=0;
volatile uint32 seconds=0;

static int stringIntoDecimal(char *str);

ISR(INT0_vect){

if(start_Heating)
{
	cancelHeating =1;
}
else{
	g_ticks=0;
	intger_time=0;
	minutes=0;
	seconds=0;
	LCD_goTo_Location(0,9);
	LCD_sendString("00");
	LCD_goTo_Location(0,12);
	LCD_sendString("00");
	DoorLocked=0;
	FoodIn=0;
	timeIsSet=0;
}


}
void MicroWave_Setting(void){

	    CLEAR_BIT( DOOR_PORT_DIR,DOOR_PIN );
		CLEAR_BIT( WEIGHT_SENSOR_PORT_DIR, WEIGHT_SENSOR_PIN ) ;
		CLEAR_BIT( START_HEATING_PORT_DIR,START_HEATING_PIN ) ;


		CLEAR_BIT( WEIGHT_SENSOR_PORT_OUT, WEIGHT_SENSOR_PIN ) ;
		CLEAR_BIT( START_HEATING_PORT_OUT,START_HEATING_PIN ) ;
		CLEAR_BIT(DOOR_PORT_OUT,DOOR_PIN );

		SET_BIT(HEATER_PORT_DIR ,HEATER_FIRST_PIN) ;
		SET_BIT(HEATER_PORT_DIR ,HEATER_SECOND_PIN ) ;
		CLEAR_BIT(HEATER_PORT_OUT,HEATER_FIRST_PIN);
		CLEAR_BIT(HEATER_PORT_OUT,HEATER_SECOND_PIN);

		SET_BIT(HEATER_LAMP_PORT_DIR ,HEATER_LAMP_PIN ) ;
		CLEAR_BIT(HEATER_LAMP_PORT_OUT,HEATER_LAMP_PIN );


}
void startHeating(void)
{
	SET_BIT(HEATER_LAMP_PORT_OUT ,HEATER_LAMP_PIN ) ;
	SET_BIT(HEATER_PORT_OUT,HEATER_FIRST_PIN);
	CLEAR_BIT(HEATER_PORT_OUT,HEATER_SECOND_PIN);
}

void stopHeating(void){

	CLEAR_BIT(HEATER_LAMP_PORT_OUT ,HEATER_LAMP_PIN ) ;
	CLEAR_BIT(HEATER_PORT_OUT,HEATER_FIRST_PIN);
	CLEAR_BIT(HEATER_PORT_OUT,HEATER_SECOND_PIN);


}

void INT0_INIT(void){

	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge

}
static int stringIntoDecimal(char *str)
{
    int i=0,num=0;
    while(i<2)
    {
        num=(num*10)+(str[i]);
        i++;
    }

     return num;
}

int setTime(void){

int i;

LCD_goTo_Location(0,9);
LCD_interToString(time[0]);
time[1]=Keypad_getKeyPressed();
LCD_goTo_Location(0,10);
LCD_interToString(time[1]);
_delay_ms(250);
minutes=stringIntoDecimal(time);

time[0]=0;
time[1]=0;
  for(i=0;i<2;i++)
  {

	  time[i]=Keypad_getKeyPressed();
	  LCD_goTo_Location(0,i+12);
	  LCD_interToString(time[i]);
	  _delay_ms(250);

  }
  intger_time=stringIntoDecimal(time);
	  if( intger_time >= 60)
	  {
		  LCD_goTo_Location(0,12);
		  LCD_sendString("  ");
		  LCD_goTo_Location(0,9);
		  LCD_sendString("  ");
		  LCD_goTo_Location(0,9);
		  minutes++;
		  LCD_interToString(minutes);
		  seconds=intger_time-60;
		  LCD_goTo_Location(0,12);
		  LCD_interToString(seconds);
	  }
	  else
	  {
		  seconds= intger_time;
	  }

  intger_time +=(minutes*60);
  timeIsSet=1;
  return intger_time;

}


