#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    struct PositionStatus{
        int index;
        int maxHeight;
    };
public:
    int trap(vector<int>& heights) {
        int len=int(heights.size());
        PositionStatus f{.index=0,.maxHeight=heights[0]},b{.index=len-1,.maxHeight=heights[len-1]};
        int tot=0;int ptr;
        while(f.index<b.index){
            if(f.maxHeight<b.maxHeight) {
                ++f.index;
                f.maxHeight= max(f.maxHeight,heights[f.index]);
                ptr=f.index;
            }
            else {
                --b.index;
                b.maxHeight= max(b.maxHeight,heights[b.index]);
                ptr=b.index;
            }
            tot+=max(0,min(f.maxHeight,b.maxHeight)-heights[ptr]);
        }
        return tot;
    }
};

// Brute-force method to validate the correctness of 'trap' function
int bruteForceTrap(const vector<int>& height) {
    int totalWater = 0;
    for (int i = 0; i < height.size(); ++i) {
        int leftMax = 0, rightMax = 0;
        for (int l = i; l >= 0; --l) { // Scan to the left
            leftMax = max(leftMax, height[l]);
        }
        for (int r = i; r < height.size(); ++r) { // Scan to the right
            rightMax = max(rightMax, height[r]);
        }
        totalWater += min(leftMax, rightMax) - height[i];
    }
    return totalWater;
}

int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<vector<int>> testCases = {
            {0,1,0,2,1,0,1,3,2,1,2,1},  // Example 1
            {4,2,0,3,2,5},              // Example 2
            // 10 additional custom test cases
            {1, 2, 1, 2, 1},            // Custom 1
            {3, 0, 2, 0, 4},            // Custom 2
            {0, 3, 0, 2, 0, 4},         // Custom 3
            {2, 0, 2},                  // Custom 4
            {1, 0, 2, 2, 1},            // Custom 5
            {5, 2, 5, 1, 8, 3, 4},      // Custom 6
            {9, 1, 2, 8, 6, 3, 5, 4},   // Custom 7
            {3, 5, 1, 3, 1, 5, 1, 4},   // Custom 8
            {1, 7, 8, 9, 1, 5, 2, 1, 4},// Custom 9
            {2, 1, 0, 2, 1, 0, 1, 3}    // Custom 10
    };
    // ANSI escape codes for colors
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";
    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the trap method
        int actualOutput = solution.trap(testCases[i]);

        // Validate the correctness using the brute-force method
        int expectedOutput = bruteForceTrap(testCases[i]);

        // Determine if the test case passed or failed
        bool status = (actualOutput == expectedOutput);

        // Print the test results with Pass/Fail status at the beginning
        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << testCases[i][j] << (j < testCases[i].size() - 1 ? ", " : "");
        }
        cout << "]; ";
        cout << "Expected (Brute-Force): " << expectedOutput << "; ";
        cout << "Actual: " << actualOutput << endl;
    }

    return 0;
}
