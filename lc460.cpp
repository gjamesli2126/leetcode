#include <iostream>
#include <list>
#include <unordered_map>
#include <map>
using namespace std;

class LFUCache {
private:
    struct KeyNode {
        int key;
        list<int>::iterator it; // Iterator to this key's position in the freq list
    };

    unordered_map<int, int> kvmap; // Key-Value map
    unordered_map<int, int> kfmap; // Key-Frequency map
    map<int, list<int>> fqmap; // Frequency-Keys map, using list for O(1) removal/insertion
    unordered_map<int, KeyNode> keyNodes; // Key to KeyNode (for fast access and updates)
    int capacity;

    void removeKeyFreq(int key) {
        if (kfmap.find(key) != kfmap.end()) {
            int freq = kfmap[key];
            fqmap[freq].erase(keyNodes[key].it); // O(1) erase
            if (fqmap[freq].empty()) {
                fqmap.erase(freq);
            }
        }
    }

    void addKeyFreq(int key) {
        removeKeyFreq(key); // Remove the key from its current frequency list
        int freq = kfmap[key] + 1; // Increase the key's frequency
        kfmap[key] = freq; // Update the key's frequency
        fqmap[freq].push_front(key); // Add the key to the front of the new frequency list
        keyNodes[key] = {key, fqmap[freq].begin()}; // Update or create the KeyNode
    }

public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (kvmap.find(key) == kvmap.end()) return -1;
        addKeyFreq(key); // Increment the frequency of the key
        return kvmap[key];
    }

    void put(int key, int value) {
        if (capacity <= 0) return;
        if (kvmap.find(key) == kvmap.end() && kvmap.size() == capacity) {
            // Evict the least frequently used key
            int lfuKey = (fqmap.begin()->second).back(); // Least recently used in the least freq list
            removeKeyFreq(lfuKey);
            kvmap.erase(lfuKey);
            kfmap.erase(lfuKey);
            keyNodes.erase(lfuKey);
        }
        kvmap[key] = value; // Update or add the value for the key
        addKeyFreq(key); // Add or update the key's frequency
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
