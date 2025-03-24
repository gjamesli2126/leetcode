#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l=0;
        int r=nums.size()-1;
        nums.push_back(INT_MIN);
        while(l<=r){
            int mid=(l+r)/2;
            if(nums[mid]<nums[mid+1]) {
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        return l;
    }
};

// Helper function to check if the index is a valid peak.
bool isValidPeak(const vector<int>& nums, int idx) {
    int n = nums.size();
    if(idx < 0 || idx >= n) return false;
    if(n == 1) return true;
    if(idx == 0) return nums[0] > nums[1];
    if(idx == n - 1) return nums[n - 1] > nums[n - 2];
    return (nums[idx] > nums[idx - 1] && nums[idx] > nums[idx + 1]);
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, vector<int> nums) {
    Solution sol;
    int idx = sol.findPeakElement(nums);
    if(isValidPeak(nums, idx)) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: Peak index = " << idx << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: Returned index = " << idx
             << " is not a valid peak.\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [1,2,3,1]
    // Expected: Only valid peak is at index 2 (3 > 2 and 3 > 1)
    vector<int> nums1 = {1, 2, 3, 1};
    runTest(1, nums1);

    // Test Case 2:
    // Input: nums = [1,2,1,3,5,6,4]
    // Expected: Valid peaks are at index 1 (2) or index 5 (6). Either is acceptable.
    vector<int> nums2 = {1, 2, 1, 3, 5, 6, 4};
    runTest(2, nums2);

    return 0;
}