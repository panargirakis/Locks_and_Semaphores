/*
* Project 3 - Part 2 - Taming Massachusetts Drivers
* Panos Argyrakis and Amanda Chan
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "helpers_2.c"
#include "linkedlist.c"
#include "locks_2.c"

#define NUMCARS 20

/**
* Manages flow of cars
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void *cars (void *arguments) {
    argstruct *args = (argstruct *) arguments;
	while (1) {
        args->approachDir = assignApp();
        args->turnDir = assignTurn();
        printf("Car %d will have approach direction: %d\n", args->threadNum, args->approachDir);
        printf("Car %d will have turn direction: %d\n", args->threadNum, args->turnDir);

		// try to go through
		// trylock loop
	};
}
#pragma clang diagnostic pop


int main() {
	pthread_t threads[NUMCARS]; // queue for all cars

	// struct for args
	argstruct *args = (argstruct *) malloc(NUMCARS*sizeof(argstruct));

	// assign car directions
	for (int i = 0; i < NUMCARS; i++) {
		pthread_create(&threads[i], NULL, &cars, (void *) &args[i]);
	}

	// join threads	
	for (int i = 0; i < NUMCARS; i++) {
	    args[i].threadNum = i;
		pthread_join(threads[i], NULL);
		printf("Called join for thread %d\n", i+1);
	}
	return 0;
}
