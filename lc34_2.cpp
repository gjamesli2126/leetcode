#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return {-1, -1};
        // 1) find the first index ≥ target  (lower_bound)
        int l = 0, r = n;           // r is exclusive
        while (l < r) {
            int m = (l + r) / 2;
            if (nums[m] < target) l = m + 1;
            else r = m;
        }
        // l is now the first pos with nums[l] ≥ target
        if (l == n || nums[l] != target) return {-1, -1};
        int sol_l = l;
        // 2) find the first index > target  (upper_bound)
        l = 0;
        r = n;                      // again, r exclusive
        while (l < r) {
            int m = (l + r) / 2;
            if (nums[m] <= target) l = m + 1;         // “push” right past the last ≤ target
            else r = m;
        }
        // l is now the first pos with nums[l] > target
        int sol_r = l - 1;          // so the last pos == target is one back
        return {sol_l, sol_r};
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