
typedef enum _Dir {L = 0, R, S, DIRMAX} Dir;
typedef enum _Cubes {NW = 0, NE, SW, SE, CUBEMAX} Cubes;
typedef enum _Appr {N = 0, S, W, E, APPRMAX} Appr;

typedef struct argstruct {
	Appr approachDir; // NW, NE, SW, or SE
	Dir turnDir; // left, right, or straight
	int threadNum;
	Cubes cubesNeeded[4];
	int numCNeeded;
	pthread_cond_t amDone = PTHREAD_COND_INITIALIZER;
} argstruct;


/**
* Assigns the given car a direction to approach from
* @return an int that represents the direction, either N, S, W, or E
*/
Appr assignApp () {
	Appr num = rand() % APPRMAX; // num between 0 and 3
	return num;
}


/**
* Assigns the given car a random direction to turn
* @return an int that represents left, right, or straight
*/
Dir assignTurn() {
	Dir num = rand() % DIRMAX; // num between 0 and 2
	return num;
}

void getCubesNeeded(argstruct *args) {
	int *numCNeeded = &args->numCNeeded;
	Cubes *cubesNeeded = &args->cubesNeeded;
	numCNeeded = 0;
	if (args->approachDir == N && args->turnDir == L) {
		numCNeeded = 3;
		cubesNeeded = {NW, SW, SE, 0};
	} else if (args->approachDir == N && args->turnDir == R) {
		numCNeeded = 1;
		cubesNeeded[0] = NW;
	} else if (args->approachDir == N && args->turnDir == S) {
		numCNeeded = 2;
		cubesNeeded = {NW, SW, 0, 0};
	} else if (args->approachDir == W && args->turnDir == L) { // W
		numCNeeded = 3;
		cubesNeeded = {NE, SW, SE, 0};
	} else if (args->approachDir == W && args->turnDir == R) {
		numCNeeded = 1;
		cubesNeeded[0] = SW;
	} else if (args->approachDir == W && args->turnDir == S) {
		numCNeeded = 2;
		cubesNeeded = {SW, SE, 0, 0};
	} else if (args->approachDir == S && args->turnDir == L) { // S
		numCNeeded = 3;
		cubesNeeded = {NW, NE, SE, 0};
	} else if (args->approachDir == S && args->turnDir == R) {
		numCNeeded = 1;
		cubesNeeded[0] = SE;
	} else if (args->approachDir == S && args->turnDir == S) {
		numCNeeded = 2;
		cubesNeeded = {NE, SE, 0, 0};
	} else if (args->approachDir == E && args->turnDir == L) { // E
		numCNeeded = 3;
		cubesNeeded = {NW, NE, SW, 0};
	} else if (args->approachDir == E && args->turnDir == R) {
		numCNeeded = 1;
		cubesNeeded[0] = NE;
	} else if (args->approachDir == E && args->turnDir == S) {
		numCNeeded = 2;
		cubesNeeded = {NW, NE, 0, 0};
	}
}
