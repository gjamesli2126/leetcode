#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // if prefix_sum[j]%k == prefix_sum[i]%k Then between (i+1)~j is the good subarray
        //remember 0 is k's mutiplee
//        unordered_map<int,vector<int>> modmp;//mod_val,{indices,.....}
        unordered_map<int,int> modmp;//只要>2有就好
        modmp[0]=-1;
        //step1 calc prefix sum
        for(int i=1;i<nums.size();i++) nums[i]+=nums[i-1];
        //step2 calc prefix remainder
        for(int i=0;i<nums.size();i++) {
            nums[i] %= k;
            if(modmp.contains(nums[i])){
                if(i-modmp[nums[i]]+1>2) return true;//[from 'i+1' to 'j' needs to have >=2 so j-(i+1)+1>=2]
            }else modmp[nums[i]]=i;
        }


        return false;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int k, bool expected) {
    Solution sol;
    bool result = sol.checkSubarraySum(nums, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: checkSubarraySum(nums, " << k << ") = "
             << (result ? "true" : "false")
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: checkSubarraySum(nums, " << k << ") = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [23,2,4,6,7], k = 6
    // Expected Output: true
    runTest(1, {23,2,4,6,7}, 6, true);

    // Test Case 2:
    // Input: nums = [23,2,6,4,7], k = 6
    // Expected Output: true
    runTest(2, {23,2,6,4,7}, 6, true);

    // Test Case 3:
    // Input: nums = [23,2,6,4,7], k = 13
    // Expected Output: false
    runTest(3, {23,2,6,4,7}, 13, false);
    runTest(4, {2,4,3}, 6, true);
    return 0;
}