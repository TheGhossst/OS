#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
//#include <sys/mman.h>
#include <sys/stat.h>

#define max 10

struct data{
    int buffer[max];
    sem_t empty,full,mutex;
    int index;
}*d;

int main(){
    int shared_fd = shm_open("/shared2",O_CREAT | O_RDWR,0777);
   // d=mmap(NULL,sizeof(struct data),PROT_READ | PROT_WRITE,MAP_SHARED,shared_fd,0);
    int x,item;
    while(1){
        sem_getvalue(&(d->empty),&x);
        if(x == max-1){
            printf("\nConsumer cant consume");
            sleep(1);
        }
        else{
            sem_wait(&(d->full));
            sem_wait(&(d->mutex));
            d->index--;
            item=d->buffer[d->index];
            printf("\nConsumer consumed %d",item);
            sleep(1);
            sem_post(&(d->empty));
            sem_post(&(d->mutex));
        }
    }
    return 0;
}