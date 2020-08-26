/*
 * hmi.h
 *
 *  Created on: Feb 18, 2020
 *      Author: shahira ibrahim
 */

#ifndef HMI_H_
#define HMI_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"


#define DOOR_PORT_DIR             DDRB
#define DOOR_PORT_OUT             PORTB
#define DOOR_PORT_IN              PINB
#define DOOR_PIN                  PB0

#define WEIGHT_SENSOR_PORT_DIR    DDRB
#define WEIGHT_SENSOR_PORT_OUT    PORTB
#define WEIGHT_SENSOR_PORT_IN     PINB
#define WEIGHT_SENSOR_PIN         PB1

#define START_HEATING_PORT_DIR    DDRB
#define START_HEATING_PORT_OUT    PORTB
#define START_HEATING_PORT_IN     PINB
#define START_HEATING_PIN         PB2


#define HEATER_PORT_DIR     DDRD
#define HEATER_PORT_OUT     PORTD
#define HEATER_FIRST_PIN    PD6
#define HEATER_SECOND_PIN   PD7

#define HEATER_LAMP_PORT_DIR  DDRD
#define HEATER_LAMP_PORT_OUT  PORTD
#define HEATER_LAMP_PIN       PD4


extern volatile uint8 DoorLocked;
extern volatile uint8 FoodIn;
extern volatile uint8 timeIsSet;
extern volatile uint8 start_Heating;
extern volatile uint8 cancelHeating;
extern volatile uint8 time[2];
extern volatile uint32 intger_time;
extern volatile uint32 g_ticks;
extern volatile uint32 minutes;
extern volatile uint32 seconds;
void INT0_INIT(void);

void stopHeating(void);

void startHeating(void);

void MicroWave_Setting(void);

int setTime (void);

#endif /* HMI_H_ */
