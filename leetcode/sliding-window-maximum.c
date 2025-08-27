/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// Helper Deque Structure
typedef struct {
    int *data;
    int front;
    int back;
} Deque;

void initDeque(Deque *dq, int size) {
    dq->data = (int*)malloc(sizeof(int) * size);
    dq->front = 0;
    dq->back = -1;
}

int isEmpty(Deque *dq) {
    return dq->front > dq->back;
}

void pushBack(Deque *dq, int val) {
    dq->data[++dq->back] = val;
}

void popBack(Deque *dq) {
    dq->back--;
}

void popFront(Deque *dq) {
    dq->front++;
}

int front(Deque *dq) {
    return dq->data[dq->front];
}

int back(Deque *dq) {
    return dq->data[dq->back];
}

void freeDeque(Deque *dq) {
    free(dq->data);
}

// Main Function
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    *returnSize = 0;

    Deque dq;
    initDeque(&dq, numsSize);

    for (int i = 0; i < numsSize; i++) {
        if (!isEmpty(&dq) && front(&dq) <= i - k) {
            popFront(&dq);
        }
        while (!isEmpty(&dq) && nums[i] >= nums[back(&dq)]) {
            popBack(&dq);
        }
        pushBack(&dq, i);
        if (i >= k - 1) {
            result[*returnSize] = nums[front(&dq)];
            (*returnSize)++;
        }
    }

    freeDeque(&dq);
    return result;
}
