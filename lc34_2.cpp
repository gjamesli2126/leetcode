#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return {-1,-1};
        int l,r,m;
        //find lower bounder via bin-search
        l=0,r=nums.size()-1;
        int sol_l=-1;
        while(l<r){
            m=l+(r-l)/2;
            if(nums[m]<target) l=m+1;
            else r=m;
        }
        if(nums[l]!=target) return {-1,-1};
        sol_l=l;
        //find upper bounder via bin-search
        l=0,r=nums.size()-1;
        while(l<r){
            m=l+(r-l+1)/2;//right bias
            if(nums[m]>target) r=m-1;
            else l=m;
        }

        return {sol_l,l};
    }
};

void runTest(int testNum, vector<int> nums, int target, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.searchRange(nums, target);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: searchRange(nums, " << target << ") = [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size() - 1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: searchRange(nums, " << target << ") = [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size() - 1 ? ", " : "");
        }
        cout << "], expected [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size() - 1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [5,7,7,8,8,10], target = 8
    // Expected Output: [3,4]
    runTest(1, {5,7,7,8,8,10}, 8, {3,4});

    // Test Case 2:
    // Input: nums = [5,7,7,8,8,10], target = 6
    // Expected Output: [-1,-1]
    runTest(2, {5,7,7,8,8,10}, 6, {-1,-1});

    // Test Case 3:
    // Input: nums = [], target = 0
    // Expected Output: [-1,-1]
    runTest(3, {}, 0, {-1,-1});

    runTest(4, {2,2},3, {-1,-1});

    return 0;
}