#include<iostream>
using namespace std;

class Node{
    public:
    int val;
    Node* next;
};
Node* head = NULL;
Node* createNode(int val){
    Node* newNode = new Node();
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(int val){
    Node* newNode = createNode(val);
    if(head==NULL){
        head = newNode;
        return;
    }
    Node* temp = head;
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void displayList(){
    Node* temp = head;
    if(temp == NULL){
        cout<<"list is empty"<<endl;
        return;
    }
    while(temp){
        cout<<temp->val<<" ";
        temp = temp->next;
    }
    cout<<endl;
    return ;
}
int main(){
    displayList();
    insertEnd(10);
    insertEnd(20);
    displayList();
    return 0;
}