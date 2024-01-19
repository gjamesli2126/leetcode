#include <bits/stdc++.h>
using namespace std;
#define mainTest main
//time: O(n), space: O(n)
class Solution {
public:
    static string minRemoveToMakeValid(string& s) {
        deque<int> dq;// put index
        for(int i=0;i<s.size();++i){
            char& c=s[i];
            if(c=='(') dq.push_back(i);
            else if(c==')' && !dq.empty()) dq.pop_back();
            else if(c==')') c='$';
        }
        string newStr;
        for(int i=0;i<s.size();++i){
            if(!dq.empty() && dq.front()==i){
                dq.pop_front();
                continue;
            }
            if(s[i]=='$') continue;
            newStr+=s[i];
        }
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
