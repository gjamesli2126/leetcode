#include <iostream>
using namespace std;
#define mainTest main

class SnapshotArray {
private:
    vector<vector<pair<int, int>>> histories; // Stores [snap_id, value] for each index
    int snap_id;

public:
    // Constructor
    SnapshotArray(int n) : snap_id(0) {
        histories.resize(n, vector<pair<int, int>>(1, {-1, 0}));//[,(pair1,pair2,...),]
    }

    // Set a value at the given index for the current snap_id
    void set(int index, int val) {
        // If the last recorded snap_id matches the current one, update the value
        if (histories[index].back().first == snap_id) {
            histories[index].back().second = val;
        } else {
            histories[index].emplace_back(snap_id, val);
        }
    }

    // Take a snapshot and return the current snap_id
    int snap() {
        return snap_id++;
    }

    // Get the value at a specific index and snap_id
    int get(int index, int snap_id) {
        const auto &history = histories[index];
        int left = 0, right = history.size() - 1, pos = -1;

        // Binary search to find the largest snap_id <= target snap_id
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (history[mid].first <= snap_id) {
                pos = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Return the value associated with the found snap_id
        return history[pos].second;
    }
};

void printResult(int testNumber, int actual, int expected) {
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    cout << "Test " << testNumber << ": ";
    if (actual == expected) {
        cout << green << "PASS" << reset;
    } else {
        cout << red << "FAIL" << reset << " (Expected: " << expected << ", Got: " << actual << ")";
    }
    cout << endl;
}

int mainTest() {
    SnapshotArray snapshotArray(3); // Initialize a SnapshotArray of size 3

    snapshotArray.set(0, 5);         // Set array[0] = 5
    int snapId1 = snapshotArray.snap(); // Take a snapshot, should return snap_id = 0

    snapshotArray.set(0, 6);         // Set array[0] = 6
    int snapId2 = snapshotArray.snap(); // Take another snapshot, should return snap_id = 1

    int value1 = snapshotArray.get(0, 0); // Get the value at index 0, snap_id 0
    printResult(1, value1, 5);          // Expected: 5

    int value2 = snapshotArray.get(0, 1); // Get the value at index 0, snap_id 1
    printResult(2, value2, 6);          // Expected: 6

    snapshotArray.set(1, 10);         // Set array[1] = 10
    int snapId3 = snapshotArray.snap(); // Take another snapshot, should return snap_id = 2

    int value3 = snapshotArray.get(1, 2); // Get the value at index 1, snap_id 2
    printResult(3, value3, 10);         // Expected: 10

    int value4 = snapshotArray.get(1, 1); // Get the value at index 1, snap_id 1
    printResult(4, value4, 0);          // Expected: 0 (no value was set before snap_id 1)

    return 0;
}