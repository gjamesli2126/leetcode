#include <bits/stdc++.h>
using namespace std;

// Custom hash function for pairs of integers
struct pair_hash {
    size_t operator()(const pair<int, int>& pair) const {
        auto hash1 = hash<int>{}(pair.first);
        auto hash2 = hash<int>{}(pair.second);
        // Use a bitwise XOR to combine the hash values
        return hash1 ^ (hash2 << 1);  // Shift hash2 to avoid collision for similar values
    }
};

int main() {
    // Create an unordered_map with a pair as the key and string as the value
    unordered_map<pair<int, int>, string, pair_hash> myMap;

    // Adding some elements to the map using {} for pair creation
    myMap[{1, 2}] = "Point 1,2";
    myMap[{3, 4}] = "Point 3,4";
    myMap[{-1, -2}] = "Point -1,-2";

    // Access and print elements from the map using {} to create the pair key
    if (myMap.find({3, 4}) != myMap.end()) {
        cout << "Found " << myMap[{3, 4}] << endl;
    } else {
        cout << "Key not found." << endl;
    }

    return 0;
}
