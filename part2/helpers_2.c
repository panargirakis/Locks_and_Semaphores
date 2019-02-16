
typedef enum _Dir {L = 0, R, STR, DIRMAX} Dir;
typedef enum _Cubes {NW = 0, NE, SW, SE, CUBEMAX} Cubes;
typedef enum _Appr {N = 0, SOUTH, W, E, APPRMAX} Appr;

typedef struct argstruct {
	Appr approachDir; // NW, NE, SW, or SE
	Dir turnDir; // left, right, or straight
	int threadNum;
	Cubes cubesNeeded[4];
	int numCNeeded;
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
	if (args->approachDir == N && args->turnDir == L) {
		args->numCNeeded = 3;
		args->cubesNeeded[0] = NW;
		args->cubesNeeded[1] = SW;
		args->cubesNeeded[2] = SE;
	} else if (args->approachDir == N && args->turnDir == R) {
		args->numCNeeded = 1;
		args->cubesNeeded[0] = NW;
	} else if (args->approachDir == N && args->turnDir == STR) {
		args->numCNeeded = 2;
		args->cubesNeeded[0] = NW;
		args->cubesNeeded[1] = SW;
	} else if (args->approachDir == W && args->turnDir == L) { // W
		args->numCNeeded = 3;
        args->cubesNeeded[0] = NE;
        args->cubesNeeded[1] = SW;
        args->cubesNeeded[2] = SE;
	} else if (args->approachDir == W && args->turnDir == R) {
		args->numCNeeded = 1;
		args->cubesNeeded[0] = SW;
	} else if (args->approachDir == W && args->turnDir == STR) {
		args->numCNeeded = 2;
        args->cubesNeeded[0] = SW;
        args->cubesNeeded[1] = SE;
	} else if (args->approachDir == SOUTH && args->turnDir == L) { // S
		args->numCNeeded = 3;
        args->cubesNeeded[0] = NW;
        args->cubesNeeded[1] = NE;
        args->cubesNeeded[2] = SE;
	} else if (args->approachDir == SOUTH && args->turnDir == R) {
		args->numCNeeded = 1;
		args->cubesNeeded[0] = SE;
	} else if (args->approachDir == SOUTH && args->turnDir == STR) {
		args->numCNeeded = 2;
        args->cubesNeeded[0] = NE;
        args->cubesNeeded[1] = SE;
	} else if (args->approachDir == E && args->turnDir == L) { // E
		args->numCNeeded = 3;
        args->cubesNeeded[0] = NW;
        args->cubesNeeded[1] = NE;
        args->cubesNeeded[2] = SW;
	} else if (args->approachDir == E && args->turnDir == R) {
		args->numCNeeded = 1;
		args->cubesNeeded[0] = NE;
	} else if (args->approachDir == E && args->turnDir == STR) {
		args->numCNeeded = 2;
        args->cubesNeeded[0] = NW;
        args->cubesNeeded[1] = NE;
	}
}
