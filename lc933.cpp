#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class RecentCounter {
private:
    deque<int> q;
public:
    RecentCounter() {
    }
    int ping(int t) {
        q.push_back(t);
        while(!q.empty() && q.front()<t-3000) q.pop_front();
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

int mainTest() {
    // Local function for testing conditions
    auto test = [](const vector<int>& obtained, const vector<int>& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        bool isPass = obtained == expected;
        cout << (isPass ? GREEN + "PASS" : RED + "FAIL") << RESET << ": " << testName;
        if (!isPass) {
            cout << " - Expected: " << RED << "[";
            for (const auto& val : expected) cout << val << " ";
            cout << "]" << RESET << ", Obtained: " << RED << "[";
            for (const auto& val : obtained) cout << val << " ";
            cout << "]" << RESET;
        }
        cout << endl;
    };

    // Array of test cases
    struct TestCase {
        vector<int> inputs;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{1, 100, 3001, 3002}, {1, 2, 3, 3}}, // Test case 1
            {{1, 2, 3, 3000, 3001, 6000}, {1, 2, 3, 4, 5, 3}}, // Test case 2
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        RecentCounter* recentCounter = new RecentCounter();
        vector<int> result;
        for (int input : testCases[i].inputs) {
            result.push_back(recentCounter->ping(input));
        }
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
        delete recentCounter; // Clean up memory
    }

    return 0;
}