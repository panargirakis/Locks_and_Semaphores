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

time_t start_t;

/**
* Manages flow of cars
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void *cars (void *arguments) {
    argstruct *args = (argstruct *) arguments;
	while (1) {
//		sleep((unsigned int) rand() % 4);
        args->approachDir = assignApp();
        args->turnDir = assignTurn();
        getCubesNeeded(args);

        Dir dir = args->approachDir;

//        printf("Car %d req to enter queue from dir %d and turn %d\n",
//        		args->threadNum, args->approachDir, args->turnDir);
        time_t end_t;
		time(&end_t);
        double time_d = difftime(end_t, start_t);
//		printf("Car %d success enter queue at time %.4f\n", args->threadNum, time_d);

		pthread_mutex_lock(&lockQ[dir]);
		push(args, dir);  // push in queue
        while (!checkIfFirst(args)) { // exit loop if you are the first in the list
			pthread_cond_wait(&condQ[dir], &lockQ[dir]);  // wait until you are serviced
		}
		pthread_mutex_unlock(&lockQ[dir]); // unlock queue
        for (int i = 0; i < args->numCNeeded; i++) { // get all cube locks
        	pthread_mutex_lock(&lockCube[args->cubesNeeded[i]]);
        }
		time(&end_t);
        time_d = difftime(end_t, start_t);
        printf("Car %d entered the intersection at time %.4f from dir %d and turn %d\n",
        		args->threadNum, time_d, args->approachDir, args->turnDir);
        sleep((unsigned int) 1); // drive in the intersection

		for (int i = 0; i < args->numCNeeded; i++) { // unlock all cube locks
			pthread_mutex_unlock(&lockCube[args->cubesNeeded[i]]);
		}
		time(&end_t);
		time_d = difftime(end_t, start_t);
		printf("Car %d exited the intersection at time %.4f\n", args->threadNum, time_d);

		pthread_mutex_lock(&lockQ[dir]);  // get queue lock
		pop(args, dir);
		pthread_cond_signal(&condQ[dir]);
		pthread_mutex_unlock(&lockQ[dir]); // unlock queue


	};
}
#pragma clang diagnostic pop


int main() {
	pthread_t threads[NUMCARS]; // queue for all cars

	// struct for args
	argstruct *args = (argstruct *) malloc(NUMCARS*sizeof(argstruct));

	time(&start_t);

	// assign car directions
	for (int i = 0; i < NUMCARS; i++) {
		args[i].threadNum = i;
		pthread_create(&threads[i], NULL, &cars, (void *) &args[i]);
	}

	// join threads	
	for (int i = 0; i < NUMCARS; i++) {
		pthread_join(threads[i], NULL);
		printf("Called join for thread %d\n", i+1);
	}
	return 0;
}
