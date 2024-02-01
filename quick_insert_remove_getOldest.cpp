#include<bits/stdc++.h>
using namespace std;

class CustomDataStructure {
private:
    list<int> elelist; // double-linked-list to keep track of the elements' insertion order & remove w/ O(1)
    unordered_map<int,list<int>::iterator> eimap; // element-> element_iter

public:
    CustomDataStructure() {}

    void insert(int val) {
        if(eimap.contains(val)) return;//ignore
        elelist.emplace_back(val);
        eimap[val]=--elelist.end();//get the last iter
    }

    bool remove(int val) {
        if(!eimap.contains(val)) return false;
        elelist.erase(eimap[val]);//erase input iter, remove input all fit elem
        eimap.erase(val);
        return true;
    }

    int getOldest() {
        if(elelist.empty()) return -1;
        return *elelist.begin();
    }
};


bool checkResult(const string& testName, int expected, int got) {
    if (expected == got) {
        cout << "\x1B[32m" << testName << " Pass\033[0m: Expected: " << expected << ", Got: " << got << endl;
        return true;
    } else {
        cout << "\x1B[31m" << testName << " Fail\033[0m: Expected: " << expected << ", Got: " << got << endl;
        return false;
    }
}

int main() {
    CustomDataStructure ds;
    int passCount = 0;
    int totalTests = 10;

    // Test Case 1: Simple insertion and getOldest
    ds.insert(1);
    passCount += checkResult("Test Case 1", 1, ds.getOldest());

    // Test Case 2: Multiple insertions
    ds.insert(2);
    ds.insert(3);
    passCount += checkResult("Test Case 2", 1, ds.getOldest());

    // Test Case 3: Insertion and removal
    ds.remove(1);
    passCount += checkResult("Test Case 3", 2, ds.getOldest());

    // Test Case 4: Remove non-existing element
    bool removeResult = ds.remove(4); // Should return false
    passCount += checkResult("Test Case 4", false, removeResult);

    // Test Case 5: Remove oldest
    ds.remove(2);
    passCount += checkResult("Test Case 5", 3, ds.getOldest());

// Test Case 6: Re-insertion of a removed element
    ds.insert(4);
    ds.remove(4);
    ds.insert(4);
    passCount += checkResult("Test Case 6", 3, ds.getOldest());

// Test Case 7: Inserting multiple new elements and removing the oldest
    ds.insert(5);
    ds.insert(6);
    ds.remove(3); // Removing the current oldest
    passCount += checkResult("Test Case 7", 4, ds.getOldest());

// Test Case 8: Clearing the structure and adding new elements
    ds.remove(4);
    ds.remove(5);
    ds.remove(6);
    ds.insert(7);
    passCount += checkResult("Test Case 8", 7, ds.getOldest());

// Test Case 9: Inserting, removing, and checking an empty structure
    ds.remove(7);
    int oldestAfterClear = ds.getOldest(); // Expecting -1 for an empty structure
    passCount += checkResult("Test Case 9", -1, oldestAfterClear);

// Test Case 10: Complex operations with multiple insertions and removals
    ds.insert(8);
    ds.insert(9);
    ds.insert(10);
    ds.remove(9);
    ds.insert(11);
    passCount += checkResult("Test Case 10", 8, ds.getOldest());

    // Display the final pass rate
    if (passCount == totalTests) {
        cout << "\x1B[94mAll Tests Passed (" << passCount << "/" << totalTests << ")\033[0m" << endl;
    } else {
        cout << "\x1B[33m" << passCount << " out of " << totalTests << " Tests Passed\033[0m" << endl;
    }

    return 0;
}