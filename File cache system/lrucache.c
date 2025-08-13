#include "lrucache.h"
#include <stdlib.h>
#include <string.h>

lru_cache_t* create_lru_cache(int capacity) {
    lru_cache_t *cache = malloc(sizeof(lru_cache_t));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    return cache;
}

void move_to_front(lru_cache_t *cache, lru_node_t *node) {
    if (node == cache->head) return;
    if (node == cache->tail) cache->tail = node->prev;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    node->prev = NULL;
    node->next = cache->head;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
}

void put_in_lru(lru_cache_t *cache, buffer_pool_t *pool, const char *filename, buffer_t *buffer) {
    lru_node_t *current = cache->head;
    while (current) {
        if (strcmp(current->filename, filename) == 0) {
            current->buffer = buffer;
            move_to_front(cache, current);
            return;
        }
        current = current->next;
    }

    lru_node_t *node = malloc(sizeof(lru_node_t));
    strncpy(node->filename, filename, 255);
    node->filename[255] = '\0';
    node->buffer = buffer;
    node->prev = NULL;
    node->next = cache->head;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
    cache->size++;

    if (cache->size > cache->capacity) {
        lru_node_t *to_remove = cache->tail;
        cache->tail = to_remove->prev;
        if (cache->tail) cache->tail->next = NULL;
        release_buffer(pool, to_remove->buffer);  // ✅ fix
        free(to_remove);
        cache->size--;
    }
}

buffer_t* get_from_lru(lru_cache_t *cache, const char *filename) {
    lru_node_t *current = cache->head;
    while (current) {
        if (strcmp(current->filename, filename) == 0) {
            move_to_front(cache, current);
            return current->buffer;
        }
        current = current->next;
    }
    return NULL;
}

void destroy_lru_cache(lru_cache_t *cache) {
    lru_node_t *current = cache->head;
    while (current) {
        lru_node_t *temp = current;
        current = current->next;
        free(temp);
    }
    free(cache);
}
