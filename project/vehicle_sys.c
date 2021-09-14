/*
 ============================================================================
 Name        : vehicle_sys.c
 Author      : Ahmed Alaa
 Version     : 1.0v
 Copyright   : for Ahmed Alaa
 Description : Vehicle Control System Simulation
 ============================================================================
 */

#include <stdio.h>
#include "vehicle_sys.h"

int INPUT_COUNT = 1;

SYSTEM_FLAG ask_for_system_state(VEHICLE *vehicle){
	/* User Interface */
	printf("###############################################################################\n");
	printf("Please, Choose just one option [a - b - c]\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	printf("Enter the character of your choice\n");
	printf("Input[%d]: ", INPUT_COUNT++);

	// Ask for user's choice
	char choice;
	scanf(" %c", &choice);

	/* Super Loop */
	while (1) // The loop will terminate if the input is valid
	{
		/* States flow */
		if ((choice == 'a') || (choice == 'A'))
		{
			vehicle->Engine = ENGINE_ON;
			return SYS_ON;
		}
		else if ((choice == 'b') || (choice == 'B'))
		{
			vehicle->Engine = ENGINE_OFF;
			return SYS_OFF;
		}
		else if ((choice == 'c') || (choice == 'C'))
		{
			vehicle->Engine = ENGINE_OFF;
			return EXIT;
		}
		else
		{
			ERROR404();
			printf("###############################################################################\n");
			printf("Enter again the character of your choice");
			printf("Input[%d]: ", INPUT_COUNT++);
			scanf(" %c", &choice);
		}
	}
}


void show_engine_state(VEHICLE *vehicle)
{
	printf("###############################################################################\n");
	if (vehicle->Engine == ENGINE_ON)
		printf("Monitoring:\n\t=> Engine State: ON\n");
	else if (vehicle->Engine == ENGINE_OFF)
		printf("Monitoring:\n\t=> Engine State: OFF\n");
}


SYSTEM_FLAG ask_for_sensors_states(VEHICLE *vehicle)
{
	printf("###############################################################################\n");
	if (WITH_ENGINE_TEMP_CONTROLLER == 1)
		printf("Please, Choose just one option [a - b - c - d]\n");
	else
		printf("Please, Choose just one option [a - b - c]\n");

	printf("a. Turn off the vehicle engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");

	if (WITH_ENGINE_TEMP_CONTROLLER == 1)
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n");

	printf("Enter the character of your choice\n");
	printf("Input[%d]: ", INPUT_COUNT++);

	// Ask for user's choice
	char choice;
	scanf(" %c", &choice);

	/* Super Loop */
	while(1) // The loop will be terminated if the input is valid
	{
		/* States flow */
		if ((choice == 'a') || (choice == 'A'))
		{
			vehicle->Engine = ENGINE_OFF;
			return SYS_OFF;
		}
		else if ((choice == 'b') || (choice == 'B'))
		{
			vehicle->Engine = ENGINE_ON;
			return TRAFFIC_LIGHT_REQUEST;
		}
		else if ((choice == 'c') || (choice == 'C'))
		{
			vehicle->Engine = ENGINE_ON;
			return ROOM_TEMPERATURE_REQUEST;
		}
		else if (((choice == 'd') || (choice == 'D')) && (WITH_ENGINE_TEMP_CONTROLLER == 1))
		{
			vehicle->Engine = ENGINE_ON;
			return ENGINE_TEMPERATURE_REQUEST;
		}
		else
		{
			ERROR404();
			printf("###############################################################################\n");
			printf("Enter again the character of your choice\n");
			printf("Input[%d]: ", INPUT_COUNT++);
			scanf(" %c", &choice);
		}
	}
}


void set_traffic_light_color(VEHICLE *vehicle)
{
	printf("###############################################################################\n");
	char color;
	printf("Please, Enter the traffic light color: [R -> Red, O -> Orange, G -> Green]\n");
	printf("Input[%d]: ", INPUT_COUNT++);
	scanf(" %c", &color);

	char flag = 0; // Flag indicate the input is valid or not, It will be raised if the input is valid only

	while(!flag)
	{
		switch (color)
		{
			case 'r':
				vehicle->traffic_light_color = RED;
				flag = 1;
				break;
			case 'R':
				vehicle->traffic_light_color = RED;
				flag = 1;
				break;
			case 'o':
				vehicle->traffic_light_color = ORANGE;
				flag = 1;
				break;
			case 'O':
				vehicle->traffic_light_color = ORANGE;
				flag = 1;
				break;
			case 'g':
				vehicle->traffic_light_color = GREEN;
				flag = 1;
				break;
			case 'G':
				vehicle->traffic_light_color = GREEN;
				flag = 1;
				break;
		}

		if(flag)
		{
			printf("=> Saved Successfully!\n");
			break;
		}

		ERROR404();
		printf("###############################################################################\n");
		printf("Please, Enter a valid traffic light color: [R -> Red, Y -> Yellow, G -> Green]\n");
		printf("Input[%d]: ", INPUT_COUNT++);
		scanf(" %c", &color);
	}
}


void set_vehicle_speed(VEHICLE *vehicle)
{
	switch (vehicle->traffic_light_color)
	{
		case GREEN:
			vehicle->speed = 100;
			break;
		case ORANGE:
			vehicle->speed = 30;
			break;
		case RED:
			vehicle->speed = 0;
			break;
	}
}


void set_room_temperature(VEHICLE *vehicle)
{
	printf("###############################################################################\n");
	printf("Please, Enter the room temperature\n");
	printf("Input[%d]: ", INPUT_COUNT++);
	scanf(" %f", &(vehicle->room_temperature));
	printf("=> Saved Successfully!\n");

	if (vehicle->room_temperature < 10)
	{
		vehicle->AC = AC_ON;
		vehicle->room_temperature = 20;
	}
	else if (vehicle->room_temperature > 30)
	{
		vehicle->AC = AC_ON;
		vehicle->room_temperature = 20;
	}
	else
		vehicle->AC = AC_OFF;
}


void set_engine_temperature(VEHICLE *vehicle)
{
	printf("###############################################################################\n");
	printf("Please, Enter the engine temperature\n");
	printf("Input[%d]: ", INPUT_COUNT++);
	scanf(" %f", &(vehicle->engine_temprature));
	printf("=> Saved Successfully!\n");

	if (vehicle->engine_temprature < 100)
	{
		vehicle->TC = TC_ON;
		vehicle->engine_temprature = 125;
	}
	else if (vehicle->engine_temprature > 150)
	{
		vehicle->TC = TC_ON;
		vehicle->engine_temprature = 125;
	}
	else
		vehicle->TC = TC_OFF;
}


void display_current_vehicle_state(VEHICLE *vehicle)
{
	printf("###############################################################################\n");
	printf("<Monitoring The Vehicle State>\n");

	if (vehicle->Engine == ENGINE_ON)
		printf("\t=> Engine State: ON\n");
	else
		printf("\t=> Engine State: OFF\n");

	if (vehicle->AC == AC_ON)
		printf("\t=> AC: ON\n");
	else
		printf("\t=> AC: OFF\n");

	printf("\t=> Vehicle Speed: %d\n", vehicle->speed);

	printf("\t=> Room Temperature: %0.1f\n", vehicle->room_temperature);

	if (WITH_ENGINE_TEMP_CONTROLLER == 1)
	{
		if (vehicle->TC == TC_ON)
			printf("\t=> Engine Temperature Controller State: ON\n");
		else
			printf("\t=> Engine Temperature Controller State: OFF\n");

		printf("\t=> Engine Temperature: %0.1f\n", vehicle->engine_temprature);
	}

}


void turn_on_engine(VEHICLE *vehicle)
{
	vehicle->Engine = ENGINE_ON;
	show_engine_state(vehicle); // Monitor the engine state
}


void turn_off_engine(VEHICLE *vehicle)
{
	vehicle->Engine = ENGINE_OFF;
	vehicle->AC = AC_OFF;
	vehicle->TC = TC_OFF;
	vehicle->speed = 0;

	show_engine_state(vehicle); // Monitor the engine state
}
