// mmap_search.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void search_in_file(const char *filename, const char *keyword) {
    // 1. Open file
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // 2. Get file size
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        exit(1);
    }
    size_t filesize = st.st_size;
    if (filesize == 0) {
        printf("File is empty.\n");
        close(fd);
        return;
    }

    // 3. Memory-map the file
    char *data = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    // 4. Search for keyword
    size_t keylen = strlen(keyword);
    char *p = data;
    size_t matches = 0;

    while ((p = memmem(p, filesize - (p - data), keyword, keylen)) != NULL) {
        size_t offset = p - data;
        printf("Match at offset %zu\n", offset);
        matches++;
        p += keylen; // move past this match
    }

    if (matches == 0) {
        printf("No matches found for '%s'.\n", keyword);
    }

    // 5. Clean up
    munmap(data, filesize);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <keyword>\n", argv[0]);
        exit(1);
    }

    search_in_file(argv[1], argv[2]);
    return 0;
}
