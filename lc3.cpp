#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int fPtr=0,bPtr;
        unordered_set<char> subStr;
        int maxLen=0;
        int sLen=int(s.length());
        for(bPtr=0;bPtr<sLen;++bPtr){
            char c=s[bPtr];//set does not support storing reference
            while(subStr.contains(c)) subStr.erase(s[fPtr++]);
            subStr.insert(c);
            maxLen=max(int(subStr.size()), maxLen);
        }
        return maxLen;
    }
};

int mainTest() {
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "[Pass] ";
        } else {
            cout << RED << "[Fail] ";
        }
        cout << RESET << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
    };

    Solution solution;

    struct TestCase {
        string s;
        int expected;
    };

    vector<TestCase> testCases = {
            {"abcabcbb", 3},  // Test case 1
            {"bbbbb", 1},     // Test case 2
            {"pwwkew", 3},    // Test case 3
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.lengthOfLongestSubstring(testCases[i].s);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
