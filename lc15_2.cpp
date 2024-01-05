#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        int len=int(nums.size());
        for(int i=0;i<len;++i){
            if(i>0 && nums[i]==nums[i-1]) continue;
            int fp=i+1,bp=len-1;
            while(fp<bp){
                if(nums[fp]+nums[bp]+nums[i]>0) --bp;
                else if(nums[fp]+nums[bp]+nums[i]<0) ++fp;
                else{
                    ans.push_back({nums[i],nums[fp],nums[bp]});
                    ++fp;
                    while(nums[fp]==nums[fp-1] && fp<bp) ++fp; //因恐重複故跳過
                }
            }
        }
        return ans;
    }
};

int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<vector<int>> testCases = {
            {-1, 0, 1, 2, -1, -4},  // Example 1
            {0, 1, 1},              // Example 2
            {0, 0, 0},              // Example 3
            {-1,0,1,2,-1,-4,-2,-3,3,0,4},
            // Additional custom test cases

    };

    // Expected outputs for the test cases
    vector<vector<vector<int>>> expectedOutputs = {
            {{-1, -1, 2}, {-1, 0, 1}}, // Example 1
            {},                        // Example 2
            {{0, 0, 0}},               // Example 3
            {{-4,0,4},{-4,1,3},{-3,-1,4},{-3,0,3},{-3,1,2},{-2,-1,3},{-2,0,2},{-1,-1,2},{-1,0,1}}
            // Expected results for additional custom test cases

    };

    // ANSI escape codes for colors
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the threeSum method
        vector<vector<int>> actualOutput = solution.threeSum(testCases[i]);

        // Sort each inner vector for consistent comparison
        for (auto &triplet : actualOutput) {
            sort(triplet.begin(), triplet.end());
        }
        sort(actualOutput.begin(), actualOutput.end());

        // Determine if the test case passed or failed
        bool status = (actualOutput == expectedOutputs[i]);

        // Print the test results with colored Pass/Fail status at the beginning
        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << testCases[i][j] << (j < testCases[i].size() - 1 ? ", " : "");
        }
        cout << "]; Expected: ";
        for (size_t j = 0; j < expectedOutputs[i].size(); ++j) {
            cout << "[";
            for (size_t k = 0; k < expectedOutputs[i][j].size(); ++k) {
                cout << expectedOutputs[i][j][k] << (k < expectedOutputs[i][j].size() - 1 ? ", " : "");
            }
            cout << "]" << (j < expectedOutputs[i].size() - 1 ? ", " : "");
        }
        cout << "; Actual: ";
        for (size_t j = 0; j < actualOutput.size(); ++j) {
            cout << "[";
            for (size_t k = 0; k < actualOutput[j].size(); ++k) {
                cout << actualOutput[j][k] << (k < actualOutput[j].size() - 1 ? ", " : "");
            }
            cout << "]" << (j < actualOutput.size() - 1 ? ", " : "");
        }
        cout << endl;
    }

    return 0;
}
