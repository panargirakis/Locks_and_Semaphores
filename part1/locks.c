//
// Created by panos and amanda on 2/12/19.
//

#include <semaphore.h>
#include <pthread.h>

typedef struct _rwlock_t {
    sem_t lockPir;
    sem_t lockNin;
    sem_t lockTeams;
    int numPirates;
    int numNinjas;
} rwlock_t;

void rwlock_init(rwlock_t *rw, unsigned int numTeams) {
    rw->numNinjas = 0;
    rw->numPirates = 0;
    sem_init(&rw->lockNin, 0, 1);
    sem_init(&rw->lockPir, 0, 1);
    sem_init(&rw->lockTeams, 0, numTeams);
}

void rwlock_acquire_pirLock(rwlock_t *rw) {
    sem_wait(&rw->lockPir); // try to get piratelock
    rw->numPirates++; // increment num of pirates
    if (rw->numPirates == 1) { // if only one person
        sem_wait(&rw->lockNin); // acquire ninjalock
    }
    sem_post(&rw->lockPir); // release lock
    sem_wait(&rw->lockTeams);
}

void rwlock_release_pirLock(rwlock_t *rw) {
    printf("rel. pirlock: trying to get pirlock\n");
    sem_wait(&rw->lockPir); // get piratelock
    printf("rel. pirlock: success get pirlock\n");
    rw->numPirates--; // decrement pirates
    if (rw->numPirates == 0) { // if last one
        sem_post(&rw->lockNin); // release ninjlock
    }
    sem_post(&rw->lockTeams);
    sem_post(&rw->lockPir); // release lock
}

void rwlock_acquire_ninLock(rwlock_t *rw) {
    sem_wait(&rw->lockNin);
    rw->numNinjas++;
    if (rw->numNinjas == 1)
        sem_wait(&rw->lockPir);
    sem_post(&rw->lockNin);
    sem_wait(&rw->lockTeams);
}

void rwlock_release_ninLock(rwlock_t *rw) {
    sem_post(&rw->lockNin);
    rw->numNinjas--;
    if (rw->numNinjas == 0)
        sem_post(&rw->lockPir);
    sem_post(&rw->lockTeams);
    sem_post(&rw->lockNin);
}

//void requestLock(rwlock_t *rw, int isPirate) {
//    if (isPirate == rw->isPirate) {
//        rwlock_acquire_readlock(rw, isPirate);
//    } else {
//        rwlock_acquire_writelock(rw);
//    }
//}
