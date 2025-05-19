#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    unordered_map<char,int> dicT;
    unordered_map<char,int> dicS;
    vector<pair<int,char>> jmpS;//only keep the char that is requiredin the T
    pair<int,int> l_r;
public:
    string minWindow(const string& s,const string& t) {
        if(s.empty() || t.empty()) return "";
        l_r={-1,s.length()};//init out of bound
        //gather dicT--requirement
        for(char ct:t) dicT[ct]++;
        //gathering only meaningful charc
        for(int i=0;i<s.length();i++) if(dicT.contains(s[i])) jmpS.emplace_back(i,s[i]);

        //start counting the forming, l---r is the index of the jmpS not the index of string
        int form=0;
        for(int l=0,r=0;r<jmpS.size();r++){
            auto [ind,c]=jmpS[r];
            //now the c is garentee in dicT
            dicS[c]++;//do not add/minus dicT as dicT is the requirement.
            if(dicT[c]==dicS[c]) form++;

            while (l<=r && form==dicT.size()){
                //start l++ing; meaning shriking the substr, omitting extra copy
                auto [pl,cl]=jmpS[l];
                auto [pr,cr]=jmpS[r];
                if(l_r.second-l_r.first>pr-pl) l_r={pl,pr};
                dicS[cl]--;
                if(dicT[cl]>dicS[cl]) form--;
                l++;
            }
        }
        return l_r.first==-1?"":s.substr(l_r.first,l_r.second-l_r.first+1);
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