#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //要把此數兩邊的數字乘在一起-> prefix 此數之前的乘機; postfix 此數之後的乘機
        int postfix=1;
        int len=int(nums.size());
        vector<int> ans(len,1);
        // store all prefix
        ans[0]=nums[0];
        for(int i=1;i<len;++i){
            ans[i]=nums[i]*ans[i-1];
        }
        //calc the postFix and mutiply by prefix
        for(int i=len-1;i>0;--i){
            ans[i]=postfix*ans[i-1];
            postfix*=nums[i];
        }
        ans[0]=postfix;
        return ans;
    }
};

int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<vector<int>> testCases = {
            {1, 2, 3, 4},       // Example 1
            {-1, 1, 0, -3, 3}   // Example 2
            // Add more test cases as needed
    };

    // Define the expected outputs for each test case
    vector<vector<int>> expectedOutputs = {
            {24, 12, 8, 6},     // Expected output for Example 1
            {0, 0, 9, 0, 0}     // Expected output for Example 2
            // Add more expected outputs as needed
    };

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the productExceptSelf method
        vector<int> actualOutput = solution.productExceptSelf(testCases[i]);

        // Determine if the test case passed or failed
        bool status = (actualOutput == expectedOutputs[i]);

        // Print the test results
        cout << "Test " << i + 1 << ": ";
        cout << "Input: nums = [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << testCases[i][j] << (j < testCases[i].size() - 1 ? ", " : "");
        }
        cout << "]; ";
        cout << "Expected: [";
        for (size_t j = 0; j < expectedOutputs[i].size(); ++j) {
            cout << expectedOutputs[i][j] << (j < expectedOutputs[i].size() - 1 ? ", " : "");
        }
        cout << "], Actual: [";
        for (size_t j = 0; j < actualOutput.size(); ++j) {
            cout << actualOutput[j] << (j < actualOutput.size() - 1 ? ", " : "");
        }
        cout << "], Status: " << (status ? "PASS" : "FAIL") << endl;
    }

    return 0;
}
