#include <stdio.h>
#include <unistd.h>
int main(){
    int pid;
    int x = 5;
    pid=fork();
    if(pid ==0){
        x=x+5;
        printf("i am chilren \n");
        printf("address 's chil = %p \n value 's chill = %d \n",&x,x);
    }
    else{
        x=x+10;
        printf("i am dad \n");
        printf("address 's dad = %p \n value 's dad = %d  \n " ,&x,x);
    }
    return 0;


}