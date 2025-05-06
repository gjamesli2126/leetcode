#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // TODO: Implement the Boyer–Moore Voting Algorithm (O(n) time, O(1) space)
        int count=0;
        int candidate;
        for(int n:nums){
            if(!count) candidate=n;
            if(n==candidate) count++;
            else count--;
        }
        return candidate;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int expected) {
    Solution sol;
    int result = sol.majorityElement(nums);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: majorityElement(...) = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: majorityElement(...) = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: nums = [3,2,3]
    // Output: 3
    runTest(1, {3,2,3}, 3);

    // Example 2:
    // Input: nums = [2,2,1,1,1,2,2]
    // Output: 2
    runTest(2, {2,2,1,1,1,2,2}, 2);

    return 0;
}