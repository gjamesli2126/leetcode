#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    stack<char> stk;
    bool match(char left,char right){
        return (left=='(' && right==')'||
                left=='[' && right==']'||
                left=='{'&&right=='}' );
    }
public:
    bool isValid(const string &s) {

        for(char c:s){
            if(c=='('||c=='['||c=='{') stk.push(c);
            else if(stk.empty() || !match(stk.top(),c)) return false;
            else stk.pop();
        }
        return stk.empty();
    }
};

int mainTest() {
    Solution solution;
    vector<pair<string, bool>> testCases = {
            {"()", true},
            {"()[]{}", true},
            {"(]", false},
            {"([)]", false},
            {"{[]}", true},
            {"", true},
            {"((", false},
            {")]", false}
            // Add more test cases if needed
    };

    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    for (int i = 0; i < testCases.size(); ++i) {
        bool actualOutput = solution.isValid(testCases[i].first);
        bool expectedOutput = testCases[i].second;
        bool status = (actualOutput == expectedOutput);

        cout << "Test " << i + 1 << ": ";
        cout << (status ? green : red) << (status ? "PASS" : "FAIL") << reset << " - ";
        cout << "Input: \"" << testCases[i].first << "\"; ";
        cout << "Expected: " << (expectedOutput ? "true" : "false") << "; ";
        cout << "Actual: " << (actualOutput ? "true" : "false") << endl;
    }

    return 0;
}
