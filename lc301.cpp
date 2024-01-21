#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<string> ans;
    void omitInvalid(string s, int start, int lastRemove, const char& open, const char& close){
        int quota=0;
        for(int i=start; i < s.length(); ++i){
            if(s[i]==open) ++quota;
            else if(s[i]==close) --quota;
            if(quota>=0) continue;

            for(int j=lastRemove; j <= i; ++j){
                if(s[j]==close && (j == lastRemove || s[j-1]!=close)){
                    //if not dup then remove.
                    omitInvalid(s.substr(0,j)+s.substr(j+1),i,j,open,close);
                }
            }
            return;
        }

        reverse(s.begin(),s.end());
        if(open=='('){
            omitInvalid(s,0,0,')','(');
        }
        else ans.push_back(s);//can use std::move(s) but optimized by compiler
    }
public:
    vector<string> removeInvalidParentheses(string& s) {
        if(s.empty()) return {""};
        omitInvalid(s,0,0,'(',')');
        return ans;//can use std::move(ans) but optimized by compiler
    }
};

void printResult(const vector<string>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool compareSets(const vector<string>& a, const vector<string>& b) {
    if (a.size() != b.size()) return false;
    unordered_set<string> setA(a.begin(), a.end());
    for (const auto& str : b) {
        if (setA.find(str) == setA.end()) return false;
    }
    return true;
}

int mainTest() {
    vector<pair<string, vector<string>>> testCases = {
            {"()())()", {"(())()", "()()()"}},
            {"(a)())()", {"(a())()", "(a)()()"}},
            {")(", {""}},
            // Add more test cases as needed
    };

    for (auto& [testCase, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        cout << "Input: \"" << testCase << "\"\n";
        vector<string> result = solution.removeInvalidParentheses(testCase);
        cout << "Output: ";
        printResult(result);

        // Determine pass/fail status
        if (compareSets(result, expected)) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
