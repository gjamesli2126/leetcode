#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //time: O(nlogn+n^2), sort: do de-dup
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        int N=nums.size();
        for(int p1=0;p1<N;p1++){
            if(p1!=0 && nums[p1]==nums[p1-1]) continue;//skip p1 duplicate
            int p2=p1+1;
            int p3=N-1;
            while(p2<p3) {
                int sum = nums[p1] + nums[p2] + nums[p3];
                if (sum < 0) p2++;
                else if (sum > 0) p3--;
                else {
                    ans.push_back({nums[p1], nums[p2++], nums[p3--]});
                    //after finding one ans, find next combinition of p2 p3 w/ fixed p1
                    while (p2 < p3 && nums[p2] == nums[p2 - 1]) p2++;
                    while (p2 < p3 && nums[p3] == nums[p3 + 1]) p3--;
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
