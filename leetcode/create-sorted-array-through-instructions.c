#define MAX_VAL 100001
#define MOD 1000000007

int bit[MAX_VAL + 2];

void update(int index, int value) {
    while (index <= MAX_VAL) {
        bit[index] += value;
        index += index & -index;
    }
}

int query(int index) {
    int result = 0;
    while (index > 0) {
        result += bit[index];
        index -= index & -index;
    }
    return result;
}

int createSortedArray(int* instructions, int instructionsSize) {
    // Clear BIT before use
    for (int i = 0; i <= MAX_VAL; i++) bit[i] = 0;

    long cost = 0;

    for (int i = 0; i < instructionsSize; i++) {
        int num = instructions[i];
        int less = query(num - 1);
        int greater = i - query(num);  // i is number of elements already inserted
        cost = (cost + (less < greater ? less : greater)) % MOD;
        update(num, 1);
    }

    return (int)cost;
}