#include <pthread.h>


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // initializes lock
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // initilize condition

typedef struct argstruct {
	int approachDir; // NW, NE, SW, or SE
	int turnDir; // left, right, or straight
} argstruct;


/**
*/
void wait () {
	Pthread_mutex_lock(&lock);
	/*critical section (intersection)*/
	while (ready == 0) {
		Pthread_cond_wait(&cond, &lock);
	}
	Pthread_mutex_unlock(&lock);
}

/**
*
*/
void signal () {
	Pthread_mutex_lock(&lock);
	ready = 1;
	Pthread_cond_signal(&cond);
	Pthread_mutex_unlock(&lock);

}
