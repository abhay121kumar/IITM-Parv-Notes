#include<stdio.h>
// What "w+" Does:

// W = Write: It creates the file if it doesn’t exist.

// The + adds read capability.

// ✅ Good for: overwriting a file with new content while also being able to read it.

// ❌ But: it clears the entire file the moment it opens — even before you write anything.

// So:

// Your old content in feedback.txt was erased the moment fopen("feedback.txt", "w+") 
// executed — before your program even wrote "new line added using w+...".
int main(){
    FILE* fp = fopen("feedback.txt","w+");
    if(fp==NULL){
        printf("filed not open\n");
        return 1;
    }
    fputs("new line added using w+ that is write and read\n",fp);
    // Move the file pointer back to the beginning before reading
    rewind(fp);
    char buffer[100];
    while(fgets(buffer,100,fp)){
        printf("%s",buffer);
    }
    fclose(fp);
    return 0;
}