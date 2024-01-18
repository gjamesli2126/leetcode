#include <bits/stdc++.h>
using namespace std;
#define mainTest main
//time: O(n), space: O(n)
class Solution {
public:
    static string minRemoveToMakeValid(string& s) {
        stack<int> stk;// put index
        for(int i=0;i<s.size();++i){
            char& c=s[i];
            if(c=='(') stk.push(i);
            else if(c==')' && )
        }

        string newStr;
        for(const char& c:s) if(c!='$') newStr+=c;
        return newStr;
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
