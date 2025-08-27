
typedef struct {
    int* memory;
    int size;
} Allocator;

Allocator* allocatorCreate(int n) {
    Allocator* obj = (Allocator*)malloc(sizeof(Allocator));
    obj->size = n;
    obj->memory = (int*)calloc(n, sizeof(int));
    return obj;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int consecutive = 0;

    for (int i = 0; i < obj->size; ++i) {
        if (obj->memory[i] == 0) {
            ++consecutive;
        } else {
            consecutive = 0;
        }

        if (consecutive == size) {
            int start = i - size + 1;
            for (int j = start; j <= i; ++j) {
                obj->memory[j] = mID;
            }
            return start;
        }
    }
    return -1; // Not enough space
}

// Free all memory units with the given mID
int allocatorFreeMemory(Allocator* obj, int mID) {
    int freed = 0;
    for (int i = 0; i < obj->size; ++i) {
        if (obj->memory[i] == mID) {
            obj->memory[i] = 0;
            ++freed;
        }
    }
    return freed;
}

void allocatorFree(Allocator* obj) {
    if (obj) {
        free(obj->memory);
        free(obj);
    }
}


/**
 * Your Allocator struct will be instantiated and called as such:
 * Allocator* obj = allocatorCreate(n);
 * int param_1 = allocatorAllocate(obj, size, mID);
 
 * int param_2 = allocatorFreeMemory(obj, mID);
 
 * allocatorFree(obj);
*/