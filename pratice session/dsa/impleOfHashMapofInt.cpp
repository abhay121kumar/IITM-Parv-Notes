#include <iostream>
using namespace std;

class Map{
    private:
    struct Node{
        int key, value;
        Node* next;
        Node(int key, int value) : key(key), value(value), next(nullptr) {}
    };
    static const int size = 1000003;
    Node* arr[size];

    public:
    Map() {
        for (int i = 0; i < size; i++) {
            arr[i] = nullptr;
        }
    }

    int hash(int key) {
        return key % size;
    }

    void put(int key, int value) {
        int index = hash(key);
        Node* head = arr[index];
        Node* cur = head;

        // Check if key exists in the linked list at this index
        while (cur) {
            if (cur->key == key) {
                cur->value = value; // Update value if key exists
                return;
            }
            cur = cur->next;
        }

        // If key does not exist, add new node at the front
        Node* newNode = new Node(key, value);
        newNode->next = head;
        arr[index] = newNode;
    }

    int get(int key) {
        int index = hash(key);
        Node* cur = arr[index];

        while (cur) {
            if (cur->key == key) return cur->value;
            cur = cur->next;
        }

        return -1; // Key not found
    }
};

int main() {
    Map map;

    // Insert key-value pairs
    map.put(1, 10);
    map.put(2, 20);
    map.put(3, 30);

    // Retrieve values using keys
    cout << "Value for key 1: " << map.get(1) << endl;
    cout << "Value for key 2: " << map.get(2) << endl;
    cout << "Value for key 3: " << map.get(3) << endl;
    cout << "Value for key 4: " << map.get(4) << endl; // This will return -1

    // Update value for key 2
    map.put(2, 25);
    cout << "Updated value for key 2: " << map.get(2) << endl;

    return 0;
}
