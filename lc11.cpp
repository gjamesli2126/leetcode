#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int maxArea(vector<int>& height) {
        int len=int(height.size()),fp=0,bp=len-1;
        int area=0;
        while(fp<bp){
            area=max(area,(bp-fp)*min(height[fp],height[bp]));

            if(height[bp]>height[fp]) ++fp;
            //不能用下一個較大則移動pointer因為會被下一個叫小騙
            //面積是因為兩邊的bar 所導致 並非 下一個bar導致
            //因為此bar ＆ 下一個bar 為獨立事件 因此不會互相影響，要看self
            else --bp;
        }
        return area;
    }
};

int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<vector<int>> testCases = {
            {1, 8, 6, 2, 5, 4, 8, 3, 7}, // Example 1
            {1, 1},                      // Example 2
            // Additional custom test cases
            {4, 3, 2, 1, 4},             // Custom 1
            {1, 2, 1},                   // Custom 2
            {3, 9, 3, 4, 7, 2, 12, 6},    // Custom 3
            {1,2,4,3}
    };

    // Expected outputs for the test cases
    vector<int> expectedOutputs = {
            49,  // Example 1
            1,   // Example 2
            // Expected results for additional custom test cases
            16,  // Custom 1
            2,   // Custom 2
            45,   // Custom 3,
            4
    };

    // ANSI escape codes for colors
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the maxArea method
        int actualOutput = solution.maxArea(testCases[i]);

        // Determine if the test case passed or failed
        bool status = (actualOutput == expectedOutputs[i]);

        // Print the test results with colored Pass/Fail status at the beginning
        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << testCases[i][j] << (j < testCases[i].size() - 1 ? ", " : "");
        }
        cout << "]; ";
        cout << "Expected: " << expectedOutputs[i] << "; ";
        cout << "Actual: " << actualOutput << endl;
    }

    return 0;
}
