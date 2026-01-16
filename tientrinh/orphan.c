#include <stdio.h>
#include <unistd.h>
int main(){
    int pid;
    pid = fork();
    if(pid < 0){
        printf("error fork \n");
        return 0;
    }
    else{
        if(pid == 0){
            printf("i am chilren \n,myChil_pid =  %d \n",getppid());
            sleep(5);
            printf("i am chilren \n,myChil_newpid =  %d \n",getppid());

        }
        else 
            printf("i am dad \n,myDad_pid =  %d \n",getpid());
    }
    return 0;
}