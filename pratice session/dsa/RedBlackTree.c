#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node* root = NULL;

// Function prototypes
Node* createNode(int data);
void rotateLeft(Node** root, Node* x);
void rotateRight(Node** root, Node* x);
void fixInsert(Node** root, Node* z);
void insert(Node** root, int data);
void inorder(Node* root);
Node* search(Node* root, int data);
void deleteNode(Node** root, int data);
void fixDelete(Node** root, Node* x);
Node* minValueNode(Node* node);
void transplant(Node** root, Node* u, Node* v);
void menu();

#define RED_STR "R"
#define BLACK_STR "B"

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // New node is always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void rotateLeft(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rotateRight(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;

    if (!y->parent)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void fixInsert(Node** root, Node* z) {
    while (z->parent && z->parent->color == RED) {
        Node* grandparent = z->parent->parent;
        if (z->parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(root, grandparent);
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(root, grandparent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insert(Node** root, int data) {
    Node* newNode = createNode(data);
    Node* y = NULL;
    Node* x = *root;

    while (x) {
        y = x;
        if (data < x->data)
            x = x->left;
        else if (data > x->data)
            x = x->right;
        else {
            printf("Duplicate values not allowed!\n");
            free(newNode);
            return;
        }
    }

    newNode->parent = y;

    if (!y)
        *root = newNode;
    else if (data < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    fixInsert(root, newNode);
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? RED_STR : BLACK_STR);
        inorder(root->right);
    }
}

Node* search(Node* root, int data) {
    if (!root || root->data == data)
        return root;
    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Helper for delete
Node* minValueNode(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

void transplant(Node** root, Node* u, Node* v) {
    if (!u->parent)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

void fixDelete(Node** root, Node* x) {
    while (x != *root && (!x || x->color == BLACK)) {
        Node* w;
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left)
                        w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right)
                    w->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = *root;
            }
        } else {
            w = x->parent->left;
            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }
            if ((!w->right || w->right->color == BLACK) &&
                (!w->left || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right)
                        w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left)
                    w->left->color = BLACK;
                rotateRight(root, x->parent);
                x = *root;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

void deleteNode(Node** root, int data) {
    Node* z = search(*root, data);
    if (!z) {
        printf("Node not found!\n");
        return;
    }

    Node* y = z;
    Color y_original_color = y->color;
    Node* x = NULL;

    if (!z->left) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x)
                x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK)
        fixDelete(root, x);
}
void printTree(Node* root, int space) {
    if (root == NULL)
        return;

    const int COUNT = 10;
    space += COUNT;

    // Print right subtree first
    printTree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d(%s)\n", root->data, root->color == RED ? "R" : "B");

    // Print left subtree
    printTree(root->left, space);
}

// Menu
void menu() {
    int choice, val;
    while (1) {
        printf("\n--- Red Black Tree Menu ---\n");
        printf("1. Insert\n");
       
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display (Inorder with Color)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(&root, val);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                deleteNode(&root, val);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                Node* found = search(root, val);
                if (found)
                    printf("Found %d (%s)\n", found->data, found->color == RED ? RED_STR : BLACK_STR);
                else
                    printf("Value not found!\n");
                break;

            case 4:
                printf("Tree structure (sideways):\n");
                printTree(root, 0);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
int main() {
    menu();
    return 0;
}
