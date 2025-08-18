// List 0: 20 -> 10 -> NULL      
// List 1: 30 -> NULL
// List 2: 60 -> 50 -> 40 -> NULL
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Function to add a node to the front of a list
void add_to_list(Node **head, int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

// Print a single linked list
void print_list(Node *head) {
    while (head) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    int list_count = 3;

    // Allocate an array of Node* (each points to a list)
    Node **lists = calloc(list_count, sizeof(Node*));  // all initialized to NULL

    // Add values to each list
    add_to_list(&lists[0], 10);
    add_to_list(&lists[0], 20);
    add_to_list(&lists[1], 30);
    add_to_list(&lists[2], 40);
    add_to_list(&lists[2], 50);
    add_to_list(&lists[2], 60);

    // Print all lists
    for (int i = 0; i < list_count; i++) {
        printf("List %d: ", i);
        print_list(lists[i]);
    }

    // Free memory (left as an exercise)
    return 0;
}
