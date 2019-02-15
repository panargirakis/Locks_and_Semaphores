//
// Created by panos and amanda on 2/11/19.
//

#define SIZE 10

typedef struct argstruct {
    int isPirate;
    int arrTime;
    int costmTime;
    int goldOwed;
    int threadNum;
    int numVisits;
    double waitTVisits[SIZE];
    int costmTVisits[SIZE];
    int teamUsed[SIZE];
} argstruct;

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
//    printf("avgTime: %d\n", avgTime);
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

    if (num >= 0 && num <= 25) {
        return 1;
    }
    else {
        return 0;
    }
}


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

/**
* Prints usage statistics for proper billing for each pirate or ninja
* @param args Pointer to the args struct of a single thread
*/
void billingStats (argstruct *args) {
    printf("\n%s with ID: %d\n", args->isPirate ? "Pirate" : "Ninja", args->threadNum);
	printf("Number of Visits: %d\n", args->numVisits);
	printf("Costuming Time of Each Visit:  ");
    for (int i = 0; i < args->numVisits; i++) {
        printf("Visit %d: %d min    ", i, args->costmTVisits[i]);
    }
    printf("\n");
	printf("Wait Times of Each Visit:  ");
    for (int i = 0; i < args->numVisits; i++) {
        printf("Visit %d: %.0f min    ", i, args->waitTVisits[i]);
    }
    printf("\n");
	printf("Total Gold: %d\n", args->goldOwed); // total gold owed to dept
}


/**
* Prints expense profits 
* @param numCTeams The number of costuming teams
* @param totalTime The total amount of time inside costuming department
*/
//void profitStats (int numCTeams, int totalTime) {
//	int teamCost = 5 * numCTeams;
//	printf("Costuming teams cost per day: %d\n", teamCost);
//
//	// amount of time that each team was busy
//	// amount of time each team was free
//
//	int avgQLen = (pirates + ninjas) / totalTime;  // average queue length
//	printf("Average Queue Length: %d\n", avgQLen);
//
//	int goldAmt; // gross revenue (amount of gold)
//	printf("Gross Revenue: %d\n", goldAmt);
//	int goldPerVis = goldAmt/numVisits;
//	printf("Gold-Per-Visit: %d\n", goldPerVis);
//
//	int totalProfit = goldAmt - teamCost;
//	printf("Total Profit: %d\n", totalProfit);
//}




