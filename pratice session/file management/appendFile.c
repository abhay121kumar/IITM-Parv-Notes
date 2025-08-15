#include<stdio.h>

int main(){
    FILE *fp = fopen("feedback.txt","a");
    if(fp==NULL){
        printf("error in opening in file\n");
        return 1;
    }
//     But fputs() expects the string first, then the file pointer:

// int fputs(const char *str, FILE *stream);
    // fputs(fp,"new line added using a mode\n"); // that is wrong using fputs
    fputs("new line added using a mode\n", fp); // correct usage of fputs
    fclose(fp);
    return 0;
}