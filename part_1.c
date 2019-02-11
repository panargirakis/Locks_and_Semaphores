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


void *individual (void *args) {
	while (1) {
		//sem_wait();
		/* critical section */
		//sem_post();
	}
}

double random_num() {
    double retVal = (double)rand() / (double)RAND_MAX;
	return retVal; // random number between 0 and 1
}

int normalDist (int avgTime) {
	double a, b;
	srand(time(NULL));
	a = random_num();
	b = random_num();
	double z = sqrt(-2*log(a)) * cos(2*M_PI*b);
	z /= 2.0;
	z *= avgTime/3.0;
	printf("avtTime: %d\n", avgTime);
	z += avgTime;
	int zInt = round(z);
	zInt = zInt < 0 ? 0 : zInt;
	zInt = zInt > avgTime*10 ? avgTime*10 : zInt;
//	printf("a: %f\n", a);
//	printf("b: %f\n", b);
//	printf("z: %f\n", z);
//    printf("z: %d\n", zInt);
	return zInt;
}

int main (int argc, char* argv[]) {
	if (argc != 8) { 
		printf("ERROR: Please enter 8 arguments\n");
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
	pirNja array[total]; // one whole queue for both pirates and ninjas

	// fill array
//	for (int i = 0; i < numPirates; i++) {
//		pthread_create(&array[i].thread_id, NULL, pirate, NULL);
//		array[i].isPirate = 1;
//		printf("%d\n", i);
//	}
//	for (int i = numPirates; i < total; i++) {
//		pthread_create(&array[i].thread_id, NULL, ninja, NULL);
//		array[i].isPirate = 0;
//		printf("%d\n", i);
//	}

	return 0;
}
