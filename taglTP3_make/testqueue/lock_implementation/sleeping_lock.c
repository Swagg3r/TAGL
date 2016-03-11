#include <stdio.h>
#include <pthread.h>

#include "lock_interface.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void lock_init(void)
{
}

void lock_finalize(void)
{
    pthread_mutex_destroy(&mutex);
}


void lock_lock(void)
{
    pthread_mutex_lock(&mutex);
}

void lock_unlock(void)
{
    pthread_mutex_unlock(&mutex);
}

