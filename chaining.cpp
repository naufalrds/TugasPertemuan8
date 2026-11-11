#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
    private:
    vector<list<int>> table;

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    void insert(int key) {
        int index = hashFunction(key);
        
        table[index].push_back(key);
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " ";

            // 22, 42, 62
            for (int data : table[i]) {
                cout << data << " ->";
            }

            cout << "NULL" << endl;
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