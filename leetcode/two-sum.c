/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// Define a hash map entry structure
typedef struct {
    int key;       
    int value;     
    UT_hash_handle hh;
} HashItem;

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashItem* map = NULL; 
    int* result = (int*)malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; ++i) {
        int complement = target - nums[i];
        HashItem* item;

        HASH_FIND_INT(map, &complement, item);
        if (item != NULL) {
            result[0] = item->value;
            result[1] = i;
            *returnSize = 2;

            HASH_CLEAR(hh, map);
            return result;
        }
        item = (HashItem*)malloc(sizeof(HashItem));
        item->key = nums[i];
        item->value = i;
        HASH_ADD_INT(map, key, item);
    }
    *returnSize = 0;
    return NULL;
}