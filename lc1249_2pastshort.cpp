#include <bits/stdc++.h>
using namespace std;
#define mainTest main
//time: O(n), space: O(n)
class Solution {
public:
    static string minRemoveToMakeValid(string& s) {
        string res;
        vector<bool> to_remove(s.length(),false);
        vector<int> open_oper_loc;

        for(int i=0;i<s.length();i++){
            char c=s[i];
            switch (c) {
                case '(':
                    open_oper_loc.push_back(i);
                    break;
                case ')':
                    if(open_oper_loc.empty()) to_remove[i]=true;
                    else open_oper_loc.pop_back();
                    break;
            }
        }
        for(int i:open_oper_loc) to_remove[i]=true;
        for(int i=0;i<s.length();i++){
            if(to_remove[i]) continue;
            res+=s[i];
        }
        return res;
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
