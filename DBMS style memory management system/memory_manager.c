#include "memory_manager.h"
#include "slab.h"
#include <stdio.h>

#define MAX_SLABS 100

static Slab* slabs[MAX_SLABS];
static int slab_count = 0;

void init_memory_manager() {
    slabs[slab_count++] = create_slab();
}

static int debug_mode = 0;

void mm_set_debug_mode(int enabled) {
    debug_mode = enabled;
}

void mm_print_stats() {
    printf("---- Memory Stats ----\n");
    printf("Total Slabs: %d\n", slab_count);
    for (int i = 0; i < slab_count; i++) {
        printf("Slab %d: Used %d / %d\n", i + 1,
               slab_get_used_blocks(slabs[i]) // ✅
);
    }
}

void mm_write_leak_report(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error writing leak report\n");
        return;
    }

    fprintf(fp, "Memory Leak Report\n");
    fprintf(fp, "===================\n");

    size_t total_leaks = 0;

    for (int i = 0; i < slab_count; ++i) {
        total_leaks += slab_leak_report(slabs[i], i, fp);  // ✅ pass file
    }

    fprintf(fp, "-------------------\nTotal Leaks: %zu\n", total_leaks);

    fclose(fp);
    printf("Leak report saved to %s\n", filename);
}



void* allocate_tuple() {
    for (int i = 0; i < slab_count; ++i) {
        void* ptr = slab_alloc(slabs[i]);
        if (ptr) return ptr;
    }
    if (slab_count < MAX_SLABS) {
        slabs[slab_count++] = create_slab();
        return slab_alloc(slabs[slab_count - 1]);
    }
    return NULL;
}

void free_tuple(void* ptr) {
    for (int i = 0; i < slab_count; ++i) {
        if (slab_owns(slabs[i], ptr)) {
            slab_free(slabs[i], ptr);
            return;
        }
    }
    printf("Invalid free detected.\\n");
}

// void shutdown_memory_manager() {
//     size_t total_leaks = 0;

//     // Also print to stdout
//     printf("Shutdown Leak Report\n");
//     printf("====================\n");

//     for (int i = 0; i < slab_count; ++i) {
//         total_leaks += slab_leak_report(slabs[i], i, stdout); // ✅ print on screen
//         destroy_slab(slabs[i]);
//     }

//     printf("--------------------\nTotal Memory Leaks: %zu\n", total_leaks);
// }

void shutdown_memory_manager() {
    FILE* fp = fopen("leaks.log", "w");
    if (!fp) {
        printf("Error opening leaks.log for writing\n");
        return;
    }

    fprintf(fp, "Shutdown Leak Report\n");
    fprintf(fp, "====================\n");

    size_t total_leaks = 0;
    for (int i = 0; i < slab_count; ++i) {
        total_leaks += slab_leak_report(slabs[i], i + 1, fp);  // ✅ Pass FILE*
        destroy_slab(slabs[i]);
    }

    fprintf(fp, "--------------------\n");
    fprintf(fp, "Total Memory Leaks: %zu\n", total_leaks);
    fclose(fp);

    printf("Leak report saved to leaks.log\n");
    printf("Shutdown complete. Memory leaks: %zu\n", total_leaks);
}


void mm_print_memory_graph() {
    printf("---- Memory Usage Graph ----\n");
    for (int i = 0; i < slab_count; ++i) {
        print_slab_memory_graph(slabs[i], i + 1);
    }
    printf("---- End of Memory Usage Graph ----\n");
}