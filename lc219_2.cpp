#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {

public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        //unordered_map & sliding windows
        if(!k) return false;
        int l=0;
        int r;
        unordered_map<int,int> val_freq;//just within the window
        for(r=0;r<=k && r<nums.size();r++){// is r<=k not r<k because from here to kth meaning size_of_windows=k+1
            val_freq[nums[r]]++;
            if(val_freq[nums[r]]>1) return true;
        }
        for(;r<nums.size();l++,r++){
            val_freq[nums[l]]--;
            val_freq[nums[r]]++;
            if(val_freq[nums[r]]>1) return true;
        }
        return false;

    }
    bool containsNearbyDuplicate_slower(vector<int>& nums, int k) {
        //unordered_map & sliding windows
        if(!k) return false;
        int l=0;
        int r;
        unordered_set<int> val;
        for(r=0;r<k && r<nums.size();r++){//if k>nums.size() -> reading garbage
            if(val.contains(nums[r])) return true;
            val.insert(nums[r]);
        }
        for(;r<nums.size();l++,r++){
            if(val.contains(nums[r])) return true;
            val.erase(nums[l]);
            val.insert(nums[r]);
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

    runTest(4,{1,4,2,3,1,2},3,true);
    runTest(5,{1,4,2,3,1,2},0,false);
    runTest(6,{1,2,3,4,5,6},15,false);
    runTest(7,{2,2},3,true);
    return 0;
}