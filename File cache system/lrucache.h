#ifndef LRUCACHE_H
#define LRUCACHE_H

#include "bufferpool.h"

typedef struct lru_node {
    char filename[256];
    buffer_t *buffer;
    struct lru_node *prev, *next;
} lru_node_t;

typedef struct {
    lru_node_t *head, *tail;
    int capacity;
    int size;
} lru_cache_t;

lru_cache_t* create_lru_cache(int capacity);
void put_in_lru(lru_cache_t *cache, buffer_pool_t *pool, const char *filename, buffer_t *buffer);
buffer_t* get_from_lru(lru_cache_t *cache, const char *filename);
void destroy_lru_cache(lru_cache_t *cache);

#endif
