/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct ListNode* findMiddle(struct ListNode* head, struct ListNode** prev) {
    struct ListNode *slow = head, *fast = head;
    *prev = NULL;

    while (fast && fast->next) {
        *prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (!head) return NULL;

    if (!head->next) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = head->val;
        node->left = node->right = NULL;
        return node;
    }

    struct ListNode* prev = NULL;
    struct ListNode* mid = findMiddle(head, &prev);


    if (prev) prev->next = NULL;


    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = mid->val;
    root->left = sortedListToBST((mid == head) ? NULL : head);
    root->right = sortedListToBST(mid->next);

    return root;
}