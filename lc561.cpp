#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int sum=0;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();++i) if(i%2==0) sum+=nums[i];
        return sum;
    }
};

int mainTest() {
    vector<pair<vector<int>, int>> testCases = {
            {{1, 4, 3, 2}, 4},       // Example 1
            {{6, 2, 6, 5, 1, 2}, 9}, // Example 2
            // Add more test cases if needed
    };

    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    for (int i = 0; i < testCases.size(); ++i) {
        vector<int> nums = testCases[i].first;
        int expectedOutput = testCases[i].second;

        Solution solution; // Create a new object for each test case
        int actualOutput = solution.arrayPairSum(nums);

        bool status = (actualOutput == expectedOutput);

        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: [";
        for (size_t j = 0; j < nums.size(); ++j) {
            if (j > 0) cout << ", ";
            cout << nums[j];
        }
        cout << "]; Expected: " << expectedOutput << "; Actual: " << actualOutput << endl;
    }

    return 0;
}