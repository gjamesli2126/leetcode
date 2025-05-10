#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        //using prefix sum, if 2 prefix sum has the same mod num, meaning the delta value if k*mutiplier
        //enforce has to be more then 2 num to form a subarr, assuming nums are postive, if concur negative: remainder=((sum%k)+k)%k
        if(!k || nums.size()<=1) return false;
        unordered_map<int,int> mod_i;
        mod_i[0]=-1;
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            if(!mod_i.contains(sum%k)) {
                mod_i[sum%k]=i;
                continue;
            }
            //found
            if(i-mod_i[sum%k]>=2) return true;
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