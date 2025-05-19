#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int global_max=-100000;
        int local_sum=-100000;
        for(int n:nums){
            local_sum=max(local_sum+n,n);
            global_max= max(global_max,local_sum);
        }
        return global_max;
    }
};

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, const vector<int>& nums, int expected) {
    Solution sol;
    vector<int> input = nums;  // copy since maxSubArray takes non-const ref
    int result = sol.maxSubArray(input);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: maxSubArray(";
        printVector(nums);
        cout << ") = " << result << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: maxSubArray(";
        printVector(nums);
        cout << ") = " << result << ", expected " << expected
             << "\033[0m\n";
    }
}

int testMain() {
    // Example 1
    runTest(1, {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);

    // Example 2
    runTest(2, {1}, 1);

    // Example 3
    runTest(3, {5, 4, -1, 7, 8}, 23);

    return 0;
}