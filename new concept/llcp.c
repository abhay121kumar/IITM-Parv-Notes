
#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>    // open, O_*
#include <unistd.h>   // read, write, lseek, close
#include <errno.h>
#include <stdio.h>    // fprintf, perror
#include <stdlib.h>   // exit, malloc, free
#include <string.h>   // strcmp, memset
#include <stdbool.h>  // bool

#ifndef COPY_BUFSZ
#define COPY_BUFSZ (1 << 20)  // 1 MiB default buffer
#endif

static ssize_t full_write(int fd, const void *buf, size_t n) {
    const unsigned char *p = (const unsigned char *)buf;
    size_t left = n;
    while (left > 0) {
        ssize_t w = write(fd, p, left);
        if (w < 0) {
            if (errno == EINTR) continue; // interrupted → retry
            return -1;                    // real error
        }
        p += w;
        left -= (size_t)w;
    }
    return (ssize_t)n;
}

static bool is_all_zeros(const unsigned char *buf, size_t n) {
    // Fast check: scan for any nonzero byte.
    for (size_t i = 0; i < n; ++i) {
        if (buf[i] != 0) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    bool sparse = false;
    const char *src = NULL, *dst = NULL;

    // Parse args: llcp [-s] src dst
    if (argc == 4 && strcmp(argv[1], "-s") == 0) {
        sparse = true;
        src = argv[2]; dst = argv[3];
    } else if (argc == 3) {
        src = argv[1]; dst = argv[2];
    } else {
        fprintf(stderr, "Usage: %s [-s] <src> <dst>\n", argv[0]);
        fprintf(stderr, "  -s   create sparse output for all-zero blocks\n");
        return 2;
    }

    // Basic (string) self-copy guard (not perfect without fstat).
    if (strcmp(src, dst) == 0) {
        fprintf(stderr, "Refusing to copy a file onto itself: %s\n", src);
        return 2;
    }

    // Open source for reading.
    int sfd = open(src, O_RDONLY);
    if (sfd < 0) { perror("open(src)"); return 1; }

    // Open destination: create/truncate, user rw (0644-like), rely on umask.
    // Note: we can't preserve mode/ownership without extra syscalls.
    int dfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dfd < 0) { perror("open(dst)"); close(sfd); return 1; }

    // Allocate buffer.
    unsigned char *buf = (unsigned char *)malloc(COPY_BUFSZ);
    if (!buf) {
        fprintf(stderr, "malloc(%d) failed\n", COPY_BUFSZ);
        close(sfd); close(dfd);
        return 1;
    }

    // Copy loop.
    for (;;) {
        ssize_t r = read(sfd, buf, COPY_BUFSZ);
        if (r < 0) {
            if (errno == EINTR) continue; // interrupted read → retry
            perror("read");
            free(buf); close(sfd); close(dfd);
            return 1;
        }
        if (r == 0) break; // EOF

        if (sparse && is_all_zeros(buf, (size_t)r)) {
            // Create a hole instead of writing zeros.
            off_t off = lseek(dfd, (off_t)r, SEEK_CUR);
            if (off == (off_t)-1) {
                // If lseek fails (e.g., not seekable), fall back to writing zeros.
                if (full_write(dfd, buf, (size_t)r) < 0) {
                    perror("write");
                    free(buf); close(sfd); close(dfd);
                    return 1;
                }
            }
        } else {
            if (full_write(dfd, buf, (size_t)r) < 0) {
                perror("write");
                free(buf); close(sfd); close(dfd);
                return 1;
            }
        }
    }

    // Optional: ensure file offset/materialized size aligns (some filesystems
    // mark a hole and keep file length automatically; nothing else needed here).

    free(buf);
    if (close(sfd) < 0) { perror("close(src)"); /* continue */ }
    if (close(dfd) < 0) { perror("close(dst)"); return 1; }

    return 0;
}
