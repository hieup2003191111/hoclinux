#include <stdio.h>
#include <unistd.h>
#include<sched.h>
#include <sys/types.h>
#include<sys/resource.h>
#include<sys/wait.h>
struct sched_param param;
void work(char *name){
    volatile long long i;
    for(i=0;i<=10000000000;i++);
    printf("process %s end\n",name);
}
int main(){
    if(fork()==0){
        param.sched_priority=1;
        sched_setscheduler(0,SCHED_FIFO,&param);
        printf("process one start\n");
        work("one");
        return 0;
    }
    if(fork()==0){
        param.sched_priority=99;
        sched_setscheduler(0,SCHED_FIFO,&param);
        printf("process two start\n");
        work("two");
        return 0;
    }
    wait(NULL);
    wait(NULL);
    return 0;

}