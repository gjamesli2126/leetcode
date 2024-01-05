#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int,int>> stk;
        int len=int(temperatures.size());
        for(int i=0;i<len;++i){
            while(!stk.empty() && stk.top().first<temperatures[i]){
                temperatures[stk.top().second]=i-stk.top().second;
                stk.pop();
            }
            stk.push({temperatures[i],i});
        }

        while(!stk.empty()){
            temperatures[stk.top().second]=0;
            stk.pop();
        }

        return temperatures;
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](const vector<int>& obtained, const vector<int>& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "PASS: " << testName << " - Expected and Obtained match." << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected and Obtained do not match." << RESET << endl;
            cout << "Expected: ";
            for (const auto& num : expected) cout << num << " ";
            cout << "\nObtained: ";
            for (const auto& num : obtained) cout << num << " ";
            cout << endl;
        }
    };

    Solution solution;

    // Test case 1
    vector<int> temperatures1 = {73,74,75,71,69,72,76,73};
    vector<int> expected1 = {1,1,4,2,1,1,0,0};
    test(solution.dailyTemperatures(temperatures1), expected1, "Test Case 1");

    // Test case 2
    vector<int> temperatures2 = {30,40,50,60};
    vector<int> expected2 = {1,1,1,0};
    test(solution.dailyTemperatures(temperatures2), expected2, "Test Case 2");

    // Test case 3
    vector<int> temperatures3 = {30,60,90};
    vector<int> expected3 = {1,1,0};
    test(solution.dailyTemperatures(temperatures3), expected3, "Test Case 3");

    // Add more test cases if necessary.

    return 0;
}
