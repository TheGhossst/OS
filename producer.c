#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
//#include <sys/mman.h>
#include <sys/stat.h>

#define max 10

struct data{
    int buffer[max];
    sem_t empty,full,mutex;
    int index;
}*d;

int main(){
    int shared_fd=shm_open("/shared2",O_RDWR | O_CREAT,0777);
    ftruncate(shared_fd,sizeof(struct data));
   // d=mmap(NULL,sizeof(struct data),PROT_READ | PROT_WRITE,MAP_SHARED,shared_fd,0);
    int x,item=0;
    sem_init(&(d->full),1,0);
    sem_init(&(d->empty),1,max);
    sem_init(&(d->mutex),1,1);
    while(1){
        sem_getvalue(&(d->full),&x);
        if(x == max){
            printf("\nProducer cant produce");
            sleep(1);
        }
        else{
            sem_wait(&(d->empty));
            sem_wait(&(d->mutex));
            item++;
            d->buffer[d->index]=item;
            d->index++;
            printf("\nProducer produced %d",item);
            sleep(1);
            sem_post(&(d->full));
            sem_post(&(d->mutex));
        }
    }
    return 0;
}