#include "memory_pool.h"
#include <stdio.h>
#include <stdint.h>

#define POOL_SIZE 1024
#define ALIGN4(s) (((s) + 3) & ~3)
#define BLOCK_SIZE sizeof(Block)

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

static uint8_t memory_pool[POOL_SIZE];
static Block* free_list = NULL;

void pool_init(void) {
    free_list = (Block*)memory_pool;
    free_list->size = POOL_SIZE - BLOCK_SIZE;
    free_list->free = 1;
    free_list->next = NULL;
}

void* pool_allocate(size_t size) {
    size = ALIGN4(size);
    Block* curr = free_list;

    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size >= size + BLOCK_SIZE + 4) {
                Block* new_block = (Block*)((uint8_t*)curr + BLOCK_SIZE + size);
                new_block->size = curr->size - size - BLOCK_SIZE;
                new_block->free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }

            curr->free = 0;
            printf("Allocated %zu bytes at %p\n", size, (void*)((uint8_t*)curr + BLOCK_SIZE));
            return (void*)((uint8_t*)curr + BLOCK_SIZE);
        }
        curr = curr->next;
    }

    printf("Allocation of %zu bytes failed: Not enough memory.\n", size);
    return NULL;
}

void pool_free(void* ptr) {
    if (!ptr)
        return;

    Block* block = (Block*)((uint8_t*)ptr - BLOCK_SIZE);
    block->free = 1;
    printf("Freed %zu bytes at %p\n", block->size, ptr);

    // Coalesce adjacent free blocks
    Block* curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += BLOCK_SIZE + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}
