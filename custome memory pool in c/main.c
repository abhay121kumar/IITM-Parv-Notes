#include "memory_pool.h"
#include <stdio.h>

int main() {
    pool_init();

    void* ptr1 = pool_allocate(256);
    void* ptr2 = pool_allocate(128);
    pool_free(ptr1);
    void* ptr3 = pool_allocate(512);

    return 0;
}
