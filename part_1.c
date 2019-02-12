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


typedef struct pirNja { // pirates and ninjas
	pthread_t thread_id;
	int isPirate; // 1 is pirate, 0 is ninja 
} pirNja;


/**
* Checks the bounds by comparing with the user input value
* @param val The user input value
* @param lower Lowest possible bound
* @param upper Highest possible bound
*/
void checkBounds (int val, int lower, int upper) {
	if (!(val >= lower && val <= upper)) {
		printf("ERROR: Value not in bounds\n");
		exit(-1);
	}
}

int returnLater();

sem_t sem[]; // semaphore
void *individual (void *arguments) {
	argstruct *args = (argstruct *) arguments;
	int willReturn;
	do {
		// wait to enter
		// enter costume department
		// sleep (dress)
		// leave costume department
		willReturn = returnLater();
	} while (willReturn);
	// update stats stored in args
	return 0;
}

/**
* Calculates a random number between 0 and 1
* @return retVal a random double
*/
double random_num() {
    double retVal = (double)rand() / (double)RAND_MAX;
	return retVal;
}

/**
* Calculate the normal distribution
* @param avgTime User input value
* @return zInt in seconds
*/
int normalDist (int avgTime) {
	double a, b, z;
	a = random_num();
	b = random_num();
	z = sqrt(-2*log(a)) * cos(2*M_PI*b); // Box-Muller Transform
	z /= 2.0;
	z *= avgTime/3.0;
	printf("avgTime: %d\n", avgTime);
	z += avgTime;
	int zInt = round(z); // rounds double to nearest int val
	zInt = zInt < 0 ? 0 : zInt; // prevents infinity error
	zInt = zInt > avgTime*10 ? avgTime*10 : zInt;
//	printf("a: %f\n", a);
//	printf("b: %f\n", b);
//	printf("z: %f\n", z);
//  printf("z: %d\n", zInt);
	return zInt;
}


/**
* Determines if pirate or ninja will return to costuming dept. later
* @return 1 if they will return, 0 if they will not return
*/
int returnLater() {
	int range, min;
	range = 99;
	min = 0;
	int num = rand() % range + min; // num between 0 and 99
	printf("Num: %d\n", num);
	if (num >= 0 && num <= 25) {
		return 1;
	}
	else {
		return 0;
	}
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
	pirNja array[total]; // one queue for both pirates and ninjas


    // struct for args
	argstruct *args = (argstruct *) malloc(total*sizeof(argstruct));

	// create threads
	for (int i = 0; i < total; i++) {
	    int isPirate = i < numPirates ? 1 : 0;
	    args[i].isPirate = isPirate;
	    args[i].arrival = isPirate ? avgATimeP : avgATimeN;
	    args[i].costumngT = isPirate ? avgCTimeP : avgCTimeN;
	    args[i].threadNum = i;
		pthread_create(&array[i].thread_id, NULL, &individual, (void *) &args[i]);
		printf("Thread %d will be isPirate%d\n", i, isPirate);
	}

	return 0;
}
