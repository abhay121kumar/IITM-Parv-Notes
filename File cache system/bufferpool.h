#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#define BUFFER_SIZE 1024
#define POOL_SIZE 5

typedef struct buffer {
    char data[BUFFER_SIZE];
    bool in_use;
} buffer_t;

typedef struct buffer_pool {
    buffer_t buffers[POOL_SIZE];
} buffer_pool_t;

buffer_pool_t* create_buffer_pool(int size);
void destroy_buffer_pool(buffer_pool_t* pool);
buffer_t* acquire_buffer(buffer_pool_t* pool);
void release_buffer(buffer_pool_t* pool, buffer_t* buffer);

#endif