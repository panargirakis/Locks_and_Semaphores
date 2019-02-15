
typedef enum _Dir {L = 0, R, S, DIRMAX} Dir;
typedef enum _Appr {NW = 0, NE, SW, SE, APPRMAX} Appr;

typedef struct argstruct {
	Dir approachDir; // NW, NE, SW, or SE
	Appr turnDir; // left, right, or straight
	int threadNum;
} argstruct;


/**
* Assigns the given car a direction to approach from
* @return an int that represents the direction, either NW, NE, SW, or SE
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
