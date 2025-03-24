#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // TODO: implement your solution here
        return 0;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int k, int expected) {
    Solution sol;
    int result = sol.subarraySum(nums, k);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: subarraySum(";
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i];
            if (i < nums.size()-1)
                cout << ", ";
        }
        cout << ", " << k << ") = " << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: subarraySum(";
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i];
            if (i < nums.size()-1)
                cout << ", ";
        }
        cout << ", " << k << ") = " << result << ", expected " << expected << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [1,1,1], k = 2
    // Expected Output: 2
    runTest(1, {1, 1, 1}, 2, 2);

    // Test Case 2:
    // Input: nums = [1,2,3], k = 3
    // Expected Output: 2
    runTest(2, {1, 2, 3}, 3, 2);

    return 0;
}