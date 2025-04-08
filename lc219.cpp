#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    unordered_map<int,int> vf;
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k0) {
        int r;
        int k=k0;
        for(r=0;k>=0 && r<nums.size();r++,k--){
            vf[nums[r]]++;
            if(vf[nums[r]]>1) return true;
        }
        for(;r<nums.size();r++){
            //first del
            vf[nums[r-k0-1]]--;
            //second: add
            vf[nums[r]]++;
            if(vf[nums[r]]>1) return true;
        }
        return false;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int k, bool expected) {
    Solution sol;
    bool result = sol.containsNearbyDuplicate(nums, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: containsNearbyDuplicate(nums, " << k << ") = "
             << (result ? "true" : "false")
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: containsNearbyDuplicate(nums, " << k << ") = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [1,2,3,1], k = 3
    // Expected Output: true
    runTest(1, {1,2,3,1}, 3, true);

    // Test Case 2:
    // Input: nums = [1,0,1,1], k = 1
    // Expected Output: true
    runTest(2, {1,0,1,1}, 1, true);

    // Test Case 3:
    // Input: nums = [1,2,3,1,2,3], k = 2
    // Expected Output: false
    runTest(3, {1,2,3,1,2,3}, 2, false);

    return 0;
}