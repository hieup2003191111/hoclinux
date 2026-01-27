#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/resource.h>
#include<sys/wait.h>
void work(char *name){
    long long i;
    for(i=0;i<=10000000000;i++);
    printf("process %s end\n",name);
}
int main(){
    if(fork()==0){
        setpriority(PRIO_PROCESS,0,10);
        printf("process one start\n");
        work("one");
        return 0;
    }
    if(fork()==0){
        setpriority(PRIO_PROCESS,0,-5);
        printf("process two start \n");
        work("two");
        return 0;
    }
    wait(NULL);
    wait(NULL);
    return 0;

}