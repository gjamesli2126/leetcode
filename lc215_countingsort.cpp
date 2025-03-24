#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        /*time: O(3n+(max-min)), space: O(max-min)*/

        auto [min_r,max_r]= minmax_element(nums.begin(),nums.end());
        int minv=*min_r;
        int maxv=*max_r;
        vector<int> buckets(maxv-minv+1,0);
        for(int num:nums){
            int adjv=num-minv;
            buckets[adjv]++;
        }
        for(int i=maxv-minv;i>=0;i--){
            k-=buckets[i];
            if(k<=0) return i+minv;
        }
        return 0;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int k, int expected) {
    Solution sol;
    int result = sol.findKthLargest(nums, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected "
             << expected << " but got " << result << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [3,2,1,5,6,4], k = 2
    // Expected Output: 5
    runTest(1, {3, 2, 1, 5, 6, 4}, 2, 5);

    // Test Case 2:
    // Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    // Expected Output: 4
    runTest(2, {3, 2, 3, 1, 2, 4, 5, 5, 6}, 4, 4);

    return 0;
}