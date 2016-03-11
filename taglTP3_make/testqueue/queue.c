#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "lock_implementation/lock_interface.h"

int *array_queue;
int array_size;

int head,tail;


static void resize_queue(void)
{
    int i=0;
    
    printf("Resizing the queue: current size is %d (head: %d, tail %d)\n",array_size, head, tail);

    printf("Content of the array: ");
    for(i=0; i<array_size; i++){
        printf("%d ",array_queue[i]);   
    }
    printf("\n\n");
    
    int* new_queue= (int*) malloc(array_size*sizeof(int)*2);

    /* copy old queue into the new one */
    memcpy(new_queue, &array_queue[tail], (array_size - tail) *sizeof(int));
    memcpy(&new_queue[array_size-tail], array_queue, tail*sizeof(int));

    /* free old queue and replace it by the new one */
    free(array_queue);
    array_queue=new_queue;
    
    tail=-1;
    head=array_size;

    array_size=array_size*2;

    
    printf("Resizing the queue: NEW size is %d (head: %d, tail %d)\n",array_size, head, tail);

    printf("Content of the array: ");
    for(i=0; i<array_size; i++){
        printf("%d ",array_queue[i]);   
    }
    printf("\n\n");

    
}

void init_queue(void)
{
    lock_init();
    
    array_size=64;
    array_queue=(int*) malloc(array_size*sizeof(int));

    head=0;
    tail=-1;
}

void terminate_queue(void)
{
    free(array_queue);

    lock_finalize();
}
    
void enqueue(int val)
{
    lock_lock();
    
    if(head == tail){
        resize_queue();
    }

    array_queue[head]=val;
    head=(head+1)%array_size;

    lock_unlock();
}


/* return -1 when the queue is empty*/
int dequeue(void)
{
    int return_value=-1;
    
    lock_lock();
    
    /*test if queue is empty*/
    if((head - tail)%array_size == 1){
        return_value= -1;
    }
    else{
    
        tail=(tail+1)%array_size;
    
        return_value= array_queue[tail];
    }

    lock_unlock();

    return return_value;
}
