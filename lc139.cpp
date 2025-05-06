#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool wordBreak(const string& s,const vector<string>& wordDict) {
        //using dp buttom up w/ memo true/false
        vector<bool> indtfTable(s.length()+1,false);//b/c empty string is breakable
        indtfTable[s.length()]=true;
        for(int i=s.length()-1;i>=0;i--){
            for(const string& word:wordDict){
                int wordlen=word.length();
                if(i+wordlen<=s.length() && s.compare(i,wordlen,word)==0 && indtfTable[i+wordlen]){
                    indtfTable[i]=true;
                    break;
                }
            }
        }
        return indtfTable[0];
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& s, vector<string> wordDict, bool expected) {
    Solution sol;
    bool result = sol.wordBreak(s, wordDict);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: wordBreak(\"" << s << "\", wordDict) = "
             << (result ? "true" : "false") << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: wordBreak(\"" << s << "\", wordDict) = "
             << (result ? "true" : "false") << ", expected "
             << (expected ? "true" : "false") << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: s = "leetcode", wordDict = ["leet","code"]
    // Output: true
    runTest(1, "leetcode", {"leet","code"}, true);

    // Example 2:
    // Input: s = "applepenapple", wordDict = ["apple","pen"]
    // Output: true
    runTest(2, "applepenapple", {"apple","pen"}, true);

    // Example 3:
    // Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    // Output: false
    runTest(3, "catsandog", {"cats","dog","sand","and","cat"}, false);

    return 0;
}