#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<char,int> cfmap;
public:
    int firstUniqChar(const string_view& s);
};
int Solution::firstUniqChar(const string_view& s) {
    for(const char c:s){
        cfmap[c]++;
    }
    for(int i=0;i<s.length();++i){
        if(cfmap[s[i]]==1) return i;
    }
    return -1;
}
void printTestResult(int testNum, int expected, int actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: " << expected << ", Actual: " << actual << endl;
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    int failedTests = 0;
    int totalTests = 0;

    // Test 1
    {
        Solution sol;
        string s = "leetcode";
        int expected = 0;
        int actual = sol.firstUniqChar(s);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        string s = "loveleetcode";
        int expected = 2;
        int actual = sol.firstUniqChar(s);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 3
    {
        Solution sol;
        string s = "aabb";
        int expected = -1;
        int actual = sol.firstUniqChar(s);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for 0% error rate
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for >0% error rate
    }
    cout << endl;

    return 0;
}
