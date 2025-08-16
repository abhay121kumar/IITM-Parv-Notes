#include<stdio.h>
#include <stdlib.h>
struct Node{
  int val;
  struct Node* next1;
  struct Node* next2;
};

struct Node* head = NULL;
struct Node* createNode(int val){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->next1 = NULL;
    newNode->next2 = NULL;
    return newNode;
}

void insertEnd(int val){
    struct Node* newNode = createNode(val);
    if(head==NULL){
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while(temp->next2!=NULL){
        temp = temp->next2; 
    }
    temp->next2 = newNode;
    newNode->next1 = temp;
    return;
}

void displayForward(){
    if(head==NULL){
        printf("no list is there\n");
        return ;
    }
    struct Node* temp = head;
    while(temp){
        printf("%d ",temp->val);
        temp = temp->next2;
    }
    printf("\n");
    return ;
}
void displayBackward(){
    if(head==NULL){
        printf("no list is there\n");
        return ;
    }
    struct Node* temp = head;
    while(temp->next2!=NULL){
        temp = temp->next2;
    }
    while(temp){
        printf("%d ",temp->val);
        temp = temp->next1;
    }
    printf("\n");
    return ;
}
int main(){
    insertEnd(2);
    insertEnd(3);
    displayForward();
    displayBackward();
    return 0;
}