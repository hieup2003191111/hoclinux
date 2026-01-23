#define _DEFAULT_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<string.h>
int main(){
    const char *name = "/my_shm";
    const int size = 4095;
    int mem = shm_open(name,O_CREAT|O_RDWR,0666);
    ftruncate(mem,size);
    void *ptr = mmap(0,size,PROT_WRITE,MAP_SHARED,mem,0);
    if(fork()>0){
        printf("this is parent process\n");
        char *msg= "hello shm\n";
        sprintf(ptr,"%s\n",msg);
        wait(NULL);
        shm_unlink(name);


    }
    else{
        printf("this is child process \n");
        sleep(3);
        printf("this is content of parent process: %s \n",(char *)ptr);
    }
    return 0;
}
