#include "slab.h"
#include <stdio.h>
#include <string.h>

#define COLOR_RED   "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

struct Slab
{
    void *memory;
    bool used[TUPLES_PER_SLAB];
};

Slab *create_slab()
{
    Slab *slab = malloc(sizeof(Slab));
    slab->memory = malloc(TUPLE_SIZE * TUPLES_PER_SLAB);
    memset(slab->used, 0, sizeof(slab->used));
    return slab;
}

void *slab_alloc(Slab *slab)
{
    for (int i = 0; i < TUPLES_PER_SLAB; ++i)
    {
        if (!slab->used[i])
        {
            slab->used[i] = true;
            return (char *)slab->memory + i * TUPLE_SIZE;
        }
    }
    return NULL;
}

void slab_free(Slab *slab, void *ptr)
{
    size_t offset = (char *)ptr - (char *)slab->memory;
    if (offset % TUPLE_SIZE != 0 || offset >= TUPLE_SIZE * TUPLES_PER_SLAB)
    {
        printf("Invalid pointer in slab_free.\\n");
        return;
    }
    size_t index = offset / TUPLE_SIZE;
    if (!slab->used[index])
    {
        printf("Double free detected.\\n");
        return;
    }
    slab->used[index] = false;
}

bool slab_owns(Slab *slab, void *ptr)
{
    return (char *)ptr >= (char *)slab->memory &&
           (char *)ptr < ((char *)slab->memory + TUPLE_SIZE * TUPLES_PER_SLAB);
}

void destroy_slab(Slab *slab)
{
    free(slab->memory);
    free(slab);
}

// size_t slab_leak_report(Slab* slab, int slab_index, FILE* out) {
//     size_t leak_count = 0;

//     for (int i = 0; i < TUPLES_PER_SLAB; ++i) {
//         if (slab_is_block_used(slab, i)) {
//             fprintf(out, "Leaked Tuple in Slab %d, Block %d\n", slab_index + 1, i);
//             leak_count++;
//         }
//     }

//     if (leak_count == 0) {
//         fprintf(out, "No leaks in Slab %d.\n", slab_index + 1);
//     }

//     return leak_count;
// }

size_t slab_leak_report(Slab* slab, int slab_index, FILE* out) {
    size_t leaks = 0;
    for (int i = 0; i < TUPLES_PER_SLAB; i++) {
        if (slab->used[i]) {
            fprintf(out, "Leaked Tuple in Slab %d, Block %d\n", slab_index, i);
            leaks++;
        }
    }
    return leaks;
}



int slab_get_used_blocks(Slab* slab) {
    int count = 0;
    for (int i = 0; i < TUPLES_PER_SLAB; ++i) {
        if (slab->used[i]) count++;
    }
    return count;
}

bool slab_is_block_used(Slab* slab, int index) {
    if (index < 0 || index >= TUPLES_PER_SLAB) return false;
    return slab->used[index];
}


void print_slab_memory_graph(Slab* slab, int slab_index) {
    if (!slab) return;

    printf("Slab %d:\n[", slab_index);

    for (int i = 0; i < TUPLES_PER_SLAB; ++i) {
        if (slab->used[i]) {
            printf(COLOR_RED "#");   // used block (red #)
        } else {
            printf(COLOR_GREEN "."); // free block (green .)
        }
    }

    printf(COLOR_RESET "] %d / %d used\n", slab_get_used_blocks(slab), TUPLES_PER_SLAB);
}