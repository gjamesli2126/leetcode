#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int slen;
    vector<vector<string>> ans;
    bool isPalindrome(const string_view& s,int st,int end){
        while(st<end){
            if(s[st]!=s[end]) return false;
            ++st;
            --end;
        }
        return true;
    }
    void dfsBackTrack(const string& s,int st,vector<string>& cur){
        if(st==slen){
            ans.push_back(cur);
            return;
        }
        for(int end=st;end<slen;++end){
            if(!isPalindrome(s,st,end)) continue;
            cur.push_back(s.substr(st,end-st+1));
            dfsBackTrack(s,end+1,cur);
            cur.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string& s) {
        slen=static_cast<int>(s.length());
        vector<string> cur;
        dfsBackTrack(s,0,cur);
        return ans;
    }
};

void printResult(const vector<vector<string>>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool compareSets(vector<vector<string>>& a, vector<vector<string>>& b) {
    for (auto& vec : a) sort(vec.begin(), vec.end());
    for (auto& vec : b) sort(vec.begin(), vec.end());
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int mainTest() {
    vector<pair<string, vector<vector<string>>>> testCases = {
            {"aab", {{"a", "a", "b"}, {"aa", "b"}}},
            {"a", {{"a"}}}
            // Add more test cases as needed
    };

    for (auto& [input, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        vector<vector<string>> result = solution.partition(input);

        cout << "Input: \"" << input << "\"\n";
        cout << "Expected Output: ";
        printResult(expected);
        cout << "Your Output: ";
        printResult(result);

        // Determine pass/fail status
        cout << "Test Result: ";
        if (compareSets(result, expected)) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
