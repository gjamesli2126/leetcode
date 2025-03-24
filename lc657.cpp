#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int x=0;
    int y=0;
public:
    bool judgeCircle(const string &moves) {
        for(char d:moves){
            switch (d){
                case 'U':
                    ++y;
                    break;
                case 'D':
                    --y;
                    break;
                case'L':
                    --x;
                    break;
                case 'R':
                    ++x;
                    break;
            }
        }
        return x==0 && y==0;
    }
};

int mainTest() {
    vector<pair<string, bool>> testCases = {
            {"UD", true},  // Example 1
            {"LL", false}, // Example 2
            {"RRDD", false}, // Custom test case
            {"UDLR", true}, // Returns to origin
    };

    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    for (int i = 0; i < testCases.size(); ++i) {
        string moves = testCases[i].first;
        bool expectedOutput = testCases[i].second;

        Solution solution; // Create a new object for each test case
        bool actualOutput = solution.judgeCircle(moves);

        cout << "Test " << i + 1 << ": ";
        if (actualOutput == expectedOutput) {
            cout << green << "PASS" << reset;
        } else {
            cout << red << "FAIL" << reset;
        }
        cout << " - Input: \"" << moves << "\"; ";
        cout << "Expected: " << (expectedOutput ? "true" : "false") << "; ";
        cout << "Actual: " << (actualOutput ? "true" : "false") << endl;
    }

    return 0;
}