#include <stdlib.h>
#include <stdbool.h>
#include "bufferpool.h"

buffer_pool_t* create_buffer_pool(int size) {
    buffer_pool_t* pool = malloc(sizeof(buffer_pool_t));
    if (!pool) return NULL;
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->buffers[i].in_use = false;
    }
    return pool;
}

void destroy_buffer_pool(buffer_pool_t* pool) {
    if (pool) free(pool);
}

buffer_t* acquire_buffer(buffer_pool_t* pool) {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (!pool->buffers[i].in_use) {
            pool->buffers[i].in_use = true;
            return &pool->buffers[i];
        }
    }
    return NULL;
}

void release_buffer(buffer_pool_t* pool, buffer_t* buffer) {
    buffer->in_use = false;
}
