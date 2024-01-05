#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<string,function<int(int,int)>> op{
            {"+",[](const int& a,const int& b){return a+b;}},
            {"-",[](const int& a,const int& b){return a-b;}},
            {"*",[](const int& a,const int& b){return a*b;}},
            {"/",[](const int& a,const int& b){return a/b;}}
    };
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(const string& s:tokens){
            if(op.contains(s)){
                int b=stk.top();
                stk.pop();
                int a=stk.top();
                stk.pop();
                stk.push(op[s](a,b));
            }
            else{
                stk.push(stoi(s));
            }
        }
        if(stk.empty()) return 0;
        return stk.top();
    }
};



int mainTest() {
    // Local function for testing conditions.
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "PASS: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        }
    };

    Solution solution;

    // Test case 1
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    test(solution.evalRPN(tokens1), 9, "Test Case 1");

    // Test case 2
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    test(solution.evalRPN(tokens2), 6, "Test Case 2");

    // Test case 3
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    test(solution.evalRPN(tokens3), 22, "Test Case 3");

    return 0;
}
