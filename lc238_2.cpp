#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ans(nums.size());
        //perform prefix mul
        vector<int> premul(nums.size());
        premul[0]=nums[0];
        for(int i=1;i<nums.size();++i) premul[i]=nums[i]*premul[i-1];
        //perform postfix mul
        vector<int> postmul(nums.size());
        postmul.back()=nums.back();
        for(int i=nums.size()-2;i>=0;--i){
            postmul[i]=nums[i]*postmul[i+1];

        }
        //mul pre & post
        ans[0]=postmul[1];
        ans.back()=premul[nums.size()-2];
        for(int i=1;i<nums.size()-1;++i) ans[i]=postmul[i+1]*premul[i-1];
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
