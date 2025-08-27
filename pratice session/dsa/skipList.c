#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 10
#define P 0.5

// Node structure
typedef struct Node {
    int key;
    struct Node** forward;
} Node;

// Skip list structure
typedef struct SkipList {
    int level;
    Node* header;
} SkipList;

// Function to create a new node
Node* createNode(int key, int level) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->forward = (Node**)malloc(sizeof(Node*) * (level + 1));
    for (int i = 0; i <= level; i++)
        n->forward[i] = NULL;
    return n;
}

// Create an empty skip list
SkipList* createSkipList() {
    SkipList* list = (SkipList*)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(-1, MAX_LEVEL); // Header with dummy key
    return list;
}

// Random level generator
int randomLevel() {
    int level = 0;
    while ((rand() / (double)RAND_MAX) < P && level < MAX_LEVEL)
        level++;
    return level;
}

// Insert a key into skip list
void insert(SkipList* list, int key) {
    Node* update[MAX_LEVEL + 1];
    Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->key != key) {
        int lvl = randomLevel();
        if (lvl > list->level) {
            for (int i = list->level + 1; i <= lvl; i++) {
                update[i] = list->header;
            }
            list->level = lvl;
        }

        Node* newNode = createNode(key, lvl);
        for (int i = 0; i <= lvl; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        printf("Inserted %d\n", key);
    }
}

// Search for a key
Node* search(SkipList* list, int key) {
    Node* current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
    }
    current = current->forward[0];

    if (current && current->key == key)
        return current;
    return NULL;
}

// Delete a key
void delete(SkipList* list, int key) {
    Node* update[MAX_LEVEL + 1];
    Node* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    if (current && current->key == key) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }

        free(current->forward);
        free(current);

        // Adjust list level
        while (list->level > 0 && list->header->forward[list->level] == NULL)
            list->level--;
        printf("Deleted %d\n", key);
    } else {
        printf("Key %d not found.\n", key);
    }
}

// Display skip list
void display(SkipList* list) {
    printf("Skip List (Level 0): ");
    Node* current = list->header->forward[0];
    while (current) {
        printf("%d ", current->key);
        current = current->forward[0];
    }
    printf("\n");
}

// Main function to test skip list
int main() {
    srand(time(NULL));
    SkipList* list = createSkipList();

    insert(list, 3);
    insert(list, 6);
    insert(list, 7);
    insert(list, 9);
    insert(list, 12);
    insert(list, 19);

    display(list);

    Node* found = search(list, 7);
    if (found)
        printf("Found: %d\n", found->key);
    else
        printf("Not found.\n");

    delete(list, 7);
    display(list);

    return 0;
}
