#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {

    }
};

// Helper to compare two lists of ranges
bool equalRanges(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Helper to print ranges
void printRanges(const vector<vector<int>>& ranges) {
    cout << "[";
    for (size_t i = 0; i < ranges.size(); ++i) {
        cout << "[" << ranges[i][0] << "," << ranges[i][1] << "]";
        if (i + 1 < ranges.size()) cout << ",";
    }
    cout << "]";
}

// Helper to run a test case
void runTest(int testNum,
             vector<int> nums,
             int lower,
             int upper,
             vector<vector<int>> expected) {
    Solution sol;
    auto result = sol.findMissingRanges(nums, lower, upper);
    if (equalRanges(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: ";
        printRanges(expected);
        cout << "\nGot:      ";
        printRanges(result);
        cout << "\n";
    }
}

int testMain(){
    // Example 1:
    // nums = [0,1,3,50,75], lower = 0, upper = 99
    // Output: [[2,2],[4,49],[51,74],[76,99]]
    runTest(1,
            {0,1,3,50,75},
            0, 99,
            {{2,2},{4,49},{51,74},{76,99}}
    );

    // Example 2:
    // nums = [-1], lower = -1, upper = -1
    // Output: []
    runTest(2,
            {-1},
            -1, -1,
            {}
    );

    return 0;
}