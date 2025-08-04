#include "memorytracker.h"
#include "hashtable.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

static int initialized = 0;
size_t total_allocated = 0;
size_t total_freed = 0;
static int summary_logged = 0;

#include <stdlib.h>  // For exit()
#include <time.h>    // For timestamp

static void fatal_error(const char* message, void* ptr) {
    // Print to terminal
    fprintf(stderr, "\n[FATAL ERROR] %s at %p\n", message, ptr);

    // Log to memory_log.txt
    FILE* file = fopen("memory_log.txt", "a");
    if (file) {
        time_t now = time(NULL);
        fprintf(file, "[%s] FATAL ERROR: %s at %p\n", ctime(&now), message, ptr);
        fclose(file);
    }

    // Clean up and exit
    mt_summary();  // Log partial stats
    ht_free_all(); // Free hash table
    exit(EXIT_FAILURE);  // Abort program immediately
}

// Initialize the memory tracker and log session start
static void init_tracker() {
    if (!initialized) {
        ht_init();
        log_session_start();  // Log the start of a new session
        initialized = 1;
    }
}

void* mt_malloc(size_t size) {
    init_tracker();
    if (size == 0) {
        log_event("WARN", NULL, size, "malloc(0) ignored");
        return NULL;
    }
    void* ptr = malloc(size);
    if (ptr) {
        ht_insert(ptr, size, "malloc");
        log_event("ALLOC", ptr, size, "malloc");
    }
    return ptr;
}

void* mt_calloc(size_t num, size_t size) {
    init_tracker();
    if (num == 0 || size == 0) {
        log_event("WARN", NULL, 0, "calloc(0, x) or calloc(x, 0) ignored");
        return NULL;
    }
    void* ptr = calloc(num, size);
    if (ptr) {
        ht_insert(ptr, num * size, "calloc");
        log_event("ALLOC", ptr, num * size, "calloc");
    }
    return ptr;
}

// void* mt_realloc(void* ptr, size_t new_size) {
//     init_tracker();
//     if (ptr) {
//         ht_remove(ptr);  // mark old as freed
//         log_event("FREE", ptr, 0, "realloc old");
//     }

//     void* new_ptr = realloc(ptr, new_size);
//     if (new_ptr) {
//         ht_insert(new_ptr, new_size, "realloc");
//         log_event("ALLOC", new_ptr, new_size, "realloc new");
//     }
//     return new_ptr;
// }

void* mt_realloc(void* ptr, size_t new_size) {
    init_tracker();

    if (ptr) {
        int removed = ht_remove(ptr);  // Check if it was valid

        if (!removed) {
            log_event("REALLOC", ptr, 0, "warning: realloc on freed or invalid pointer");
            fatal_error("Invalid realloc (use-after-free?)", ptr);  // << Here
        }

        log_event("FREE", ptr, 0, "realloc old");
    }

    void* new_ptr = realloc(ptr, new_size);
    if (new_ptr) {
        ht_insert(new_ptr, new_size, "realloc");
        log_event("ALLOC", new_ptr, new_size, "realloc new");
    }

    return new_ptr;
}


// void mt_free(void* ptr) {
//     init_tracker();
//     if (!ptr) return;

//     int found = ht_remove(ptr);
//     if (found) {
//         free(ptr);
//         log_event("FREE", ptr, 0, "ok");
//     } else {
//         log_event("FREE", ptr, 0, "warning: invalid or double free");
//     }
// }

void mt_free(void* ptr) {
    init_tracker();
    if (!ptr) return;

    int found = ht_remove(ptr);
    if (found) {
        free(ptr);
        log_event("FREE", ptr, 0, "ok");
    } else {
        log_event("FREE", ptr, 0, "warning: invalid or double free");
        fatal_error("Double or invalid free detected", ptr);  // << Call here
    }
}

// void mt_summary() {
//     // First, dump all allocations and their status
//     ht_dump_all();

//     // Then, write final summary stats (total alloc/freed/leaked)
//     extern size_t total_allocated, total_freed;

//     FILE* file = fopen("memory_log.txt", "a");
//     if (file) {
//         fprintf(file, "\n=========================================================\n");
//         fprintf(file, "--- Memory Tracker Summary ---\n");
//         fprintf(file, "--- Memory Usage Stats ---\n");
//         fprintf(file, "Total Allocated: %zu bytes\n", total_allocated);
//         fprintf(file, "Total Freed:     %zu bytes\n", total_freed);
//         fprintf(file, "Memory Leaked:   %zu bytes\n", total_allocated - total_freed);
//         fclose(file);
//     }
// }


void mt_summary() {
    if (summary_logged) return;  // Don't log again
    summary_logged = 1;
    printf(">>> mt_summary() called\n"); // ✅ DEBUG print
    // Dump all active allocations
    ht_dump_all();

    extern size_t total_allocated, total_freed;
    FILE* file = fopen("memory_log.txt", "a");
    if (file) {
        fprintf(file, "\n=========================================================\n");
        fprintf(file, "--- Memory Tracker Summary ---\n");
        fprintf(file, "--- Memory Usage Stats ---\n");
        fprintf(file, "Total Allocated: %zu bytes\n", total_allocated);
        fprintf(file, "Total Freed:     %zu bytes\n", total_freed);
        fprintf(file, "Memory Leaked:   %zu bytes\n", total_allocated - total_freed);
        fclose(file);
    }
}


void mt_finalize() {
    printf(">>> mt_finalize() called\n"); // ADD THIS
    mt_summary();     // Log summary
    ht_free_all();    // Now destroy internal hash table
}




