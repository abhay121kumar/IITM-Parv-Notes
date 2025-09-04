#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

// Size constants
#define FILE_SIZE   (100 * 1024 * 1024)  // 100 MB
#define BLOCK_SIZE  (4096)               // typical page size

// Timing helper
static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Create test file
static void create_file(const char *path) {
    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    if (ftruncate(fd, FILE_SIZE) < 0) {
        perror("ftruncate");
        exit(1);
    }
    close(fd);
}

// Buffered I/O benchmark
static void bench_buffered(const char *path) {
    unsigned char *buf = malloc(BLOCK_SIZE);
    if (!buf) { perror("malloc"); exit(1); }
    memset(buf, 0xAB, BLOCK_SIZE);

    int fd = open(path, O_RDWR);
    if (fd < 0) { perror("open"); exit(1); }

    double t0 = now_sec();
    for (off_t off = 0; off < FILE_SIZE; off += BLOCK_SIZE) {
        if (pwrite(fd, buf, BLOCK_SIZE, off) != BLOCK_SIZE) {
            perror("pwrite");
            exit(1);
        }
    }
    fsync(fd);
    double t1 = now_sec();

    // Drop kernel cache for fair read test
#ifdef __linux__
    posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED);
#endif

    for (off_t off = 0; off < FILE_SIZE; off += BLOCK_SIZE) {
        if (pread(fd, buf, BLOCK_SIZE, off) != BLOCK_SIZE) {
            perror("pread");
            exit(1);
        }
    }
    double t2 = now_sec();

    close(fd);
    free(buf);

    printf("Buffered I/O: write %.3f s, read %.3f s\n", t1 - t0, t2 - t1);
}

// Direct I/O benchmark
static void bench_direct(const char *path) {
    // O_DIRECT requires aligned buffer and size
    void *buf;
    if (posix_memalign(&buf, BLOCK_SIZE, BLOCK_SIZE) != 0) {
        perror("posix_memalign");
        exit(1);
    }
    memset(buf, 0xCD, BLOCK_SIZE);

    int fd = open(path, O_RDWR | O_DIRECT);
    if (fd < 0) { perror("open"); exit(1); }

    double t0 = now_sec();
    for (off_t off = 0; off < FILE_SIZE; off += BLOCK_SIZE) {
        if (pwrite(fd, buf, BLOCK_SIZE, off) != BLOCK_SIZE) {
            perror("pwrite");
            exit(1);
        }
    }
    fsync(fd);
    double t1 = now_sec();

#ifdef __linux__
    posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED);
#endif

    for (off_t off = 0; off < FILE_SIZE; off += BLOCK_SIZE) {
        if (pread(fd, buf, BLOCK_SIZE, off) != BLOCK_SIZE) {
            perror("pread");
            exit(1);
        }
    }
    double t2 = now_sec();

    close(fd);
    free(buf);

    printf("Direct I/O: write %.3f s, read %.3f s\n", t1 - t0, t2 - t1);
}

// mmap benchmark
static void bench_mmap(const char *path) {
    int fd = open(path, O_RDWR);
    if (fd < 0) { perror("open"); exit(1); }

    double t0 = now_sec();
    unsigned char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) { perror("mmap"); exit(1); }

    for (off_t off = 0; off < FILE_SIZE; off += BLOCK_SIZE) {
        memset(map + off, 0xEF, BLOCK_SIZE);
    }
    msync(map, FILE_SIZE, MS_SYNC);
    double t1 = now_sec();

#ifdef __linux__
    posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED);
#endif

    for (off_t off = 0; off < FILE_SIZE; off += BLOCK_SIZE) {
        volatile unsigned char c = map[off]; (void)c; // force read
    }
    double t2 = now_sec();

    munmap(map, FILE_SIZE);
    close(fd);

    printf("mmap I/O: write %.3f s, read %.3f s\n", t1 - t0, t2 - t1);
}

int main(void) {
    const char *path = "io_bench.dat";

    create_file(path);
    bench_buffered(path);
    bench_direct(path);
    bench_mmap(path);

    unlink(path); // cleanup
    return 0;
}
