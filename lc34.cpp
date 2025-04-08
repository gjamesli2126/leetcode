#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return {-1,-1};
        int l=0;
        int r=nums.size()-1;
        int lower_ind=-1;//,higher_ind=-1;
        //bin search 1st time to find the lower bound
        while(l<=r){
            int mid=(l+r)/2;
            if(nums[mid]<target) l=mid+1;
            else if(nums[mid]>=target) r=mid-1;
        }
        if(l>=nums.size() || nums[l]!=target) return {-1,-1};
        lower_ind=l;
        r=nums.size()-1;
        l=0;
        //bin search 2nd time to find the upper bound
        while(l<=r){
            int mid=(l+r)/2;
            if(nums[mid]<=target) l=mid+1;
            else if(nums[mid]>target) r=mid-1;
        }
        return {lower_ind,r};
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