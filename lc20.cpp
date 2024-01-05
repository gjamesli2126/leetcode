#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for(const char& c:s){
            if(stk.empty() && (c==']' || c==')' || c=='}')) return false;
            else if(!stk.empty() && !(c=='(' || c=='[' || c=='{')){
                if(stk.top()=='('){
                    if(c==')') stk.pop();
                    else return false;
                }
                else if(stk.top()=='['){
                    if(c==']') stk.pop();
                    else return false;
                }
                else if(stk.top()=='{') {
                    if (c == '}') stk.pop();
                    else return false;
                }
            }
            else stk.push(c);
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
