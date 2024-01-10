#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution{
public:
    int maxProfit(const vector<int>& prices){
        int maxPro=0;
        int minCost=prices[0];
        for(const int& price:prices){
            minCost=min(price,minCost);
            maxPro=max(price-minCost,maxPro);
        }
        return maxPro;
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
        vector<int> prices;
        int expected;
    };

    vector<TestCase> testCases = {
            {{7,1,5,3,6,4}, 5},  // Test case 1
            {{7,6,4,3,1}, 0},    // Test case 2
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.maxProfit(testCases[i].prices);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
