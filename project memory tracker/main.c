#include "memorytracker.h"
#include <stdio.h>

int main() {
    char* a = (char*) mt_malloc(100);
    int* b = (int*) mt_calloc(10, sizeof(int));
    b = (int*) mt_realloc(b, 20 * sizeof(int));
    mt_free(a);

    mt_summary();   // Print all unfreed blocks
    mt_finalize();  // Free all unfreed memory (if any)
    return 0;
}
