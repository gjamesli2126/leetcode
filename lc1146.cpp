#include <iostream>
using namespace std;
#define mainTest main
/*
 * <---mid
 * Find the first occurrence (leftmost): r = mid - 1
 * Find the smallest  target ≤ value: r = mid - 1

 * mid----->
	•	Find the last occurrence (rightmost): l = mid + 1
	•	Find the largest value ≤ target: l = mid + 1

 這題是要 找 last <=target,所以是要找 right most
 * */
class SnapshotArray {
private:
    vector<vector<pair<int,int>>> hisotries;
    int snap_id;
public:
    // Constructor
    SnapshotArray(int length):snap_id(0){
        hisotries.resize(length,vector<pair<int,int>>(1,{-1,0}));//init as {-1,0} to avoid emp[ty history
    }

    // Set a value at the given index for the current snap_id
    void set(int index, int val) {
        // If the last recorded snap_id matches the current one, update the value
        auto& history=hisotries.at(index);
        auto& [last_snap_id,last_value]=history.back();
        if(last_snap_id==snap_id) last_value=val;
        else history.emplace_back(snap_id,val);
    }

    // Take a snapshot and return the current snap_id
    int snap() {
        return snap_id++;
    }

    // Get the value at a specific index and snap_id
    int get(int index, int snap_id) {
        const auto& history=hisotries.at(index);
        int l=0,r=history.size()-1,pos=-1;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(history.at(mid).first<=snap_id){
                pos=mid;
                l=mid+1;//find right most
            }else r=mid-1;
        }
        return history.at(pos).second;
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