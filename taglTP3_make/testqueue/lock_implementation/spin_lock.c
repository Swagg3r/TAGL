#include <stdio.h>
#include <pthread.h>

#include "lock_interface.h"


volatile int lock=0;

void lock_init(void)
{
}

void lock_finalize(void)
{
}


void lock_lock(void)
{
    while(!__sync_bool_compare_and_swap(&lock,0,1)){;}
    
}

void lock_unlock(void)
{
    lock=0;
}
