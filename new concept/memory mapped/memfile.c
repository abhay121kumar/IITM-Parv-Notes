// mmap_example.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];

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

    // 3. Memory-map the file
    char *mapped = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    // 4. Use file as memory
    write(STDOUT_FILENO, mapped, filesize); // print file contents

    // 5. Clean up
    munmap(mapped, filesize);
    close(fd);

    return 0;
}
