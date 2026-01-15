#include <stdio.h>
#include <unistd.h>
int main(){
    int pid;
    pid=fork();
    if(pid ==0){
        printf("i am chilren \n");
        char *args[]={"ls","-l",NULL};
        execv("/bin/ls",args);
        printf("error");
    }
    else{
        sleep(1);
        printf("i am dad \n");
    }
    return 0;


}