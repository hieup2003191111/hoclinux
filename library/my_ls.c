#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[]){
    int hint=0;
    int all=0;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-l")==0){
            all=1;
        }
        if(strcmp(argv[i],"-a")==0){
            hint=1;
        }
        if(strcmp(argv[i],"-la")==0){
            all=1;
            hint=1;
        }
    }
    if(all&&hint){
        printf("property\n");
        printf("hint\n");    }
    else if(all==1){
        printf("property\n");
    }
    else if(hint==1){
        printf("hint\n");
    }
    return 0;
}
