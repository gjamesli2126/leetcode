#include <bits/stdc++.h>
using namespace std;
#define mainTest main
//time: O(3n), space: O(1)
class Solution {
public:
    static string minRemoveToMakeValid(string& s) {
        int pCount=0;
        string newStr;
        for(char& c:s){
            if(c==')' && !pCount) c='$';
            if(c=='(') ++pCount;
            else if(c==')') --pCount;
        }
        pCount=0;
        for(auto it=s.rbegin();it<s.rend();++it){
            char& c=*it;
            if(c=='(' && !pCount) c='$';
            if(c==')') ++pCount;
            else if(c=='(') --pCount;
        }
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
