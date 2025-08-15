#include<stdio.h>

int main(){
    FILE* fp = fopen("feedback.txt","r+");
    char buffer[100];
    if(fp==NULL){
        printf("file not found\n");
        return 1;
    }
    while(fgets(buffer,100,fp)){
        printf("%s",buffer);
    }
    fputs("new line added using r+ that is read + right\n",fp);
    fclose(fp);
    return 0;
}