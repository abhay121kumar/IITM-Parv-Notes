#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 5  


typedef struct Buffer {
    int id;              
    char data[256];      
    struct Buffer* prev;
    struct Buffer* next;
} Buffer;


typedef struct {
    int capacity;          
    int size;              
    Buffer* head;        
    Buffer* tail;         
    Buffer* hashmap[MAX_CAPACITY];  
} LRUCache;


Buffer* create_buffer(int id, const char* data) {
    Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
    buffer->id = id;
    strncpy(buffer->data, data, sizeof(buffer->data) - 1);
    buffer->data[sizeof(buffer->data) - 1] = '\0';  
    buffer->prev = buffer->next = NULL;
    return buffer;
}


int hash(int id) {
    return id % MAX_CAPACITY;
}


LRUCache* lruCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    memset(cache->hashmap, 0, sizeof(cache->hashmap));  
    return cache;
}


void move_to_front(LRUCache* cache, Buffer* buffer) {
    if (cache->head == buffer) return;  

    // Remove from current position
    if (buffer->prev) buffer->prev->next = buffer->next;
    if (buffer->next) buffer->next->prev = buffer->prev;
    if (cache->tail == buffer) cache->tail = buffer->prev;

    // Move to front
    buffer->prev = NULL;
    buffer->next = cache->head;
    if (cache->head) cache->head->prev = buffer;
    cache->head = buffer;
    if (!cache->tail) cache->tail = buffer;
}

// Get a buffer by its ID (LRU)
Buffer* lruCacheGet(LRUCache* cache, int id) {
    int idx = hash(id);
    Buffer* buffer = cache->hashmap[idx];

    while (buffer && buffer->id != id) buffer = buffer->next;

    if (!buffer) return NULL;  // Buffer not found

    move_to_front(cache, buffer);
    return buffer;
}

// Put a new buffer in the cache (or update existing buffer)
void lruCachePut(LRUCache* cache, int id, const char* data) {
    int idx = hash(id);
    Buffer* buffer = cache->hashmap[idx];

    // Search for the buffer in the hashmap
    while (buffer && buffer->id != id) buffer = buffer->next;

    if (buffer) {
        // Buffer exists, update its data and move to front
        strncpy(buffer->data, data, sizeof(buffer->data) - 1);
        buffer->data[sizeof(buffer->data) - 1] = '\0';
        move_to_front(cache, buffer);
        return;
    }

    // New buffer
    Buffer* new_buffer = create_buffer(id, data);

    // Insert into hashmap (at the head of collision chain)
    new_buffer->next = cache->hashmap[idx];
    if (cache->hashmap[idx]) cache->hashmap[idx]->prev = new_buffer;
    cache->hashmap[idx] = new_buffer;

    // Insert at the front of the doubly linked list (most recent)
    new_buffer->prev = NULL;
    new_buffer->next = cache->head;
    if (cache->head) cache->head->prev = new_buffer;
    cache->head = new_buffer;
    if (!cache->tail) cache->tail = new_buffer;

    cache->size++;

    // Evict the least recently used buffer if the pool is full
    if (cache->size > cache->capacity) {
        Buffer* evict_buffer = cache->tail;
        if (evict_buffer->prev) evict_buffer->prev->next = NULL;
        cache->tail = evict_buffer->prev;

        // Remove from hashmap
        int evict_idx = hash(evict_buffer->id);
        Buffer* temp = cache->hashmap[evict_idx];
        if (temp == evict_buffer) {
            cache->hashmap[evict_idx] = temp->next;
        } else {
            while (temp && temp->next != evict_buffer) temp = temp->next;
            if (temp) temp->next = evict_buffer->next;
        }

        free(evict_buffer);
        cache->size--;
    }
}

// Free memory for the cache
void lruCacheFree(LRUCache* cache) {
    Buffer* buffer = cache->head;
    while (buffer) {
        Buffer* next = buffer->next;
        free(buffer);
        buffer = next;
    }
    free(cache);
}

// Print buffer data for debugging
void printBuffer(LRUCache* cache, int id) {
    Buffer* buffer = lruCacheGet(cache, id);
    if (buffer) {
        printf("Buffer ID: %d, Data: %s\n", buffer->id, buffer->data);
    } else {
        printf("Buffer with ID %d not found.\n", id);
    }
}

int main() {
    LRUCache* cache = lruCacheCreate(3);

    // Put buffers into the cache
    lruCachePut(cache, 1, "Buffer 1");
    lruCachePut(cache, 2, "Buffer 2");
    lruCachePut(cache, 3, "Buffer 3");

    // Access buffers
    printBuffer(cache, 1); 
    printBuffer(cache, 2); 

    // Add another buffer, which will evict the least recently used buffer (Buffer 3)
    lruCachePut(cache, 4, "Buffer 4");

    // Try accessing evicted buffer
    printBuffer(cache, 3); // Should print "Buffer with ID 3 not found."

    // Put more buffers and test eviction
    lruCachePut(cache, 5, "Buffer 5");
    printBuffer(cache, 4); 
    printBuffer(cache, 5); 

    // Free the cache
    lruCacheFree(cache);
    return 0;
}
