/*
* Project 3 - Part 1 - Pirates and Ninjas
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
#include "helpers.c"
#include "locks.c"

rwlock_t sem; // semaphore

void *individual (void *arguments) {
	argstruct *args = (argstruct *) arguments;
	int willReturn;
	do {
		time_t start_t, end_t;
		sleep((unsigned int) args->arrTime);

		time(&start_t);
		printf("Thread %d isPir? %d try enter cost dept\n", args->threadNum, args->isPirate);
		if (args->isPirate)
		    rwlock_acquire_pirLock(&sem);
        else
            rwlock_acquire_ninLock(&sem);
        printf("Thread %d isPir? %d success enter cost dept\n", args->threadNum, args->isPirate);
		// enter costume department -- attempt to access lock for costume shop

		time(&end_t); // measure waiting time
		double diff_t = difftime(end_t, start_t);
		sleep((unsigned int) args->costmTime);

		// leave costume department
        printf("Thread %d isPir? %d try leave cost dept\n", args->threadNum, args->isPirate);
        if (args->isPirate)
            rwlock_release_pirLock(&sem);
        else
            rwlock_release_ninLock(&sem);
        printf("Thread %d isPir? %d success leave cost dept\n", args->threadNum, args->isPirate);

        if (diff_t <= 30.0)
			args->totalCostT += args->costmTime; // only add time if low waiting time

		willReturn = returnLater();
	} while (willReturn);
	// update stats stored in args

	return 0;
}

int main (int argc, char* argv[]) {
	// srand(time(NULL)); // get different random number each time
	if (argc != 8) { 
		printf("ERROR: Please enter 7 arguments\n");
		exit(-1);
	}

	int numCTeams = atoi(argv[1]); // number of costuming teams
	checkBounds(numCTeams, 2, 4);

	int numPirates = atoi(argv[2]); // number of pirates
	checkBounds(numPirates, 10, 50);

	int numNinjas = atoi(argv[3]); // number of ninjas
	checkBounds(numNinjas, 10, 50);

	int avgCTimeP = atoi(argv[4]); // average costuming time of a pirate
	normalDist(avgCTimeP);

	int avgCTimeN = atoi(argv[5]); // average costuming time of a ninja
	int avgATimeP = atoi(argv[6]); // average arrival time of a pirate
	int avgATimeN = atoi(argv[7]); // average arrival time of a ninja

	const int total = numPirates + numNinjas; // total number of pirates and ninjas
	pthread_t threads[total]; // one queue for both pirates and ninjas

	// ------ init semaphores
    rwlock_init(&sem, (unsigned int) numCTeams);


    // struct for args
	argstruct *args = (argstruct *) malloc(total*sizeof(argstruct));

	// create threads
	for (int i = 0; i < total; i++) {
	    int isPirate = i < numPirates ? 1 : 0;
	    args[i].isPirate = isPirate;
	    args[i].arrTime = isPirate ? normalDist(avgATimeP) : normalDist(avgATimeN);
	    args[i].costmTime = isPirate ? normalDist(avgCTimeP) : normalDist(avgCTimeN);
	    args[i].threadNum = i;
		pthread_create(&threads[i], NULL, &individual, (void *) &args[i]);
		printf("Thread %d will be isPirate%d\n", i, isPirate);
	}

	for (int i = 0; i < total; i++) {
		pthread_join(threads[i], NULL);
		printf("Called join for thread %d\n", i+1);
	}

	// print final stats

	return 0;
}
