
int countWhileMerge(long* sum, int left, int right, int lower, int upper) {
    if (right - left <= 1) return 0;

    int mid = (left + right) / 2;
    int count = countWhileMerge(sum, left, mid, lower, upper) +
                countWhileMerge(sum, mid, right, lower, upper);

    int j = mid, k = mid, t = mid;
    int len = right - left;
    long* cache = (long*)malloc(sizeof(long) * len);
    int r = 0;

    for (int i = left; i < mid; ++i) {
        while (k < right && sum[k] - sum[i] < lower) k++;
        while (j < right && sum[j] - sum[i] <= upper) j++;
        count += j - k;

        // merge step
        while (t < right && sum[t] < sum[i]) {
            cache[r++] = sum[t++];
        }
        cache[r++] = sum[i];
    }

    while (t < right) cache[r++] = sum[t++];

    for (int i = 0; i < r; ++i) {
        sum[left + i] = cache[i];
    }

    free(cache);
    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* prefix = (long*)malloc(sizeof(long) * (numsSize + 1));
    prefix[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    int result = countWhileMerge(prefix, 0, numsSize + 1, lower, upper);
    free(prefix);
    return result;
}