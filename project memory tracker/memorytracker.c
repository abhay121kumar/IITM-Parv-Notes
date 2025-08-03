#include "memorytracker.h"
#include "hashtable.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

static int initialized = 0;

static void init_tracker() {
    if (!initialized) {
        ht_init();
        initialized = 1;
    }
}

void* mt_malloc(size_t size) {
    init_tracker();
    void* ptr = malloc(size);
    if (ptr) {
        ht_insert(ptr, size, "malloc");
        log_event("ALLOC", ptr, size, "malloc");
    }
    return ptr;
}

void* mt_calloc(size_t num, size_t size) {
    init_tracker();
    void* ptr = calloc(num, size);
    if (ptr) {
        ht_insert(ptr, num * size, "calloc");
        log_event("ALLOC", ptr, num * size, "calloc");
    }
    return ptr;
}

void* mt_realloc(void* ptr, size_t new_size) {
    init_tracker();
    if (ptr) {
        ht_remove(ptr);  // mark old as freed
        log_event("FREE", ptr, 0, "realloc old");
    }

    void* new_ptr = realloc(ptr, new_size);
    if (new_ptr) {
        ht_insert(new_ptr, new_size, "realloc");
        log_event("ALLOC", new_ptr, new_size, "realloc new");
    }
    return new_ptr;
}

void mt_free(void* ptr) {
    init_tracker();
    if (!ptr) return;

    int found = ht_remove(ptr);
    if (found) {
        free(ptr);
        log_event("FREE", ptr, 0, "ok");
    } else {
        log_event("FREE", ptr, 0, "warning: invalid or double free");
    }
}

void mt_summary() {
    printf("\n--- Memory Tracker Summary ---\n");
    ht_dump_leaks();
}

void mt_finalize() {
    ht_free_all();
}
