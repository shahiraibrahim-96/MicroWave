/*
 * main.c
 *
 *  Created on: Feb 15, 2020
 *      Author: shahira ibrahim
 */


#include "lcd.h"
#include "keypad.h"
#include "timers.h"
#include "hmi.h"


int main (void){


	LCD_init();
	MicroWave_Setting();
	INT0_INIT();
	SREG  |= (1<<7);
	uint32 num=0;
	LCD_clearScreen();
	LCD_sendString("HeatTime=00:00");
	while(1){


	if( (DoorLocked !=1) ||  (FoodIn !=1) ){

		if(BIT_IS_SET(DOOR_PORT_IN,DOOR_PIN)){

			_delay_ms(30);
			if(BIT_IS_SET(DOOR_PORT_IN,DOOR_PIN)){
				DoorLocked=1;

			}

		}
		if(BIT_IS_SET(WEIGHT_SENSOR_PORT_IN,WEIGHT_SENSOR_PIN)){
			_delay_ms(30);
			if(BIT_IS_SET(WEIGHT_SENSOR_PORT_IN,WEIGHT_SENSOR_PIN))
			{
				FoodIn=1;

			}

		}



	}

  if(timeIsSet==0)
  {
	  num= setTime();
  }

     while(timeIsSet ==1 && FoodIn ==1 && DoorLocked ==1 ){
				if(BIT_IS_SET(START_HEATING_PORT_IN ,START_HEATING_PIN))
				{
					start_Heating=1;

					TIMER1_CTCMode(FCPU_64,31250);
					do{
						startHeating();
					}while(g_ticks <  num && !cancelHeating );
					TIMER1_OFF();
					g_ticks=0;
					intger_time=0;
					stopHeating();
					cancelHeating=0;
					DoorLocked=0;
					FoodIn=0;
					timeIsSet=0;
					start_Heating=0;

				}

     }






	}

}

