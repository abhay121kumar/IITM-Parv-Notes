#include <iostream>
using namespace std;

class vector {
private:
    int* arr;
    int count;
    int capacity;

    void resize(int new_capacity) {
        int* temp = new int[new_capacity];
        for (int i = 0; i < count; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        capacity = new_capacity;
    }

public:
    vector() {
        count = 0;
        capacity = 2;
        arr = new int[capacity];
    }

    void insert(int key) {
        if (count == capacity) {
            resize(capacity * 2);
        }
        arr[count++] = key;
    }

    void pop_back() {
        if (count > 0) {
            count--;
        }
    }

    int size() const {
        return count;
    }

    int& operator[](int index) {
        if (index < 0 || index >= count) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }


    void display() const {
        for (int i = 0; i < count; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~vector() {
        delete[] arr;
    }
};

int main() {
    vector v1;
    v1.insert(10);
    cout << "array size " << v1.size() << endl;
    v1.display();

    v1.insert(10);
    v1.insert(20);
    v1.insert(30);

    cout << "array size " << v1.size() << endl;
    v1.display();
    cout << v1[1]<<endl;     // accesses the first element
    v1[1] = 100;       // modifies the second element
    cout << v1[1];     // accesses the first element
    return 0;
}
