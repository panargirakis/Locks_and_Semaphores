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
	args->numVisits = 0;
	do {
		time_t start_t, end_t;
		int arrTime = normalDist(args->arrTime);

		// BE OUT AND ABOUT
		sleep((unsigned int) arrTime);

		time(&start_t);
		int team;
		if (args->isPirate)
		    team = rwlock_acquire_pirLock(&sem);
        else
            team = rwlock_acquire_ninLock(&sem);
        printf("%s id:%d success enter cost dept. Using team %d\n",
        		args->isPirate ? "Pirate" : "Ninja", args->threadNum, team);
		// enter costume department -- attempt to access lock for costume shop

		time(&end_t); // measure waiting time
		double wait_t = difftime(end_t, start_t);
		int costmT = normalDist(args->costmTime);

		// DRESS UP
		sleep((unsigned int) costmT);

		// leave costume department
        if (args->isPirate)
            rwlock_release_pirLock(&sem);
        else
            rwlock_release_ninLock(&sem);

		printf("%s id:%d left cost dept. Used team %d\n",
			   args->isPirate ? "Pirate" : "Ninja", args->threadNum, team);

        if (wait_t > 30.0) { // if wait time more than 30 min
//			printf("Waited for more than 30 min [%.0fmin]\n", wait_t);
            ;
		} else {
			args->goldOwed += costmT; // only add time if low waiting time
        }

        // keep track of stats
        args->waitTVisits[args->numVisits] = wait_t;
        args->costmTVisits[args->numVisits] = costmT;
        args->teamUsed[args->numVisits] = team;
		args->numVisits++;

		willReturn = returnLater();
	} while (willReturn);
	return 0;
}

int main (int argc, char* argv[]) {
	// srand(time(NULL)); // get different random number each time
	printf("\n~~~~~ Welcome to Pirates vs Ninjas - Peace Edit ~~~~~~\n");
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

	// start the clock
	time_t start_t, end_t;
	time(&start_t); // measure waiting time

	// create threads
	for (int i = 0; i < total; i++) {
	    int isPirate = i < numPirates ? 1 : 0;
	    args[i].isPirate = isPirate;
	    args[i].arrTime = isPirate ? avgATimeP : avgATimeN;
	    args[i].costmTime = isPirate ? avgCTimeP : avgCTimeN;
	    args[i].threadNum = i;
		pthread_create(&threads[i], NULL, &individual, (void *) &args[i]);
//		printf("Thread %d will be isPirate %d\n", i, isPirate);
	}

	for (int i = 0; i < total; i++) {
		pthread_join(threads[i], NULL);
//		printf("Called join for thread %d\n", i+1);
	}

	time(&end_t); // measure waiting time
	double total_t = difftime(end_t, start_t);

	int usagePerTeam[numCTeams];
	for (int i = 0; i < numCTeams; i++) { // initialize variable-sized array
		usagePerTeam[i] = 0;
	}
	int grossGold = 0;
	int totalVisits = 0;
	int totalWaitT = 0;
	for (int i = 0; i < total; i++) {
		argstruct *currT = &args[i];
		billingStats(currT);
		grossGold += currT->goldOwed;
		totalVisits += currT->numVisits;
		for (int j = 0; j < currT->numVisits; j++) { // for every visit
			usagePerTeam[currT->teamUsed[j]-1] += currT->costmTVisits[j]; // add costuming time to team total
			totalWaitT += currT->waitTVisits[j];
		}
	}

	printf("\nTotal time in day: %.0f minutes\n", total_t);
	for (int i = 0; i < numCTeams; i++) {
		printf("Team %d was busy %.0f%% of the day with %d min of work\n", i+1, usagePerTeam[i]*100.0/total_t,
				usagePerTeam[i]);
	}

	printf("\nGross profit: %d gold\n", grossGold);
	printf("Gold-Per-Visit: %d gold\n", grossGold / totalVisits);

	int expenses = numCTeams * 5;
	printf("Net profit: %d gold\n", grossGold - expenses);

	int avgQLen = 0;
//	printf("Average Queue Length: %d individuals\n", avgQLen);


	// print final stats

	return 0;
}
