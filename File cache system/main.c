#include <stdio.h>
#include "file_cache.h"

#define POOL_SIZE 5
#define BUFFER_SIZE 1024
#define LRU_SIZE 3

int main() {
    file_cache_t *cache = create_file_cache(POOL_SIZE, BUFFER_SIZE, LRU_SIZE);

    const char *files[] = {"test1.txt", "test2.txt", "test3.txt", "test1.txt"};
    for (int i = 0; i < 4; ++i) {
        buffer_t *buf = read_file_cached(cache, files[i]);
        if (buf)
            printf("Read from cache/file: %s -> %s\n", files[i], buf->data);
        else
            printf("Failed to read: %s\n", files[i]);
    }

    destroy_file_cache(cache);
    return 0;
}
