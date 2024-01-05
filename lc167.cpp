#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int len=int(numbers.size()),fp=0,bp=len-1;
        while(fp<bp){
            if(numbers[fp]+numbers[bp]>target) --bp;
            else if(numbers[fp]+numbers[bp]<target) ++fp;
            else{
                return {++fp,++bp};
            }
        }
        return {};
    }
};
int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<pair<vector<int>, int>> testCases = {
            {{2, 7, 11, 15}, 9},        // Example 1
            {{2, 3, 4}, 6},             // Example 2
            {{-1, 0}, -1},              // Example 3
            {{1, 2, 3, 4, 5}, 9},       // Custom 1
            {{-3, -2, -1, 0, 1}, -3},   // Custom 2
            {{100, 200, 300, 400}, 700},// Custom 3
            {{0, 0, 1, 2}, 1},          // Custom 4
            {{-5, -4, -3, -2, -1}, -9}, // Custom 5
            {{1, 1, 1, 10}, 11},        // Custom 6
            {{-100, 0, 100, 200}, 100}, // Custom 7
            {{5, 25, 75}, 100},         // Custom 8
            {{3, 24, 50, 79, 88, 150, 345}, 200},  // Custom 9
            {{-1, 3, 4, 5, 7, 10, 11}, 10}         // Custom 10
    };

    // Corrected expected outputs for the test cases
    vector<vector<int>> expectedOutputs = {
            {1, 2}, {1, 3}, {1, 2}, {4, 5}, {1, 4}, {3, 4}, {1, 3}, {1, 2}, {1, 4}, {1, 4}, {2, 3}, {3, 6}, {1, 7}
    };

    // ANSI escape codes for colors
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the twoSum method
        vector<int> actualOutput = solution.twoSum(testCases[i].first, testCases[i].second);

        // Determine if the test case passed or failed
        bool status = (actualOutput == expectedOutputs[i]);

        // Print the test results with colored Pass/Fail status at the beginning
        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: numbers = [";
        for (size_t j = 0; j < testCases[i].first.size(); ++j) {
            cout << testCases[i].first[j] << (j < testCases[i].first.size() - 1 ? ", " : "");
        }
        cout << "], target = " << testCases[i].second << "; ";
        cout << "Expected: [";
        for (const int &num : expectedOutputs[i]) {
            cout << num << (num == expectedOutputs[i].back() ? "" : ", ");
        }
        cout << "], Actual: [";
        for (const int &num : actualOutput) {
            cout << num << (num == actualOutput.back() ? "" : ", ");
        }
        cout << "]" << endl;
    }

    return 0;
}