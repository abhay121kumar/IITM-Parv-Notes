
#define MAX_SIZE 50000

typedef struct {
    int left[MAX_SIZE];   
    int right[MAX_SIZE];  
    int leftSize;
    int rightSize;
} MedianFinder;

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Max-heapify up
void heapifyUpMax(int* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent] >= heap[idx]) break;
        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

// Max-heapify down
void heapifyDownMax(int* heap, int size, int idx) {
    while (2 * idx + 1 < size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = left;

        if (right < size && heap[right] > heap[left])
            largest = right;

        if (heap[idx] >= heap[largest]) break;

        swap(&heap[idx], &heap[largest]);
        idx = largest;
    }
}

// Min-heapify up
void heapifyUpMin(int* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent] <= heap[idx]) break;
        swap(&heap[parent], &heap[idx]);
        idx = parent;
    }
}

// Min-heapify down
void heapifyDownMin(int* heap, int size, int idx) {
    while (2 * idx + 1 < size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = left;

        if (right < size && heap[right] < heap[left])
            smallest = right;

        if (heap[idx] <= heap[smallest]) break;

        swap(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->leftSize = 0;
    obj->rightSize = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->leftSize == 0 || num <= obj->left[0]) {
        obj->left[obj->leftSize++] = num;
        heapifyUpMax(obj->left, obj->leftSize - 1);
    } else {
        obj->right[obj->rightSize++] = num;
        heapifyUpMin(obj->right, obj->rightSize - 1);
    }

    // Rebalance heaps
    if (obj->leftSize > obj->rightSize + 1) {
        // Move root from left to right
        obj->right[obj->rightSize++] = obj->left[0];
        heapifyUpMin(obj->right, obj->rightSize - 1);
        obj->left[0] = obj->left[--obj->leftSize];
        heapifyDownMax(obj->left, obj->leftSize, 0);
    } else if (obj->rightSize > obj->leftSize) {
        // Move root from right to left
        obj->left[obj->leftSize++] = obj->right[0];
        heapifyUpMax(obj->left, obj->leftSize - 1);
        obj->right[0] = obj->right[--obj->rightSize];
        heapifyDownMin(obj->right, obj->rightSize, 0);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->leftSize > obj->rightSize)
        return obj->left[0];
    else
        return ((double)obj->left[0] + obj->right[0]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
}


/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/