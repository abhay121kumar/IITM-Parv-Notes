#include "file_cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

file_cache_t* create_file_cache(int pool_size, int buffer_size, int lru_size) {
    file_cache_t* cache = malloc(sizeof(file_cache_t));
    cache->buffer_pool = create_buffer_pool(pool_size, buffer_size);
    cache->lru_cache = create_lru_cache(lru_size);
    return cache;
}

void destroy_file_cache(file_cache_t *cache) {
    destroy_buffer_pool(cache->buffer_pool);
    destroy_lru_cache(cache->lru_cache);
    free(cache);
}

buffer_t* read_file_cached(file_cache_t *cache, const char *filename) {
    buffer_t *cached = get_from_lru(cache->lru_cache, filename);
    if (cached) return cached;

    FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;

    buffer_t *buf = get_buffer(cache->buffer_pool);
    if (!buf) {
        fclose(fp);
        return NULL;
    }

    fread(buf->data, 1, buf->size, fp);
    fclose(fp);

    put_in_lru(cache->lru_cache, cache->buffer_pool, filename, buf);
    return buf;
}
