#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
int readercount=0;
pthread_t reader[10];
pthread_t writer;

sem_t r,w,rw;
void *reade(void * arg){
    int reader_id=*((int*)arg);
    while(1){
        sem_wait(&r);
        readercount++;
        if(readercount == 1)    sem_wait(&rw);
        sem_post(&r);
        sleep(1);
        printf("\nReader %d is reading ",reader_id);
        sleep(1);
        sem_wait(&r);
        readercount--;
        printf("\nReader %d left",reader_id);
        if(readercount ==0) sem_post(&rw);
        sem_post(&r);
        sleep(1);
        
        sleep(1);
    }
    return NULL;
}
void writ(){
    while(1){
        sem_wait(&w);
        sem_wait(&rw);
        printf("\nWriter is writing");
        sleep(1);
        sem_post(&rw);
        sem_post(&w);
        printf("\nWriter left");
        sleep(1);
    }
}
int main(){
    int n,i;
    printf("Enter the number of readers:  ");
    scanf("%d",&n);
    int a[n];
    sem_init(&r,0,1);
    sem_init(&w,0,1);
    sem_init(&rw,0,1);
    for(i=0;i<n;i++)    a[i]=i;
    for(i=0;i<n;i++)    pthread_create(&reader[i],NULL,(void *)reade,&a[i]);
    pthread_create(&writer,NULL,(void*)writ,NULL);
    for(i=0;i<n;i++)    pthread_join(reader[i],NULL);
    pthread_join(writer,NULL);

}
