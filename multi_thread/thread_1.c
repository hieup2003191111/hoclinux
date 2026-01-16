#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void *count();
void *count(){
    for(int i=1;i<=5;i++){
        printf("%d",i);
        sleep(1);
    }
    return NULL;
}
int main(){
    pthread_t thread;
    pthread_create(&thread,NULL,count,NULL);
    pthread_join(thread,NULL);
    printf("end thread \n");

}