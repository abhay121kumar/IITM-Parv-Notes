#include "stdio.h"
int main(){
    FILE *fp = fopen("feedback.txt","w");
    if(fp==NULL){
        printf("Error Opening File!\n");
        return 1;
    }
    fprintf(fp, "writing in the file\n pppppppppppp\n kkkkkkkkkk\nkkkkkkkkkk\n");
    fclose(fp);
    printf("feedback saved to file\n");
}