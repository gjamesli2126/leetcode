#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int l,r;
        for(l=0, r=0;r<nums.size();r++){
            if(!nums[r]) k--;
            if(k<0) k+=1-nums[l++];//see if we can give back
        }
        return r-l;
    }
};
void runTest(int testNum, vector<int> nums, int k, int expected) {
    Solution sol;
    int result = sol.longestOnes(nums, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: longestOnes(nums, " << k << ") = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: longestOnes(nums, " << k << ") = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
    // Expected Output: 6
    runTest(1, {1,1,1,0,0,0,1,1,1,1,0}, 2, 6);

    // Test Case 2:
    // Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
    // Expected Output: 10
    runTest(2, {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3, 10);

    return 0;
}