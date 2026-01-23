#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void handle_sig(int sig){
    printf("\n [SIGNAL] received signal %d \n",sig);
    exit(0);
}
int main(){
    signal(SIGINT,handle_sig);
    printf("enter ctr+c to send signal \n");
    while(1){
        printf("working \n");
        sleep(1);
    }
    return 0;
}