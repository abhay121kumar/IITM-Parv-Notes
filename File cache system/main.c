#include <stdio.h>
#include <stdlib.h>
#include "bufferpool.h"
#include "lrucache.h"

char* read_file_cached();
typedef struct file_cache file_cache_t;
file_cache_t* create_file_cache();

int main() {
    file_cache_t* cache = create_file_cache();
    if (!cache) {
        printf("Failed to create cache\n");
        return 1;
    }

    const char* filenames[] = {"file1.txt", "file2.txt", "file1.txt", "file3.txt"};
    for (int i = 0; i < 4; ++i) {
        char* content = read_file_cached(cache, filenames[i]);
        if (content) {
            printf("Content: %s\n", content);
        }
    }
    return 0;
}
