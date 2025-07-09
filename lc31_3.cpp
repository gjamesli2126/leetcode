#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.size()<=1) return;
        //find the pivot point fn the back
        int ns=nums.size();
        for(int i=ns-1;i>0;i--){
            if(nums[i-1]>=nums[i]) continue;
            for(int j=ns-1;j>=i;j--){
                if(nums[j]<=nums[i-1]) continue;//find te first num larger then nums[i-1]
                swap(nums[i-1],nums[j]);
                reverse(nums.begin()+i,nums.end());
                return;

            }
        }
        //if it is the largest->turn to the smalles
        reverse(nums.begin(),nums.end());
    }
};
void runTest(int testNum, vector<int> nums, vector<int> expected) {
    Solution sol;
    sol.nextPermutation(nums);

    if (nums == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: nextPermutation(";
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << (i < nums.size()-1 ? ", " : "");
        }
        cout << ") = [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: nextPermutation(";
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << (i < nums.size()-1 ? ", " : "");
        }
        cout << ") = [";
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << (i < nums.size()-1 ? ", " : "");
        }
        cout << "], expected [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [1,2,3]
    // Expected Output: [1,3,2]
    runTest(1, {1, 2, 3}, {1, 3, 2});

    // Test Case 2:
    // Input: nums = [3,2,1]
    // Expected Output: [1,2,3]
    runTest(2, {3, 2, 1}, {1, 2, 3});

    // Test Case 3:
    // Input: nums = [1,1,5]
    // Expected Output: [1,5,1]
    runTest(3, {1, 1, 5}, {1, 5, 1});
    runTest(10, {1, 5, 1}, {5, 1, 1});
    runTest(4,{1, 4, 7, 5, 3, 2, 2},{1, 5, 2, 2, 3, 4, 7});
    return 0;
}