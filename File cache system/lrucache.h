#ifndef LRUCACHE_H
#define LRUCACHE_H

#include "bufferpool.h"

typedef struct lru_node {
    char filename[256];
    buffer_t *buffer;
    size_t file_size;
    struct lru_node *prev;
    struct lru_node *next;
} lru_node_t;

typedef struct {
    lru_node_t *head;
    lru_node_t *tail;
    int size;
    int capacity;
} lru_cache_t;

lru_cache_t* create_lru_cache(int capacity);
void free_lru_cache(lru_cache_t *cache, buffer_pool_t *pool);
char* access_lru(lru_cache_t *cache, const char *filename);
void insert_lru(lru_cache_t *cache, const char *filename, buffer_t *buffer, size_t size, buffer_pool_t *pool);
buffer_t* get_from_lru(lru_cache_t *cache, const char *filename);

#endif
