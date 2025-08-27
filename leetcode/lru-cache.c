#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 10000  

typedef struct Node {
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    int capacity;
    int size;
    Node* head;  
    Node* tail;  
    Node* hashmap[MAX_CAPACITY]; 
} LRUCache;


Node* create_node(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}


int hash(int key) {
    return key % MAX_CAPACITY;
}


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    memset(cache->hashmap, 0, sizeof(cache->hashmap));
    return cache;
}

// Move node to front of DLL
void move_to_front(LRUCache* cache, Node* node) {
    if (cache->head == node) return;

   
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (cache->tail == node) cache->tail = node->prev;

    node->prev = NULL;
    node->next = cache->head;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
}


int lRUCacheGet(LRUCache* cache, int key) {
    int idx = hash(key);
    Node* node = cache->hashmap[idx];
    while (node && node->key != key) node = node->next;

    if (!node) return -1;

    move_to_front(cache, node);
    return node->value;
}

// Put key-value into cache
void lRUCachePut(LRUCache* cache, int key, int value) {
    int idx = hash(key);
    Node* node = cache->hashmap[idx];

    // Check if key already exists
    while (node && node->key != key) node = node->next;

    if (node) {
        node->value = value;
        move_to_front(cache, node);
        return;
    }

    // New key
    Node* new_node = create_node(key, value);

    // Insert into hashmap (at head of collision chain)
    new_node->next = cache->hashmap[idx];
    if (cache->hashmap[idx]) cache->hashmap[idx]->prev = new_node;
    cache->hashmap[idx] = new_node;

    // Insert at front of DLL
    new_node->prev = NULL;
    new_node->next = cache->head;
    if (cache->head) cache->head->prev = new_node;
    cache->head = new_node;
    if (!cache->tail) cache->tail = new_node;

    cache->size++;

    // Evict if over capacity
    if (cache->size > cache->capacity) {
        Node* to_remove = cache->tail;
        if (to_remove->prev)
            to_remove->prev->next = NULL;
        cache->tail = to_remove->prev;

        // Remove from hashmap
        int remove_idx = hash(to_remove->key);
        Node* curr = cache->hashmap[remove_idx];
        Node* prev = NULL;
        while (curr && curr != to_remove) {
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            if (prev) prev->next = curr->next;
            else cache->hashmap[remove_idx] = curr->next;
        }

        free(to_remove);
        cache->size--;
    }
}

// Free memory
void lRUCacheFree(LRUCache* cache) {
    Node* curr = cache->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(cache);
}