/*
 * functions.h
 *
 *  Created on: Sep 7, 2021
 *      Author: AhmedAlaa
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/* Enumerations and Macros */

#define ERROR404() (printf("Error 404: Not Found!\n"))

typedef enum {
	FAILED, SUCCEED, EXIT
} FLAG;

typedef enum {
	ON, OFF
} ENGINE_STATE;


/* Functions Prototypes */
FLAG ask_for_engine_state(ENGINE_STATE *state);
FLAG repeat_until_succeed_or_exit(ENGINE_STATE *state);

#endif /* FUNCTIONS_H_ */
