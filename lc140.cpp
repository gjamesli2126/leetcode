#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_set<string> wordDictSet;
    vector<string> strList;
    string orgStr;
    string vec2str(const vector<string>& v){
        string str;
        for(int i=0;i<v.size();++i){
            str+=v[i];
            if(i!=v.size()-1) str+=' ';
        }
        return str;
    }
    void dfs(int stInd,vector<string>& strBuilt){
        if(stInd==orgStr.length()) {
            strList.emplace_back(vec2str(strBuilt));
            return;
        }
        for(int i=stInd;i<orgStr.length();++i){
            string word=orgStr.substr(stInd,i-stInd+1);
            if(!wordDictSet.contains(word)) continue;
            strBuilt.emplace_back(word);
            dfs(i+1,strBuilt);
            strBuilt.pop_back();
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        copy(wordDict.begin(),wordDict.end(), inserter(wordDictSet,wordDictSet.end()));
        orgStr=s;
        vector<string> strBuild;//path
        dfs(0,strBuild);
        return strList;
    }
};

void printResult(const vector<string>& result, const vector<string>& expected) {
    if (result == expected) {
        cout << "\033[1;32mPass\033[0m"; // Green for Pass
    } else {
        cout << "\033[1;31mFail\033[0m"; // Red for Fail
    }

    cout << " | Result: [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "\"" << result[i] << "\"";
    }
    cout << "]";

    cout << " | Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "\"" << expected[i] << "\"";
    }
    cout << "]" << endl;
}

int mainTest() {
    // Test Case 1
    {
        Solution sol1;
        string s = "catsanddog";
        vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
        vector<string> expected = {"cat sand dog", "cats and dog"}; // Expected result

        cout << "Test Case 1:\n  Input: s = \"" << s << "\"\n  wordDict = [";
        for (size_t i = 0; i < wordDict.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << "\"" << wordDict[i] << "\"";
        }
        cout << "]" << endl;

        vector<string> result = sol1.wordBreak(s, wordDict);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "  ";
        printResult(result, expected);
    }

    // Test Case 2
    {
        Solution sol2;
        string s = "pineapplepenapple";
        vector<string> wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};
        vector<string> expected = {
                "pine apple pen apple",
                "pineapple pen apple",
                "pine applepen apple"}; // Expected result

        cout << "Test Case 2:\n  Input: s = \"" << s << "\"\n  wordDict = [";
        for (size_t i = 0; i < wordDict.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << "\"" << wordDict[i] << "\"";
        }
        cout << "]" << endl;

        vector<string> result = sol2.wordBreak(s, wordDict);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "  ";
        printResult(result, expected);
    }

    // Test Case 3
    {
        Solution sol3;
        string s = "catsandog";
        vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};
        vector<string> expected = {}; // Expected result (no valid segmentation)

        cout << "Test Case 3:\n  Input: s = \"" << s << "\"\n  wordDict = [";
        for (size_t i = 0; i < wordDict.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << "\"" << wordDict[i] << "\"";
        }
        cout << "]" << endl;

        vector<string> result = sol3.wordBreak(s, wordDict);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "  ";
        printResult(result, expected);
    }

    return 0;
}