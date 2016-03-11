#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "queue.h"

__thread int __thread_id;
volatile int main_work = 1;
static pthread_barrier_t init_barr;

int64_t* ops;

#define NB_OPS_SEQUENCE 1


void ALRMhandler (int sig)
{
    main_work = 0;
}

void* my_thread(void* threadid)
{
    int64_t round=0;
    __thread_id = (int)(int64_t)threadid;

    /* wait for the others to initialize */
    int ret = pthread_barrier_wait(&init_barr);
    if (ret != 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD)
    {
        fprintf(stderr, "Waiting on the barrier failed!\n");
        exit(1);
    }

    for (round = 0; main_work; round++)
    {

        if((round+__thread_id)%(NB_OPS_SEQUENCE*2)<NB_OPS_SEQUENCE){
            enqueue(round);
        }
        else{
            dequeue();
        }    
        
    }

    /* store the result */
    ops[__thread_id] = round;

    return NULL;
}




int main(int argc, char *argv[])
{
    int64_t totops=0;
    pthread_t* thr;
    int testtime = 1;
    int n_threads=1;

    if(argc>1){
        n_threads=atoi(argv[1]);
    }

    signal (SIGALRM, ALRMhandler);
    
    printf("########## exp setup: \t %d threads\n",n_threads);


    thr = (pthread_t*) malloc(n_threads * sizeof(pthread_t));
    ops = (int64_t*) malloc(n_threads * sizeof(int64_t));
    memset(ops, 0, n_threads * sizeof(int64_t));

    init_queue();
    
    if(pthread_barrier_init(&init_barr, NULL, n_threads+1))
    {
        printf("Could not create a barrier\n");
        exit(1);
    }

    /* create the threads */
    int i = 0;
    
    for(i=0; i < n_threads; i++){
        if(pthread_create(&thr[i], NULL, &my_thread, (void*)(int64_t)i)){
            printf("Could not create thread %d\n", i);
            exit(1);
        }
    }
    
    /* wait for everyone to initialize, then set the alarm */
    int ret = pthread_barrier_wait(&init_barr);
    if (ret != 0 && ret != PTHREAD_BARRIER_SERIAL_THREAD){
        fprintf(stderr, "Waiting on the barrier failed!\n");
        exit(1);
    }

    alarm (testtime);
    totops = 0;
    for(i = 0; i < n_threads; i++){
        if(pthread_join(thr[i], NULL)){
            fprintf(stderr, "Could not join thread %d\n", i);
            exit(1);
        }        
        printf("[%d]: %lld\n" , i, (long long int)ops[i]);
        
        totops += ops[i];
    }


    printf("throughput: %.2lf Mops\n", (double)(totops/testtime)/1000000.0);

    
    terminate_queue();
    
    return 0;

    
}
