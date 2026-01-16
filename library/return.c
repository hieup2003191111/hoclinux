#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
    int fd;
    fd = open("hehe.txt",O_RDONLY);
    if(fd<0){
        printf("error open file \n");
        close(fd);
        return -1;
    }
    else {
        printf("success open file \n");
        close(fd);
        return 0;
    }

}