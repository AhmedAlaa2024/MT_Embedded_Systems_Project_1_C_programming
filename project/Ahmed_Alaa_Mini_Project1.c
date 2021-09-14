/*
 ============================================================================
 Name        : Ahmed_Alaa_Mini_Project1.c
 Author      : Ahmed Alaa
 Version     : 1.0v
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

extern int INPUT_COUNT;

#include "functions.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/* Configurations */
	VEHICLE vehicle = {RED, ENGINE_OFF};
	SYSTEM_FLAG system_flag = ENGINE_OFF;

	INPUT_COUNT = 1;

	int traffic_data = 0, room_temperature_data = 0, engine_temperature_data = 0;

	// Start the User Interface
	printf("Welcome To Vehicle Control System (VCS)\n");

	/* Super Loop */
	while(1)
	{
		system_flag = ask_for_system_state(&vehicle); // Ask the user for choice

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
		else if (system_flag == SYS_ON)
		{
			turn_on_engine(&vehicle);

			while (1)
			{
				system_flag = ask_for_sensors_states(&vehicle); // Show the sensor states menu and ask him for one choice

				if (system_flag == SYS_OFF) // If the user ask to turn off the engine
				{
					turn_off_engine(&vehicle);
					traffic_data = room_temperature_data = engine_temperature_data = 0;
					break; // Repeat the main menu
				}
				else if (system_flag == TRAFFIC_LIGHT_REQUEST)
				{
					set_traffic_light_color(&vehicle);
					set_vehicle_speed(&vehicle);
					traffic_data = 1;
				}
				else if (system_flag == ROOM_TEMPERATURE_REQUEST)
				{
					set_room_temperature(&vehicle);
					room_temperature_data = 1;
				}
				else if ((system_flag == ENGINE_TEMPERATURE_REQUEST) && (WITH_ENGINE_TEMP_CONTROLLER == 1))
				{
					set_engine_temperature(&vehicle);
					engine_temperature_data = 1;
				}

				if(traffic_data && room_temperature_data && engine_temperature_data)
					display_current_vehicle_state(&vehicle);
			}
		}
	}

	printf("##################################################################\n");
	printf("Thanks for you. Come again!\n");
	return EXIT_SUCCESS;
}
