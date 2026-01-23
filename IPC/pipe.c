#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
int piped[2];
char msg[] = "hello,i am hieu\n";
char buf[50];
int main(){
    pipe(piped);
    int p=fork();
    if(p>0){
        printf("parent process \n");
        close(piped[0]);
        write(piped[1],msg,strlen(msg)+1);
        close(piped[1]);
        wait(NULL);
    }
    else{
        printf("child process \n");
        close(piped[1]);
        read(piped[0],buf,sizeof(buf));
        printf("%s",buf);
        close(piped[0]);

    }
    return 0;
}