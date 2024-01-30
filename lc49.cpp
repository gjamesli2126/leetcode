#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<string,vector<string>> svmap;
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        for(const string& s:strs){
            string anaStr=s;
            sort(anaStr.begin(),anaStr.end());
            svmap[anaStr].emplace_back(s);
        }
        vector<vector<string>> ans;
        ans.reserve(svmap.size());
        for(auto& [_,v]:svmap){
            ans.emplace_back(v);
        }
        return ans;
    }
};

void printTestResult(int testNum, const vector<vector<string>>& expected, const vector<vector<string>>& actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: ";
        for (const auto& group : expected) {
            cout << "[";
            for (const string& word : group) {
                cout << "\"" << word << "\",";
            }
            cout << "], ";
        }
        cout << "Actual: ";
        for (const auto& group : actual) {
            cout << "[";
            for (const string& word : group) {
                cout << "\"" << word << "\",";
            }
            cout << "], ";
        }
        cout << endl;
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
        vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
        vector<vector<string>> expected = {{"bat"}, {"nat","tan"}, {"ate","eat","tea"}};
        vector<vector<string>> actual = sol.groupAnagrams(strs);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        vector<string> strs = {""};
        vector<vector<string>> expected = {{""}};
        vector<vector<string>> actual = sol.groupAnagrams(strs);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 3
    {
        Solution sol;
        vector<string> strs = {"a"};
        vector<vector<string>> expected = {{"a"}};
        vector<vector<string>> actual = sol.groupAnagrams(strs);
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
