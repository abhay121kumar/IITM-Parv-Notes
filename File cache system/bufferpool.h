#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <stddef.h>

typedef struct buffer {
    char *data;
    size_t size;
    int in_use;
    struct buffer_pool *buffer_pool; // <== fix: add this
} buffer_t;

typedef struct buffer_pool {
    buffer_t *buffers;
    int pool_size;
    int buffer_size;
} buffer_pool_t;

buffer_pool_t* create_buffer_pool(int pool_size, int buffer_size);
buffer_t* get_buffer(buffer_pool_t *pool);
void release_buffer(buffer_pool_t *pool, buffer_t *buffer);
void destroy_buffer_pool(buffer_pool_t *pool);

#endif
