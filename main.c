#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>

int M,N;
int M2,N2;
int matrixA[1000][1000];
int matrixB[1000][1000];
int answer1[1000][1000];
int answer2[1000][1000];
struct rowColoumn{
    int row;
    int coloumn;
};
void *multiplyRows(void *rowIndex)
{
    int ri = rowIndex;
    for(int j = 0 ; j < N2 ; j++ ){
        int sum = 0;
        for(int i = 0 ; i < M2 ; i++){
           sum += matrixA[ri][i]*matrixB[i][j];
        }
        answer1[ri][j] = sum;
    }
    pthread_exit(NULL);
}
void * multiplyElements(void *rowColoumn){
    struct rowColoumn *data = (struct rowColoumn*) rowColoumn;
    int r = data->row;
    int c = data->coloumn;
    //printf("%d %d",r,c);
    int sum = 0;
    for(int i = 0 ; i < N; i++){
        sum+=matrixA[r][i]*matrixB[i][c];
    }
    answer2[r][c] = sum;
    pthread_exit(NULL);
}
void readSize(char * line , int *M,int *N){
    char *p = line;
    //printf("line %s",&line);
    int c=0;
    while (*p) { // While there are more characters to process...
        if ( isdigit(*p) || ( (*p=='-'||*p=='+') && isdigit(*(p+1)) )) {
            long val = strtol(p, &p, 10); // Read number
            //printf("%ld\n", val); // and print it.
            if(c==0){ *M = val; }
            else if ( c==1) { *N =val; }
            c++;
        }
        else { p++; }
    }
}

void readFile (FILE* fp,int matrixNo){
    if (fp==NULL)
    {
        printf("no such file.");
        return;
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    //Reading Sizes.
    if(((read = getline(&line, &len, fp)) != -1) ){
        if(matrixNo == 0){
            readSize(line,&M,&N);
        }
        else{
            readSize(line,&M2,&N2);
        }
    }
    //int matrixA[M][N];
    printf("M is %d N is %d \n",M,N);
    //Reading Elements
    int i=0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char *p = line;
        int j=0;
        while (*p) { // While there are more characters to process...
            if ( isdigit(*p) || ( (*p=='-'||*p=='+') && isdigit(*(p+1)) )) {
                long val = strtol(p, &p, 10); // Read number
                //printf("%ld  ", val); // and print it.
                if(matrixNo == 0){
                    matrixA[i][j]=val;
                    //printf("(%d,%d)%ld  ", i,j,matrixA[i][j]);
                }
                else{
                    matrixB[i][j]=val;
                    // printf("(%d,%d)%ld  ", i,j,matrixB[i][j]);
                }
                j++;
            }
            else {p++;}
        }
        i++;
        printf("\n");
    }
}
int main(int argc, char* argv []) {

    //Read File A.
    FILE* fp = fopen(argv[1],"r");
    if(fp == NULL){
        FILE* fp = fopen("a.txt","r");
        readFile(fp,0);
    }else{
        readFile(fp,0);
    }
    //Read File B.
    FILE* fp2 = fopen(argv[2],"r");
    if(fp2 == NULL){
        FILE* fp2 = fopen("b.txt","r");
        readFile(fp2,1);
    }
    else{
        readFile(fp2,1);
    }
    //Print Matrix A
    printf("%d %d\n",M,N);
    for(int l = 0 ; l < M ; l++){
        for(int k = 0 ; k < N ;k++){
            printf("(%d,%d)%d  ",l,k,matrixA[l][k]);
        }
        printf("\n");
    }

    //Print Matrix B
    printf("%d %d\n",M2,N2);
    for(int l = 0 ; l < M2 ; l++){
        for(int k = 0 ; k < N2 ;k++){
            printf("(%d,%d)%d  ",l,k,matrixB[l][k]);
        }
        printf("\n");
    }

    //Multiplication!

    //First Method Threads do row multiplication.
    //int answer[M][N2];
    struct timeval stop, start;
    gettimeofday(&start, NULL); //start checking time
    pthread_t tid[M];
    for(int i = 0 ; i < M ; i++){
        pthread_create(&tid[i], NULL, multiplyRows, (void *)i);
    }
    for(int i = 0 ; i < M ; i++){
        pthread_join(tid[i], NULL);
    }
    printf("Answer Dimensions %d %d\n",M,N2);
    for(int l = 0 ; l < M ; l++){
        for(int k = 0 ; k < N2 ;k++){
            printf("(%d,%d)%d  ",l,k,answer1[l][k]);
        }
        printf("\n");
    }
    gettimeofday(&stop, NULL); //end checking time
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
    printf("Number of threads = %d\n",M);

    //Second Method - A thread computes each element in the output C matrix.
    //Creating Threads
    struct timeval stop2, start2;
    gettimeofday(&start2, NULL); //start checking time

    pthread_t tid2[M*N2];
    int c = 0;
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N2 ; j++){
            struct rowColoumn *x = malloc(sizeof(struct rowColoumn));;
            x->row=i; x->coloumn=j;
            pthread_create(&tid2[c], NULL, multiplyElements, (void *)x);
            c++;
        }
    }
     //Joining Threads
    for(int i = 0 ; i < M*N2 ; i++){
        pthread_join(tid2[i], NULL);
    }
    gettimeofday(&stop2, NULL); //end checking time
    printf("Seconds taken %lu\n", stop2.tv_sec - start2.tv_sec);
    printf("Microseconds taken: %lu\n", stop2.tv_usec - start2.tv_usec);
    printf("Number of threads = %d\n",M*N2);
    printf("Answer Dimensions %d %d\n",M,N2);
    for(int l = 0 ; l < M ; l++){
        for(int k = 0 ; k < N2 ;k++){
            printf("(%d,%d)%d  ",l,k,answer2[l][k]);
        }
        printf("\n");
    }
    return 0;
}
