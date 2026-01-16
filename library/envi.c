#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
    char *user = getenv("USER");
    char *home = getenv("HOME");
    char cwd[1024];
    if(user) printf("user: %s \n",user);
    if(home) printf("home: %s \n",home);
    if(getcwd(cwd,sizeof(cwd))!=NULL){
        printf("directory : %s \n",cwd);
    }
    return 0;

}