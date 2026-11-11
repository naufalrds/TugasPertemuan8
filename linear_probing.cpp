#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
    private:
    vector <int> table;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    public:
    HashTable() {
        table.resize(TABLE_SIZE, -1);
    }

    void insert(int key) {
        int index = hashFunction(key);
        
        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = key;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : " << table[i] << endl;
        }
    }
};

int main() {
    HashTable ht;

    ht.insert(23);
    ht.insert(43);
    ht.insert(13);
    ht.insert(35);

    ht.display();

    return 0;
}