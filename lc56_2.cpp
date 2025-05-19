#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        vector<vector<int>> res={intervals.front()};
        for(int i=1;i<intervals.size();i++){
            int f=intervals[i][0];
            int s=intervals[i][1];
            if(f<=res.back()[1]) res.back()[1]=max(s,res.back()[1]);//if mergable
            else res.push_back(intervals[i]);
        }
        return res;
    }
};

// Helper function to compare two 2D vectors.
bool compareVectors(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if(a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if(a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); j++) {
            if(a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Helper function to print a 2D vector in the format: [[a,b],[c,d],...]
void printVector2D(const vector<vector<int>>& intervals) {
    cout << "[";
    for (size_t i = 0; i < intervals.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < intervals[i].size(); j++) {
            cout << intervals[i][j];
            if(j < intervals[i].size() - 1)
                cout << ",";
        }
        cout << "]";
        if(i < intervals.size() - 1)
            cout << ",";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<vector<int>> intervals, vector<vector<int>> expected) {
    Solution sol;
    vector<vector<int>> result = sol.merge(intervals);
    if (compareVectors(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: ";
        printVector2D(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected ";
        printVector2D(expected);
        cout << " but got ";
        printVector2D(result);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    // Expected Output: [[1,6],[8,10],[15,18]]
    vector<vector<int>> intervals1 = { {1,3}, {2,6}, {8,10}, {15,18} };
    vector<vector<int>> expected1 = { {1,6}, {8,10}, {15,18} };
    runTest(1, intervals1, expected1);

    // Test Case 2:
    // Input: intervals = [[1,4],[4,5]]
    // Expected Output: [[1,5]]
    vector<vector<int>> intervals2 = { {1,4}, {4,5} };
    vector<vector<int>> expected2 = { {1,5} };
    runTest(2, intervals2, expected2);

    return 0;
}