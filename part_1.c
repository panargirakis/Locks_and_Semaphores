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


sem_t sem[];

void checkBounds (int val, int lower, int upper) {
	if (!(val >= lower && val <= upper)) {
		printf("ERROR: Value not in bounds\n");
		exit(-1);
	}
}


typedef struct pirNja { // pirates and ninjas
	pthread_t thread_id;
	int isPirate; // 1 is pirate, 0 is ninja 
} pirNja;


void *pirate() {

}

void *ninja () {

}

void test () {
	while (1) {
		//sem_wait();
		/* critical section */
		//sem_post();
	}
}


int main (int argc, char* argv[]) {
	if (argc != 8) { 
		printf("ERROR: Please enter 8 arguments\n");
		exit(-1);
	}

	int numCTeams = atoi(argv[1]);
	checkBounds(numCTeams, 2, 4);

	int numPirates = atoi(argv[2]);
	checkBounds(numPirates, 10, 50);

	int numNinjas = atoi(argv[3]);
	checkBounds(numNinjas, 10, 50);

	int avgCTimeP = atoi(argv[4]);
	int avgCTimeN = atoi(argv[5]);
	int avgATimeP = atoi(argv[6]);
	int avgATimeN = atoi(argv[7]);

	const int total = numPirates + numNinjas; // total number of pirates and ninjas
	pirNja array[total]; // one whole queue for both pirates and ninjas

	// fill array
	for (int i = 0; i < numPirates; i++) {
		pthread_create(&array[i].thread_id, NULL, pirate, NULL);
		array[i].isPirate = 1;
		printf("%d\n", i);
	}
	for (int i = numPirates; i < total; i++) {
		pthread_create(&array[i].thread_id, NULL, ninja, NULL);
		array[i].isPirate = 0;
		printf("%d\n", i);
	}

	return 0;
}
