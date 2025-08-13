#include "bufferpool.h"
#include <stdlib.h>
#include <string.h>

buffer_pool_t* create_buffer_pool(int pool_size, int buffer_size) {
    buffer_pool_t *pool = malloc(sizeof(buffer_pool_t));
    pool->pool_size = pool_size;
    pool->buffer_size = buffer_size;
    pool->buffers = malloc(pool_size * sizeof(buffer_t));
    for (int i = 0; i < pool_size; ++i) {
        pool->buffers[i].data = malloc(buffer_size);
        pool->buffers[i].size = buffer_size;
        pool->buffers[i].in_use = 0;
        pool->buffers[i].buffer_pool = pool;  // <== fix
    }
    return pool;
}

buffer_t* get_buffer(buffer_pool_t *pool) {
    for (int i = 0; i < pool->pool_size; ++i) {
        if (!pool->buffers[i].in_use) {
            pool->buffers[i].in_use = 1;
            memset(pool->buffers[i].data, 0, pool->buffer_size);
            return &pool->buffers[i];
        }
    }
    return NULL;
}

void release_buffer(buffer_pool_t *pool, buffer_t *buffer) {
    buffer->in_use = 0;
}

void destroy_buffer_pool(buffer_pool_t *pool) {
    for (int i = 0; i < pool->pool_size; ++i) {
        free(pool->buffers[i].data);
    }
    free(pool->buffers);
    free(pool);
}
