#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
public:
    bool isValid(string& s) {
        //use a better method then stack: Nah, still using stack but use string as a stack. So just add a single pointer named: top
        //top 之前反正都把它改成這些bracket 所以其實是把string前面都當成stack
        int top=-1;
        for(char& c:s){
            if(c=='(' || c=='[' || c=='{') s[++top]=c;
            else{//if )]}
                if(top==-1) return false;
                if(s[top]=='('&&c==')' || s[top]=='['&&c==']' || s[top]=='{'&&c=='}') --top;
                else return false;
            }
        }
        //at the end, top should be back to -1 meaning nothing on the stack
        return top==-1;
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
            {")]", false},
            {"]", false},
            {"(])",false}
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
