#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        //shift but do not shrink windows size
        int l,r;
        for(l=0,r=0;l<=r && r<nums.size();r++){
            if(nums[r]==0) k--;
            if(k<0){
                k+=1-nums[l];//看看是否能還回去
                l++;//維持最大 r-l 不變
            }
        }
        return r-l;//r had ++ed
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