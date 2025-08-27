/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAXVAL 20002 

int bit[MAXVAL];

int lowbit(int x) {
    return x & (-x);
}

void update(int index) {
    while (index < MAXVAL) {
        bit[index]++;
        index += lowbit(index);
    }
}

int query(int index) {
    int sum = 0;
    while (index > 0) {
        sum += bit[index];
        index -= lowbit(index);
    }
    return sum;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* res = (int*)malloc(sizeof(int) * numsSize);
    memset(bit, 0, sizeof(bit));

    for (int i = numsSize - 1; i >= 0; i--) {
        int index = nums[i] + 10001; // shift to positive range
        res[i] = query(index - 1);   // count of smaller elements
        update(index);              // insert into BIT
    }

    *returnSize = numsSize;
    return res;
}