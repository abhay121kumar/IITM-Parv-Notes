
#define MAX_HASH_SIZE 10007

typedef struct Node {
    char* key;
    char** group;
    int size;
    int capacity;
    struct Node* next;
} Node;

unsigned long hash(const char* str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c;
    return h % MAX_HASH_SIZE;
}

int cmpChar(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

char* sortString(const char* str) {
    int len = strlen(str);
    char* sorted = malloc(len + 1);
    strcpy(sorted, str);
    qsort(sorted, len, sizeof(char), cmpChar);
    return sorted;
}

char* strdupSafe(const char* str) {
    char* copy = malloc(strlen(str) + 1);
    if (!copy) exit(1);
    strcpy(copy, str);
    return copy;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    Node* hashTable[MAX_HASH_SIZE] = {0};

    for (int i = 0; i < strsSize; i++) {
        char* sortedKey = sortString(strs[i]);
        unsigned long h = hash(sortedKey);

        Node* curr = hashTable[h];
        while (curr && strcmp(curr->key, sortedKey) != 0)
            curr = curr->next;

        if (!curr) {
            curr = malloc(sizeof(Node));
            curr->key = sortedKey;
            curr->group = malloc(4 * sizeof(char*));
            curr->capacity = 4;
            curr->size = 0;
            curr->next = hashTable[h];
            hashTable[h] = curr;
        } else {
            free(sortedKey); // Already stored in key
        }

        if (curr->size >= curr->capacity) {
            curr->capacity *= 2;
            curr->group = realloc(curr->group, curr->capacity * sizeof(char*));
        }

        curr->group[curr->size++] = strdupSafe(strs[i]);
    }

    // Build result
    char*** result = malloc(strsSize * sizeof(char**));
    *returnColumnSizes = malloc(strsSize * sizeof(int));
    int count = 0;

    for (int i = 0; i < MAX_HASH_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr) {
            result[count] = curr->group;
            (*returnColumnSizes)[count] = curr->size;
            count++;
            curr = curr->next;
        }
    }

    *returnSize = count;
    return result;
}