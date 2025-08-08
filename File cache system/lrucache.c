#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lrucache.h"

lru_cache_t* create_lru_cache(int capacity) {
    lru_cache_t *cache = malloc(sizeof(lru_cache_t));
    cache->head = cache->tail = NULL;
    cache->size = 0;
    cache->capacity = capacity;
    return cache;
}

void move_to_front(lru_cache_t *cache, lru_node_t *node) {
    if (node == cache->head) return;

    // Remove node
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (node == cache->tail)
        cache->tail = node->prev;

    // Insert at front
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (!cache->tail)
        cache->tail = node;
}

buffer_t* get_from_lru(lru_cache_t *cache, const char *filename) {
    lru_node_t *curr = cache->head;
    while (curr) {
        if (strcmp(curr->filename, filename) == 0) {
            move_to_front(cache, curr);
            return curr->buffer;
        }
        curr = curr->next;
    }
    return NULL;
}

void insert_lru(lru_cache_t *cache, const char *filename, buffer_t *buffer, size_t size, buffer_pool_t *pool) {
    if (cache->size >= cache->capacity) {
        // Evict LRU
        lru_node_t *old_tail = cache->tail;
        if (old_tail) {
            printf("Evicting %s from cache\n", old_tail->filename);
            if (old_tail->prev)
                old_tail->prev->next = NULL;
            cache->tail = old_tail->prev;
            if (cache->head == old_tail)
                cache->head = NULL;

            release_buffer(pool, old_tail->buffer);
            free(old_tail);
            cache->size--;
        }
    }

    lru_node_t *node = malloc(sizeof(lru_node_t));
    strncpy(node->filename, filename, sizeof(node->filename));
    node->buffer = buffer;
    node->file_size = size;
    node->prev = NULL;
    node->next = cache->head;

    if (cache->head)
        cache->head->prev = node;
    cache->head = node;
    if (!cache->tail)
        cache->tail = node;

    cache->size++;
}

void free_lru_cache(lru_cache_t *cache, buffer_pool_t *pool) {
    lru_node_t *curr = cache->head;
    while (curr) {
        lru_node_t *temp = curr;
        curr = curr->next;
        release_buffer(pool, temp->buffer);
        free(temp);
    }
    free(cache);
}
