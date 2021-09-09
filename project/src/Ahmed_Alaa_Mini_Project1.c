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

#include "functions.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/* Configurations */
	FLAG stage1 = FAILED;
	ENGINE_STATE engine_state;

	// Start the User Interface
	printf("Welcome To Vehicle Control System (VCS)\n");

	/* Super Loop */
	while(1)
	{
		stage1 = ask_for_engine_state(&engine_state);

		if (stage1 == EXIT)
		{
			printf("Logging out...\n");
			break;
		}
		else if (stage1 == FAILED)
			stage1 = repeat_until_succeed_or_exit(&engine_state);

		break;
	}

	printf("Thanks for you. Come again!\n");
	return EXIT_SUCCESS;
}