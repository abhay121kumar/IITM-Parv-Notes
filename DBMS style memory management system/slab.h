// #ifndef SLAB_H
// #define SLAB_H

// #include <stdlib.h>
// #include <stdbool.h>

// #define TUPLE_SIZE 64
// #define TUPLES_PER_SLAB 128

// typedef struct Slab Slab;

// Slab* create_slab();
// void* slab_alloc(Slab* slab);
// void slab_free(Slab* slab, void* ptr);
// bool slab_owns(Slab* slab, void* ptr);


// void destroy_slab(Slab* slab);
// size_t slab_leak_report(Slab* slab);
// int slab_get_used_blocks(Slab* slab); 

// int slab_get_used_blocks(Slab* slab);
// bool slab_is_block_used(Slab* slab, int index);

// #endif // SLAB_H

#ifndef SLAB_H
#define SLAB_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // Required for malloc/free

#define TUPLES_PER_SLAB 128
#define TUPLE_SIZE 64

typedef struct Slab Slab;

// Existing functions
Slab* create_slab();
void* allocate_tuple_from_slab(Slab* slab);
bool free_tuple_from_slab(Slab* slab, void* ptr);
bool slab_owns(Slab* slab, void* ptr);
void destroy_slab(Slab* slab);
int slab_get_used_blocks(Slab* slab);
bool slab_is_block_used(Slab* slab, int index);

// 🔧 Add missing declarations used in memory_manager.c
void* slab_alloc(Slab* slab);
void slab_free(Slab* slab, void* ptr);
size_t slab_leak_report(Slab* slab, int slab_index, FILE* out);

void print_slab_memory_graph(Slab* slab, int slab_id);

#endif
