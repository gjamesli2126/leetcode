#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        //sort by from
        auto cmp_from=[](const vector<int>& v1,const vector<int>& v2){
            return v1[1]<v2[1];//return true then a comes BEFORE b
        };
        sort(trips.begin(),trips.end(),cmp_from);
        //push to drop-off queue(on board at this time)

        auto cmp_dropoff=[](const vector<int>& v1,const vector<int>& v2){
            return v1[2]>v2[2];//return true if smaller, return true meaning b will be pop first
        };
        priority_queue<vector<int>,vector<vector<int>>, decltype(cmp_dropoff)> minHeap;
        int onBoard=0;
        for(const vector<int>& trip:trips){
            int req=trip[0];
            int from=trip[1];
            int to_exclusive=trip[2];
            //drop off everyone that the prev_end<=this_from
            while(!minHeap.empty() && minHeap.top()[2]<=from) {
                onBoard-=minHeap.top()[0];
                minHeap.pop();
            }
            onBoard+=req;
            if(onBoard>capacity) return false;
            minHeap.push(trip);
        }

        return true;
    }
};

void printTrips(const vector<vector<int>>& trips) {
    cout << "[";
    for (size_t i = 0; i < trips.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < trips[i].size(); ++j) {
            cout << trips[i][j] << (j + 1 < trips[i].size() ? ", " : "");
        }
        cout << "]" << (i + 1 < trips.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, vector<vector<int>> trips, int capacity, bool expected) {
    Solution sol;
    bool result = sol.carPooling(trips, capacity);
    const string PASS = "\033[32m", FAIL = "\033[31m", RESET = "\033[0m";
    cout << "Test Case " << testNum << ": carPooling(";
    printTrips(trips);
    cout << ", " << capacity << ") = ";
    cout << boolalpha << result;
    if (result == expected) {
        cout << " " << PASS << "PASS" << RESET << "\n";
    } else {
        cout << " " << FAIL << "FAIL (expected " << boolalpha << expected << ")" << RESET << "\n";
    }
}

int testMain() {
    // Example 1
    // trips = [[2,1,5],[3,3,7]], capacity = 4 -> false
    runTest(1, {{2,1,5}, {3,3,7}}, 4, false);

    // Example 2
    // trips = [[2,1,5],[3,3,7]], capacity = 5 -> true
    runTest(2, {{2,1,5}, {3,3,7}}, 5, true);

    // Additional tests
    // Single trip exactly fits capacity
    runTest(3, {{5,0,5}}, 5, true);
    // Overlapping trips exceed capacity at peak
    runTest(4, {{2,0,4}, {4,2,6}, {1,5,7}}, 5, false);
    // Non-overlapping trips always okay
    runTest(5, {{3,0,2}, {2,2,5}, {4,5,8}}, 4, true);

    runTest(6,{{9,3,6},{8,1,7},{6,6,8},{8,4,9},{4,2,9}},28,false);
    return 0;
}