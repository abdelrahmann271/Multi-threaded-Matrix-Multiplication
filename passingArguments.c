/*
//
// Created by nour on 11/13/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

 struct thread_data{
int thread_id;
int sum;
char *message;
};

void * print_hello_world(void* threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    int tid = my_data->thread_id;
    int sum = my_data->sum;
    char * msg = my_data->message;
//print identification of thread and exit
    printf("Thread %d out of %d: %s \n",tid,sum,msg);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        struct thread_data *tdata = malloc(sizeof(struct thread_data));
        tdata->thread_id=t;
        tdata->sum=(int)NUM_THREADS;
        tdata->message="Hello World";
        rc = pthread_create(&threads[t], NULL, print_hello_world, (void *) tdata);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    return 0;
}*/
