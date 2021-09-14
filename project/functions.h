/*
 * functions.h
 *
 *  Created on: Sep 7, 2021
 *      Author: AhmedAlaa
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/* Enumerations and Macros */
#define WITH_ENGINE_TEMP_CONTROLLER 1
#define ERROR404() (printf("Error 404: Not Found!\n"))

typedef enum {
	EXIT, SYS_OFF, SYS_ON, TRAFFIC_LIGHT_REQUEST, ROOM_TEMPERATURE_REQUEST, ENGINE_TEMPERATURE_REQUEST
} SYSTEM_FLAG;

typedef enum {
	ENGINE_OFF, ENGINE_ON
} ENGINE_STATE;
typedef enum {
	RED, ORANGE, GREEN
} TRAFFIC_LIGHT;

typedef enum {
	AC_OFF, AC_ON
} AC_STATE;

typedef enum {
	TC_OFF, TC_ON
} ENGINE_TC_STATE;

typedef struct {
	ENGINE_STATE Engine;
	AC_STATE AC;
	TRAFFIC_LIGHT traffic_light_color;
	ENGINE_TC_STATE TC;
	float room_temperature;
	float engine_temprature;
	int speed; // Speed unit is km/hr
} VEHICLE;


/* Functions Prototypes */
SYSTEM_FLAG ask_for_system_state(VEHICLE *vehicle);
void show_engine_state(VEHICLE *vehicle);

void turn_on_engine(VEHICLE *vehicle);
void turn_off_engine(VEHICLE *vehicle);

SYSTEM_FLAG ask_for_sensors_states(VEHICLE *vehicle);
void set_traffic_light_color(VEHICLE *vehicle);
void set_vehicle_speed(VEHICLE *vehicle);
void set_room_temperature(VEHICLE *vehicle);
void set_engine_temperature(VEHICLE *vehicle);
void display_current_vehicle_state(VEHICLE *vehicle);

#endif /* FUNCTIONS_H_ */
