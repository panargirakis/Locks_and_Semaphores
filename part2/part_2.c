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
#include "locks_2.c"
#include "helpers_2.c"


/**
* Manages flow of cars
*/
void *cars (void *arguments) {
}


int main() {
	const int numCars = 20;
	pthread_t threads[numCars]; // queue for all cars

	// struct for args
	argstruct *args = (argstruct *) malloc(numCars*sizeof(argstruct));

	// assign car directions
	for (int i = 0; i < numCars; i++) {
		args[i].approachDir = assignApp();
		args[i].turnDir = assignTurn();
		pthread_create(&threads[i], NULL, &cars, (void *) &args[i]);
		printf("Car %d will have approach direction: %d\n", i, args[i].approachDir);
		printf("Car %d will have turn direction: %d\n", i, args[i].turnDir);
		printf("\n");	
	}

	// join threads	
	for (int i = 0; i < numCars; i++) {
		pthread_join(threads[i], NULL);
		printf("Called join for thread %d\n", i+1);
	}
	return 0;
}
