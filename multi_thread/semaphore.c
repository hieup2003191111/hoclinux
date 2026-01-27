#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
sem_t lock;
void *work(void *arg){
    int id = *(int *)(arg);
    printf("thread %d wait \n",id);
    sem_wait(&lock);
    printf("thread %d start \n",id);
    sleep(2);
    printf("thread %d leave \n",id);
    sem_post(&lock);
    return NULL;
}
int main(){
    sem_init(&lock,0,3);
    int id[11];
    pthread_t T[11];
    sem_post(&lock);
    printf("tra 1 lock du khong giu lock \n");
    for(int i=1;i<=10;i++){     
        id[i]=i;  
        pthread_create(&T[i],NULL,work,&id[i]);
    }
    for(int i=1;i<=10;i++){       
        pthread_join(T[i],NULL);
    }
    sem_destroy(&lock);
    return 0;
}