#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    unordered_map<char,int> dictT;
    unordered_map<char,int> dictS;
    vector<pair<int,char>> jmpS;
    pair<int,int> maxP1_minL={-1,INT_MAX};

public:
    string minWindow(string s, string t) {
        if(t.length()>s.length()) return "";
        //collect dictT
        for(char c:t) dictT[c]++;
        //gather jmpS
        for(int i=0;i<s.length();i++){
            char c=s[i];
            if(!dictT.contains(c)) continue;
            jmpS.emplace_back(i,c);
        }
        if(jmpS.empty()) return "";
        //loop thru jmpS, rec maxP1_minL
        int formed=0;
        for(int l=0,r=0;r<jmpS.size();r++){
            auto& [ind,c]=jmpS[r];
            dictS[c]++;
            if(dictS[c]==dictT[c]) formed++;

            while(l<=r && formed==dictT.size()){
                auto [p1,c1]=jmpS[l];
                auto [p2,c2]=jmpS[r];
                if(p2-p1+1<maxP1_minL.second) maxP1_minL={p1,p2-p1+1};
                dictS[c1]--;//只會看到必要的
                if(dictS[c1]<dictT[c1]) formed--;
                l++;
            }
        }
        return maxP1_minL.first==-1? "":s.substr(maxP1_minL.first,maxP1_minL.second);
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