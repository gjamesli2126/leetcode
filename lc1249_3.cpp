#include <bits/stdc++.h>
using namespace std;
#define mainTest main
//time: O(n), space: O(n)
class Solution {
public:
    static string minRemoveToMakeValid(string& s) {
        //mark with $ tobe del
        int sl=s.length();
        deque<int> lft_dq;
        for(int i=0;i<sl;i++){
            char& c=s[i];
            if(c=='(') lft_dq.push_back(i);
            else if(c==')'){
                if(lft_dq.empty()) c='$';
                else lft_dq.pop_back();
            }
        }
        string newStr;
        //cpy to the newStr
        for(int i=0;i<sl;i++){
            if(!lft_dq.empty() && i==lft_dq.front()) lft_dq.pop_front();
            else if(s[i]!='$') newStr+=s[i];
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
