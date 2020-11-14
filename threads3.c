//
// Created by nour on 11/13/20.
//

/*
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 10

*/
/*The function initially executed by threads*//*

        //gcc main.c -lpthread
        // ./a.out
void * print_hello_world(void* tid)
{
//print identification of thread and exit
    printf("Thread %ld : Hello World \n",tid);
    pthread_exit(NULL);
}

int main() {
    //The main program that creates 10 threads then exits

    pthread_t threads[NUM_THREADS];
    //declare an array of type pthread_t

    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello_world, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
    //the main should also terminate

    return 0;
}
*/
