#include <stdio.h>

struct Student {
    char name[20];
    int age;
};

int main() {
    struct Student s1 = {"abhay", 24};

    FILE *fp = fopen("student.dat", "wb");
    fwrite(&s1, sizeof(s1), 1, fp);
    fclose(fp);
    
    return 0;
}
