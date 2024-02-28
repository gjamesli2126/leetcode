#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int fp=0,bp=0;
        int maxLen=0;
        unordered_set<char> subStr;
        while(bp<s.length()){
            if(!subStr.contains(s[bp])){
                subStr.insert(s[bp]);
                ++bp;
                maxLen=max(bp-fp,maxLen);
                continue;
            }
            subStr.erase(s[fp]);
            ++fp;
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
