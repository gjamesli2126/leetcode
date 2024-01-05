#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //store all shits in set
        int maxCont=0;
        unordered_set<int> numPool(nums.begin(),nums.end());
        for(const int& n:nums){
            if(!numPool.contains(n) ||numPool.contains(n-1)) continue;
            //if is head
            int nx=1;
            while(numPool.contains(n+nx)){
                numPool.erase(n+nx);
                ++nx;
            }
            maxCont=max(maxCont,nx);
        }
        return maxCont;
    }
};

int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<pair<vector<int>, int>> testCases = {
            {{100, 4, 200, 1, 3, 2}, 4},         // Example 1
            {{0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, 9}, // Example 2
            // Additional test cases
            {{}, 0},                             // Empty array
            {{1, 2, 2, 3}, 3},                   // Consecutive with duplicates
            {{9, 1, 4, 7, 3, -2, 0, 5, 8, -1, 6}, 7} // Non-consecutive mix
    };

    // ANSI escape codes for colors
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the longestConsecutive method
        int actualOutput = solution.longestConsecutive(testCases[i].first);

        // Determine if the test case passed or failed
        bool status = (actualOutput == testCases[i].second);

        // Print the test results with colored Pass/Fail status at the beginning
        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: [";
        for (size_t j = 0; j < testCases[i].first.size(); ++j) {
            cout << testCases[i].first[j] << (j < testCases[i].first.size() - 1 ? ", " : "");
        }
        cout << "]; ";
        cout << "Expected: " << testCases[i].second << "; ";
        cout << "Actual: " << actualOutput << endl;
    }

    return 0;
}
