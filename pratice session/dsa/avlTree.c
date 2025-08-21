// // Inserting 20 into the tree

// //           20

// // Inserting 10 into the tree

// //           20
// //      10

// // Inserting 30 into the tree

// //           20
// //      10      30

// // Inserting 5 into the tree

// //           20
// //      10      30
// //   5

// // Inserting 25 into the tree

// //           20
// //      10      30
// //   5      25


// #include <stdio.h>
// #include <stdlib.h>

// // Structure to represent each node in the AVL tree
// struct Node {
//     int key;
//     struct Node* left;
//     struct Node* right;
//     int height;
// };

// // Function to get the height of the node
// int height(struct Node* node) {
//     if (node == NULL)
//         return 0;
//     return node->height;
// }

// // Function to get the maximum of two integers
// int max(int a, int b) {
//     return (a > b) ? a : b;
// }

// // Function to create a new node with given key
// struct Node* newNode(int key) {
//     struct Node* node = (struct Node*)malloc(sizeof(struct Node));
//     node->key = key;
//     node->left = node->right = NULL;
//     node->height = 1; // New node is initially at height 1
//     return node;
// }

// // Right rotation to balance the tree
// struct Node* rightRotate(struct Node* y) {
//     struct Node* x = y->left;
//     struct Node* T2 = x->right;

//     // Perform rotation
//     x->right = y;
//     y->left = T2;

//     // Update heights
//     y->height = max(height(y->left), height(y->right)) + 1;
//     x->height = max(height(x->left), height(x->right)) + 1;

//     // Return the new root
//     return x;
// }

// // Left rotation to balance the tree
// struct Node* leftRotate(struct Node* x) {
//     struct Node* y = x->right;
//     struct Node* T2 = y->left;

//     // Perform rotation
//     y->left = x;
//     x->right = T2;

//     // Update heights
//     x->height = max(height(x->left), height(x->right)) + 1;
//     y->height = max(height(y->left), height(y->right)) + 1;

//     // Return the new root
//     return y;
// }

// // Get the balance factor of a node (left-heavy, right-heavy, or balanced)
// int getBalance(struct Node* node) {
//     if (node == NULL)
//         return 0;
//     return height(node->left) - height(node->right);
// }

// // Function to insert a node with a given key into the AVL tree
// struct Node* insert(struct Node* node, int key) {
//     // Step 1: Perform normal BST insert
//     if (node == NULL)
//         return newNode(key);

//     if (key < node->key)
//         node->left = insert(node->left, key);
//     else if (key > node->key)
//         node->right = insert(node->right, key);
//     else // Duplicates are not allowed in AVL tree
//         return node;

//     // Step 2: Update height of this ancestor node
//     node->height = max(height(node->left), height(node->right)) + 1;

//     // Step 3: Get the balance factor to check whether this node became unbalanced
//     int balance = getBalance(node);

//     // Step 4: If this node becomes unbalanced, then there are 4 cases

//     // Left Left Case
//     if (balance > 1 && key < node->left->key)
//         return rightRotate(node);

//     // Right Right Case
//     if (balance < -1 && key > node->right->key)
//         return leftRotate(node);

//     // Left Right Case
//     if (balance > 1 && key > node->left->key) {
//         node->left = leftRotate(node->left);
//         return rightRotate(node);
//     }

//     // Right Left Case
//     if (balance < -1 && key < node->right->key) {
//         node->right = rightRotate(node->right);
//         return leftRotate(node);
//     }

//     // Return the (unchanged) node pointer
//     return node;
// }

// // Function to perform an in-order traversal and display the tree structure
// void displayTree(struct Node* root, int space) {
//     if (root == NULL)
//         return;

//     // Increase the distance between levels
//     space += 10;

//     // Process right child first (because we print the tree from top to bottom)
//     displayTree(root->right, space);

//     // Print the current node after space
//     printf("\n");
//     for (int i = 10; i < space; i++)
//         printf(" ");
//     printf("%d\n", root->key);

//     // Process left child
//     displayTree(root->left, space);
// }

// // Main function to demonstrate AVL tree operations
// int main() {
//     struct Node* root = NULL;

//     // Insert nodes into the AVL tree
//     printf("Inserting 20 into the tree\n");
//     root = insert(root, 20);
//     displayTree(root, 0);

//     printf("\nInserting 10 into the tree\n");
//     root = insert(root, 10);
//     displayTree(root, 0);

//     printf("\nInserting 30 into the tree\n");
//     root = insert(root, 30);
//     displayTree(root, 0);

//     printf("\nInserting 5 into the tree\n");
//     root = insert(root, 5);
//     displayTree(root, 0);

//     printf("\nInserting 25 into the tree\n");
//     root = insert(root, 25);
//     displayTree(root, 0);

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

// Structure to represent each node in the AVL tree
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of the node
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node with the given key
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Right rotation to balance the tree
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return the new root
    return x;
}

// Left rotation to balance the tree
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return the new root
    return y;
}

// Get the balance factor of a node (left-heavy, right-heavy, or balanced)
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node with a given key into the AVL tree
struct Node* insert(struct Node* node, int key) {
    // Step 1: Perform normal BST insert
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Duplicates are not allowed in AVL tree
        return node;

    // Step 2: Update height of this ancestor node
    node->height = max(height(node->left), height(node->right)) + 1;

    // Step 3: Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // Step 4: If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to perform an in-order traversal and display the tree structure
void displayTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    // Increase the distance between levels
    space += 10;

    // Process right child first (because we print the tree from top to bottom)
    displayTree(root->right, space);

    // Print the current node after space
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    // Process left child
    displayTree(root->left, space);
}

// Function to find the node with the minimum value
struct Node* minNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with a given key
struct Node* deleteNode(struct Node* root, int key) {
    // Step 1: Perform standard BST delete
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is larger than the root's key, then it lies in the right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // If the key is the same as the root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = minNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }

    // Step 2: Update height of this ancestor node
    root->height = max(height(root->left), height(root->right)) + 1;

    // Step 3: Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(root);

    // Step 4: If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to display the menu and get user's choice
void menu() {
    printf("Choose an operation:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Insert
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2: // Delete
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3: // Display
                printf("Current tree structure:\n");
                displayTree(root, 0);
                printf("\n");
                break;
            case 4: // Exit
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
