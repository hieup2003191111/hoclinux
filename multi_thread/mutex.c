#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int a=0;
pthread_mutex_t lock;
void *work(){
    //  pthread_mutex_lock(&lock);
     for(int i=1;i<=100000;i++){
        a=++a;
    }
    // pthread_mutex_unlock(&lock);
    return NULL;
}
int main(){
    // pthread_mutex_init(&lock,NULL);
    pthread_t thr1,thr2;
    pthread_create(&thr1,NULL,work,NULL);
    pthread_create(&thr2,NULL,work,NULL);
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    // pthread_mutex_destroy(&lock);
    printf("value a = %d\n",a);
    return 0;
}