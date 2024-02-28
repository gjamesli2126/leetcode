#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
private:
    unordered_set<int> numSet;
public:
    int longestConsecutive(vector<int>& nums) {
        int longest=0;
        numSet.insert(nums.begin(),nums.end());
        for(const int n:nums){
            //找第一個num of continuous
            //meaning processed || not the smallest
            if(!numSet.contains(n) || numSet.contains(n-1)) continue;
            int nx;
            for(nx=1;numSet.contains(n+nx);++nx){
                numSet.erase(n+nx);
            }
            longest=max(longest,nx);
        }
        return longest;
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
