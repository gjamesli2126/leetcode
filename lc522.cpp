#include <bits/stdc++.h>
using namespace std;

#define mainTest main

class Solution {
public:
    int findLUSlength(vector<string>& strs) {

    }
};
int mainTest() {
    Solution sol;

    vector<string> strs;

    // Test case 1
    strs = {"aba", "cdc", "eae"};
    cout << sol.findLUSlength(strs) << " (expected 3)" << endl;

    // Test case 2
    strs = {"aaa", "aaa", "aa"};
    cout << sol.findLUSlength(strs) << " (expected -1)" << endl;

    // Test case 3
    strs = {"abc", "ab", "a"};
    cout << sol.findLUSlength(strs) << " (expected 3)" << endl;

    // Test case 4
    strs = {"abcd", "abcd", "abc"};
    cout << sol.findLUSlength(strs) << " (expected -1)" << endl;

    // Test case 5
    strs = {"a", "b"};
    cout << sol.findLUSlength(strs) << " (expected 1)" << endl;

    return 0;
}