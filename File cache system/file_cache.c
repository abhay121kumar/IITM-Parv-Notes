#include "file_cache.h"
#include "lrucache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256

// Global objects
buffer_pool_t *global_pool = NULL;
lru_cache_t *global_lru = NULL;

// Initialize everything
void initialize_file_cache(int pool_size, int buffer_size, int lru_capacity) {
    global_pool = create_buffer_pool(pool_size, buffer_size);
    global_lru = create_lru_cache(lru_capacity);
}

// Read file using LRU cache
char* read_file_cached(const char *filename) {
    if (!global_pool || !global_lru) {
        fprintf(stderr, "Cache not initialized.\n");
        return NULL;
    }

    // Try to get from cache
    buffer_t *cached_buf = get_from_lru(global_lru, filename);
    if (cached_buf) {
        printf("[Cache Hit] %s\n", filename);
        return cached_buf->data;
    }

    // Cache miss: read from file
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    buffer_t *buf = allocate_buffer(global_pool);
    if (!buf) {
        fprintf(stderr, "No free buffers in pool.\n");
        fclose(fp);
        return NULL;
    }

    size_t bytes = fread(buf->data, 1, size, fp);
    buf->data[bytes] = '\0';
    fclose(fp);

    insert_lru(global_lru, filename, buf, bytes, global_pool);
    printf("[Cache Miss] %s\n", filename);
    return buf->data;
}

// Cleanup everything
void shutdown_file_cache() {
    if (global_lru)
        free_lru_cache(global_lru, global_pool);
    if (global_pool)
        free_buffer_pool(global_pool);
}
