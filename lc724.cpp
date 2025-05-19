#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        //if (prefix sum==sum-me) return my index
        int sum=accumulate(nums.begin(),nums.end(),0);
        int prefixSum=0;
        for(int i=0;i<nums.size();i++){
            int remaining=sum-nums[i];
            if(prefixSum==remaining/2.0) return i;
            prefixSum+=nums[i];
        }

        return -1;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, vector<int> nums, int expected) {
    Solution sol;
    int result = sol.pivotIndex(nums);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: pivotIndex(";
        printVector(nums);
        cout << ") = " << result << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: pivotIndex(";
        printVector(nums);
        cout << ") = " << result << ", expected " << expected
             << "\033[0m\n";
    }
}

int testMain() {
    // Example 1
    // nums = [1,7,3,6,5,6] -> 3
    runTest(1, {1,7,3,6,5,6}, 3);

    // Example 2
    // nums = [1,2,3] -> -1
    runTest(2, {1,2,3}, -1);

    // Example 3
    // nums = [2,1,-1] -> 0
    runTest(3, {2,1,-1}, 0);
    runTest(4,{-1,-1,-1,-1,-1,-1},-1);

    return 0;
}