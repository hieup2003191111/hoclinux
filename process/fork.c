#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    pid_t pid;
    int count = 0;
    //goi fork
    pid = fork();
    if(pid < 0){
        perror("loi fork");
        return 1;
    } else if(pid ==0){
        printf("process con bd \n");
        printf("pid cua tien trinh con: %d\n", getpid());
        printf("pid cua tien trinh cha: %d\n", getppid());
        count = 50; 
        printf("Gia tri bien sau khi thay doi trong con: %d\n", count);

    } else {
        printf("process cha bd\n");
        printf("PID cua tien trinh cha: %d\n", getpid());
        printf("PID cua tien trinh con vua tao: %d\n", pid);
        wait(NULL);
        printf("process con ket thuc \n");
        printf("gia tri bien trong process cha la %d",count);
    }
    return 0;
}