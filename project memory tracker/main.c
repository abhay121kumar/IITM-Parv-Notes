#include "memorytracker.h"
#include <stdio.h>

int main() {
    char* a = (char*) mt_malloc(100);
    // int* b = (int*) mt_calloc(10, sizeof(int));
    int* b = (int*) mt_calloc(0, sizeof(int));
    b = (int*) mt_realloc(b, 20 * sizeof(int));
    printf("Allocated memory at %p and %p\n", a, b);
    mt_free(a);
    //for edge case testing
    // mt_free(a);
    // a = (char*) mt_realloc(a, 20 * sizeof(int));
    // printf("Allocated memory at %p and %p\n", a, b);
    // a=NULL;
    // mt_free(a);
    // printf("Allocated memory at %p and %p\n", a, b);
    // mt_summary();   // Print all unfreed blocks
    mt_finalize();  // Free all unfreed memory (if any)
    return 0;
}
