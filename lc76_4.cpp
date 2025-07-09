#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    string minWindow(const string& s,const string& t) {
        unordered_map<char,int> need,window;
        int formed=0;
        for(char c:t) need[c]++;
        int required=need.size();
        int l=0,r;
        pair<int,int> rec_lr={-1,s.length()};
        for(r=0;r<s.length();r++){
            char c=s[r];
            ++window[c];
            if(need[c]>0 && need[c]==window[c]) ++formed;//formed means how many kinds of charc are satisfied.
            while(l<=r && formed==required){//need.size() is the number of entries
                //update the recoreded left & right
                if(r-l<rec_lr.second-rec_lr.first) rec_lr={l,r};
                char cl=s[l];
                if(window[cl]==need[cl]) --formed;//just fell under
                window[cl]--;
                l++;
            }

        }
        return rec_lr.first==-1?"":s.substr(rec_lr.first,rec_lr.second-rec_lr.first+1);
    }
};

void runTest(int testNum, string s, string t, string expected) {
    Solution sol;
    string result = sol.minWindow(s, t);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: minWindow(\"" << s << "\", \"" << t
             << "\") = \"" << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: minWindow(\"" << s << "\", \"" << t
             << "\") = \"" << result << "\", expected \""
             << expected << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "ADOBECODEBANC", t = "ABC"
    // Expected Output: "BANC"
    runTest(1, "ADOBECODEBANC", "ABC", "BANC");

    // Test Case 2:
    // Input: s = "a", t = "a"
    // Expected Output: "a"
    runTest(2, "a", "a", "a");

    // Test Case 3:
    // Input: s = "a", t = "aa"
    // Expected Output: ""
    runTest(3, "a", "aa", "");
    runTest(4, "a", "b", "");
    runTest(5, "aa", "aa", "aa");
    return 0;
}