#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0){
        printf("error fork \n");
        return 0;
    }
    else{
        if(pid == 0){
            printf("i am chilren \n,myChil_pid =  %d \n",getpid());
        }
        else 
            printf("i am dad \n,myDad_pid =  %d \n",getpid());
    }
    return 0;
}