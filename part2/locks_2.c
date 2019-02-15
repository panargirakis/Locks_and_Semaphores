#include <pthread.h>


pthread_mutex_t locks[APPRMAX] = {PTHREAD_MUTEX_INITIALIZER}; // initializes lock
pthread_cond_t cond[APPRMAX] = PTHREAD_COND_INITIALIZER; // initilize condition


/**
*/
void wait () {
//	Pthread_mutex_lock(&locks);
//	/*critical section (intersection)*/
//	while (ready == 0) {
//		Pthread_cond_wait(&cond, &lock);
//	}
//	Pthread_mutex_unlock(&lock);
}

/**
*
*/
void signal () {
//	Pthread_mutex_lock(&lock);
//	ready = 1;
//	Pthread_cond_signal(&cond);
//	Pthread_mutex_unlock(&lock);

}
