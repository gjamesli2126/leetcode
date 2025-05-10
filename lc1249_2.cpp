#include <bits/stdc++.h>
using namespace std;
#define mainTest main
//time: O(n), space: O(n)
class Solution {
private:
    stack<int> acc_stk;//position use "$" mark in the string
public:
    string minRemoveToMakeValid(string& s) {
        //replace the string's shit with $
        for(int i=0;i<s.length();i++){
            char c=s[i];
            if(c=='(') acc_stk.emplace(i);
            else if(c==')' && !acc_stk.empty()) acc_stk.pop();
            else if(c==')') s[i]='$';
        }
        while(!acc_stk.empty()){
            int i=acc_stk.top();
            s[i]='$';
            acc_stk.pop();
        }
        string ans;
        for(char c:s) if(c!='$') ans+=c;
        return ans;
    }
};
int mainTest() {
    Solution solution;

    // Define test cases
    vector<string> testCases = {
            "lee(t(c)o)de)",
            "a)b(c)d",
            "))(("
    };

    // Iterate through test cases and display results
    for (auto& testCase : testCases) {
        string result = solution.minRemoveToMakeValid(testCase);
        cout << "Input: \"" << testCase << "\"\n";
        cout << "Output: \"" << result << "\"\n\n";
    }

    return 0;
}
