// #include<stdio.h>
// #include<stdlib.h>

// struct Node{
//     int val;
//     struct Node* next;
// };

// struct Node *head = NULL;

// struct Node* createNode(int val){
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->val = val;
//     newNode->next = NULL;
//     return newNode;
// }

// void insertEnd(int val){
//     struct Node* newNode = createNode(val);
//     if(head == NULL){
//         head = newNode;
//         return;
//     }
//     struct Node* temp = head;
//     while(temp->next!=NULL){
//         temp = temp->next;
//     }
//     temp->next = newNode;
// }

// void displayList(){
//     struct Node* temp = head;
//     if(temp == NULL){
//         printf("list is empty\n");
//         return;
//     }
//     while(temp!=NULL){
//         printf("%d ",temp->val);
//         temp=temp->next;
//     }
//     printf("\n");
// }

// int main(){
//     displayList();
//     insertEnd(10);
//     displayList();
//     insertEnd(200);
//     insertEnd(30);
//     displayList();
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

// Create a new node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Initialize the linked list
void initList(struct LinkedList* list) {
    list->head = NULL;
}

// Insert at the end
void insertEnd(struct LinkedList* list, int val) {
    struct Node* newNode = createNode(val);
    if (list->head == NULL) {
        list->head = newNode;
        return; 
    }
    struct Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Display the list
void displayList(struct LinkedList* list) {
    struct Node* temp = list->head;
    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

// Free all nodes
void freeList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

int main() {
    struct LinkedList list;
    initList(&list);

    displayList(&list);
    insertEnd(&list, 10);
    insertEnd(&list, 200);
    insertEnd(&list, 30);
    displayList(&list);

    freeList(&list); // Clean up
    return 0;
}
