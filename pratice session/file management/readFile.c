#include<stdio.h>

int main(){
    char buffer[100];
    FILE *fp = fopen("feedback.txt","r");
    if(fp==NULL){
        printf("File not found\n");
        return 1;
    }
     while (fgets(buffer, 100, fp)) {
        printf("%s", buffer);
    }

    fclose(fp);
    return 0;
}