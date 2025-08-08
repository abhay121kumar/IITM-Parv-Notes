#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include "bufferpool.h"
#include "lrucache.h"
#include <time.h>

#define CACHE_SIZE 32  // Hash table size or max file entries (adjust as needed)
#define POOL_SIZE 10   // Number of buffers in pool
#define BUFFER_SIZE 4096

// Structure to store a cached file entry
typedef struct cached_file {
    char filename[256];
    buffer_t *buffer;
    size_t file_size;
    time_t last_accessed;
    struct cached_file *next;
} cached_file_t;

// File cache system structure
typedef struct file_cache {
    buffer_pool_t *buffer_pool;
    cached_file_t *files[CACHE_SIZE]; // Simple hash table for filenames
    int cached_files_count;
} file_cache_t;

// Function to create file cache
file_cache_t* create_file_cache();

// Function to read a file using cache
char* read_file_cached(file_cache_t *cache, const char *filename);

// Hash function to map filenames to an index
unsigned int hash(const char *str);

#endif // FILE_CACHE_H
