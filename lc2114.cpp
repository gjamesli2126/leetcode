#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int mostWordsFound(vector<string>& sentences);
};
int Solution::mostWordsFound(vector<std::string> &sentences) {
    //find the space number;
    int maxSpace=0;
    for(const string& s:sentences){
        int count=count_if(s.begin(),s.end(),[](char c){return c==' ';});
        maxSpace= max(count,maxSpace);
    }
    return maxSpace+1;
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
        vector<string> sentences = {"alice and bob love leetcode", "i think so too", "this is great thanks very much"};
        int expected = 6;
        int actual = sol.mostWordsFound(sentences);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        vector<string> sentences = {"please wait", "continue to fight", "continue to win"};
        int expected = 3;
        int actual = sol.mostWordsFound(sentences);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Add more test cases here

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
