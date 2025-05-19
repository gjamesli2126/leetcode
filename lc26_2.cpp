#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int overwriteThis=0;
        int scout;
        for(scout=0;scout<nums.size();scout++){
            if(nums[overwriteThis]==nums[scout]) continue;
            nums[++overwriteThis]=nums[scout];//直接往下一個覆寫
        }
        return overwriteThis+1;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int expectedK, vector<int> expectedNums) {
    Solution sol;
    int k = sol.removeDuplicates(nums);
    bool pass = true;
    if (k != expectedK) pass = false;
    for (int i = 0; i < expectedK && pass; ++i) {
        if (nums[i] != expectedNums[i]) pass = false;
    }
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: k = " << k << ", nums = [";
        for (int i = 0; i < expectedK; ++i) {
            cout << nums[i] << (i + 1 < expectedK ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: got k = " << k << ", nums = [";
        for (int i = 0; i < expectedK && i < nums.size(); ++i) {
            cout << nums[i] << (i + 1 < expectedK ? ", " : "");
        }
        cout << "], expected k = " << expectedK << ", nums = [";
        for (int i = 0; i < expectedK; ++i) {
            cout << expectedNums[i] << (i + 1 < expectedK ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: nums = [1,1,2]
    // Output: k = 2, nums = [1,2,...]
    runTest(1, {1,1,2}, 2, {1,2});

    // Example 2:
    // Input: nums = [0,0,1,1,1,2,2,3,3,4]
    // Output: k = 5, nums = [0,1,2,3,4,...]
    runTest(2, {0,0,1,1,1,2,2,3,3,4}, 5, {0,1,2,3,4});

    return 0;
}