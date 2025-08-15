#include<stdio.h>
struct student{
    char name[20];
    int age;
};
int main(){
    struct student s2; 
    FILE* fp = fopen("student.dat","rb");
    if(fp==NULL){
        return 1;
    }
    fread(&s2,sizeof(s2),1,fp);
    fclose(fp);
    printf("NAme: %s, Age: %d\n",s2.name,s2.age);
    return 0;
}