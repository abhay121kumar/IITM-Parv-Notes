#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stddef.h>  // for size_t

// Initializes the memory pool. Call before using pool_allocate.
void pool_init(void);

// Allocates a block of memory from the pool.
void* pool_allocate(size_t size);

// Frees a previously allocated block.
void pool_free(void* ptr);

#endif // MEMORY_POOL_H
