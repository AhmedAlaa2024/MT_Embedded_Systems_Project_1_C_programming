/*
 ============================================================================
 Name        : Project.c
 Author      : Ahmed Alaa
 Version     : 1.0v
 Copyright   : for Ahmed Alaa
 Description : Vehicle Control System Simulation
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

extern int INPUT_COUNT; // This is just for make the console pretty

#include "vehicle_sys.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/* Configurations */
	VEHICLE vehicle;
	SYSTEM_FLAG system_flag;

	INPUT_COUNT = 1;
	vehicle.room_temperature = 27;
	vehicle.engine_temprature = 90;
	// Start the User Interface
	printf("Welcome To Vehicle Control System (VCS)\n");

	/* Main Super Loop */
	while(1)
	{
		system_flag = ask_for_system_state(&vehicle); // Ask the user for choice of main menu

		if (system_flag == EXIT) // If the user chose to exit the system
		{
			printf("Logging out...\n");
			break; // Stop the processing of the program
		}
		else if (system_flag == SYS_OFF) // If the user ask to turn off the engine
		{
			show_engine_state(&vehicle); // Monitor the engine state
			continue; // Repeat the main menu
		}
		else if (system_flag == SYS_ON) // If the user ask to turn on the engine
		{
			turn_on_engine(&vehicle);

			/* Super Loop */
			while (1)
			{
				system_flag = ask_for_sensors_states(&vehicle); // Show the sensor states menu and ask him for one choice

				if (system_flag == SYS_OFF) // If the user ask to turn off the engine
				{
					turn_off_engine(&vehicle);
					break; // Repeat the main menu
				}
				else if (system_flag == TRAFFIC_LIGHT_REQUEST) // If the user ask to set traffic light color
				{
					set_traffic_light_color(&vehicle); // Ask the user to enter the traffic light color
					set_vehicle_speed(&vehicle); // Determine the speed regarding to the traffic light color
				}
				else if (system_flag == ROOM_TEMPERATURE_REQUEST) // If the user ask to set room temperature
				{
					set_room_temperature(&vehicle); // Ask the user to enter the room temperature and make its calculations
				}
				// ENGINE_TEMPERATURE_REQUEST is enable flag to engine temperature treatment
				else if ((system_flag == ENGINE_TEMPERATURE_REQUEST) && (WITH_ENGINE_TEMP_CONTROLLER == 1)) // If the user ask to set engine temperature
				{
					set_engine_temperature(&vehicle); // Ask the user to enter the engine temperature and make its calculations
				}

				if (vehicle.speed == 30)
				{
					vehicle.TC = TC_ON;
					vehicle.engine_temprature *= (5.0/4);
					vehicle.engine_temprature += 1;

					vehicle.AC = AC_ON;
					vehicle.room_temperature *= (5.0/4);
					vehicle.room_temperature += 1;
				}

					display_current_vehicle_state(&vehicle);
			}
			display_current_vehicle_state(&vehicle);
		}
	}

	printf("##################################################################\n");
	printf("Thanks for you. Come again!\n");
	return EXIT_SUCCESS;
}
