#include<bits/stdc++.h>
using namespace std;
#define mainTest main
class LRUCache {
private:
    int capacity;
    unordered_map<int, int> kvmap;
    list<int> listQ;
    unordered_map<int, list<int>::iterator> iteratorMap; // New hash map to store iterators

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto itmap = kvmap.find(key);
        if (itmap == kvmap.end()) return -1;

        // Move the accessed key to the end of the list
        listQ.erase(iteratorMap[key]);
        listQ.push_back(key);
        iteratorMap[key] = --listQ.end(); // Update the iterator in the hash map

        return itmap->second;
    }

    void put(int key, int value) {
        auto itmap = kvmap.find(key);
        if (itmap != kvmap.end()) {
            itmap->second = value;
            listQ.erase(iteratorMap[key]);
            listQ.push_back(key);
            iteratorMap[key] = --listQ.end(); // Update the iterator in the hash map
            return;
        }

        // If key not found and cache is full, remove the least recently used item
        if (kvmap.size() == capacity) {
            int listFront = listQ.front();
            kvmap.erase(listFront);
            iteratorMap.erase(listFront); // Remove the iterator from the hash map
            listQ.pop_front();
        }

        kvmap[key] = value;
        listQ.push_back(key);
        iteratorMap[key] = --listQ.end(); // Store the iterator in the hash map
    }
};

int mainTest() {
    vector<string> commands = {"LRUCache","put","put","put","put","get","get","get","get","put","get","get","get","get","get"};
    vector<vector<int>> inputs = {{3},{1,1},{2,2},{3,3},{4,4},{4},{3},{2},{1},{5,5},{1},{2},{3},{4},{5}};
    vector<int> expected = {0,0,0,0,0,4,3,2,-1,0,-1,2,3,-1,5}; // The first three are null (0 for representation)

    LRUCache* cache = nullptr;

    for (int i = 0; i < commands.size(); i++) {
        if (commands[i] == "LRUCache") {
            cache = new LRUCache(inputs[i][0]);
            cout << "Created an LRUCache with capacity: " << inputs[i][0] << endl;
        } else if (commands[i] == "put") {
            cache->put(inputs[i][0], inputs[i][1]);
            cout << "Put (" << inputs[i][0] << "," << inputs[i][1] << ") into the cache." << endl;
        } else if (commands[i] == "get") {
            int val = cache->get(inputs[i][0]);
            cout << "Get key " << inputs[i][0] << " : " << val << " | Expected: " << expected[i] << endl;
        }
    }

    delete cache; // Cleanup
    return 0;
}
