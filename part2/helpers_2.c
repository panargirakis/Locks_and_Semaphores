/**
* Assigns the given car a direction to approach from
* @return an int that represents the direction, either NW, NE, SW, or SE
*/
int assignApp () {
	int range, min;
	range = 99;
	min = 0;
	int num = rand() % range + min; // num between 0 and 99
	
	if (num >= 0 && num < 24) {
		return 1; // NW
	}
	else if (num >= 24 && num < 50) {
		return 2; // NE
	}
	else if (num >= 50 && num < 75) {
		return 3; // SW
	}
	else {
		return 4; // SE
	}
}


/**
* Assigns the given car a random direction to turn
* @return an int that represents left, right, or straight
*/
int assignTurn() {
	int range, min;
	range = 89;
	min = 0;
	int num = rand() % range + min; // num between 0 and 89

	if (num >= 0 && num < 29) {
		return 1; // left
	}
	else if (num >= 29 && num < 59) {
		return 2; // right
	}
	else {
		return 3; // straight
	}					
}
