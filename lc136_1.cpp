#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        //using ^ to cancel out each other
        int res=0;
        for(int n:nums) res^=n;
        return res;
    }
};

#define mainTest main

// Helper to run a single test case
void runTest(int testNum, const vector<int>& nums, int expected) {
    Solution sol;
    int result = sol.singleNumber(const_cast<vector<int>&>(nums));

    const string GREEN = "\033[32m", RED = "\033[31m", RESET = "\033[0m";
    if (result == expected) {
        cout << GREEN << "Test Case " << testNum << " Passed: "
             << result << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " Failed: got "
             << result << ", expected " << expected << RESET << "\n";
    }
}

int mainTest() {
    // Example 1
    runTest(1, {2,2,1}, 1);

    // Example 2
    runTest(2, {4,1,2,1,2}, 4);

    // Example 3
    runTest(3, {1}, 1);

    // Additional tests
    runTest(4, {7,3,5,4,5,3,4}, 7);
    runTest(5, {-1,-1,-2}, -2);

    return 0;
}