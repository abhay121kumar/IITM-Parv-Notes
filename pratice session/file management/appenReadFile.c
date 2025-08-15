#include<stdio.h>

int main(){
    FILE* fp = fopen("feedback.txt","a+");
    if(fp==NULL){
        printf("filed not open\n");
        return 1;
    }
    fputs("new line added using a+ that is append and read\n",fp);
    // Move the file pointer back to the beginning before reading
    rewind(fp);
    char buffer[100];
    while(fgets(buffer,100,fp)){
        printf("%s",buffer);
    }
    fclose(fp);
    return 0;
}