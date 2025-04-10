#include <iostream>
#include <list>
#include <vector>
using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<int>> table;
    vector <int> table1;

public:
    // HashTable() : table(TABLE_SIZE) {}

    HashTable() : table1(TABLE_SIZE, -1) {}

    int hashFunction(int key)
    {
        return key % TABLE_SIZE;
    }
  

    int quadraticProbe(int index, int attempt)
    {
        return (index + attempt * attempt) % TABLE_SIZE;
    }

    void insert(int key)            //for quadratic probing
    {
        int index = hashFunction(key);
        int attempt = 0;
        while (table1[index] != -1) {
            attempt++;
            index = quadraticProbe(hashFunction(key), attempt);
        }

        table1[index] = key;
    }

    bool search(int key)            //for quadratic probing
    {
        int index = hashFunction(key);
        int attempt = 0;
        while (table1[index] != -1) {
            if (table1[index] == key) {
                return true;
            }
            attempt++;
            index = quadraticProbe(hashFunction(key), attempt);
        }

        return false;
    }
    void remove(int key)                 //for quadratic probing
    {
        int index = hashFunction(key);
        int attempt = 0;

        // Quadratic probing to find and remove the key
        while (table1[index] != -1) {
            if (table1[index] == key) {
                table1[index] = -1; // Mark the slot as empty to indicate removal
                return;
            }
            attempt++;
            index = quadraticProbe(hashFunction(key), attempt);
        }
    }
    void display()             //for linear probing
    {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Index " << i << ": " << table1[i] << std::endl;
        }
    }
};

int main() {
    HashTable hashTable;

    hashTable.insert(10);
    hashTable.insert(20);
    hashTable.insert(30);
    hashTable.insert(15);
    hashTable.insert(55);

    std::cout << "Hash Table contents after insertion:" << std::endl;
    hashTable.display();

    int keyToSearch = 20;
    if (hashTable.search(keyToSearch))
    {
        cout << "Key " << keyToSearch << " found in the hash table." << std::endl;
    }
    else
    {
        cout << "Key " << keyToSearch << " not found in the hash table." << std::endl;
    }

    int keyToRemove = 55;
    hashTable.remove(keyToRemove);

    cout << "Hash Table contents after removal of key " << keyToRemove << ":" << std::endl;
    hashTable.display();

    return 0;
}
