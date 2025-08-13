#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include "bufferpool.h"
#include "lrucache.h"

typedef struct {
    buffer_pool_t *buffer_pool;
    lru_cache_t *lru_cache;
} file_cache_t;

file_cache_t* create_file_cache(int pool_size, int buffer_size, int lru_size);
void destroy_file_cache(file_cache_t *cache);
buffer_t* read_file_cached(file_cache_t *cache, const char *filename);

#endif
