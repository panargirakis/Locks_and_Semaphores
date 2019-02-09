//
// Created by panos on 2/9/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

void checkBounds (int val, int lower, int upper) {
	if (!(val >= lower && val <= upper)) {
		printf("ERROR: Value not in bounds");
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



int main (int argc, char* argv[]) {
	if (argc != 8) { 
		printf("ERROR: Please enter 8 arguments\n");
		exit(-1);
	}

	int numCTeams = atoi(argv[1]);
	checkBounds(numCTeams, 2, 4);

	int numPirates = atoi(argv[2]);
	checkBounds(numCTeams, 10, 50);

	int numNinjas = atoi(argv[3]);
	checkBounds(numCTeams, 10, 50);

	int avgCTimeP = atoi(argv[4]);
	int avgCTimeN = atoi(argv[5]);
	int avgATimeP = atoi(argv[6]);
	int avgATimeN = atoi(argv[7]);

	const int total = numPirates + numNinjas; // total number of pirates and ninjas
	pirNja array[total];
	for (int i = 0; i < numPirates; i++) {
		pthread_create(&array[i].thread_id, NULL, pirate, NULL);
		array[i].isPirate = 1;
	}
	for (int i = numPirates; i < total; i++) {
		pthread_create(&array[i].thread_id, NULL, ninja, NULL);
		array[i].isPirate = 0;
	}

	return 0;
}
