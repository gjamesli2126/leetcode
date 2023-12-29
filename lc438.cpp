#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<char,int> pAna,subsAna;
public:
    vector<int> findAnagrams(string s, string p) {
        if(s.empty() || p.empty()) return {};
        vector<int> ans;
        int slen=int(s.length());
        int plen=int(p.length());
        if(plen>slen) return {};
        for(int i=0;i<plen;++i){
            pAna[p[i]]++;
            subsAna[s[i]]++;
        }
        if(p=="aa"){

        }
        for(int fp=0,bp=plen-1;bp<slen;++fp,subsAna[s[++bp]]++){
//            cout<<"subs: "<<endl;
//            for(const auto &[c,f]:subsAna) cout<<c<<":"<<f<<endl;
//            cout<<"p: "<<endl;
//            for(const auto &[c,f]:pAna) cout<<c<<":"<<f<<endl;
//            cout<<endl;
            if(pAna.size()==subsAna.size()){
                bool same=true;
                for(const auto &[c,f]:subsAna){
                    if(pAna.find(c)==pAna.end() || pAna[c]!=f){
                        same&=false;
                        break;
                    }
                }
                if(same) ans.push_back(fp);
            }
            subsAna[s[fp]]--;
            if(!subsAna[s[fp]]) subsAna.erase(s[fp]);
        }
        return ans;
    }
};

int mainTest() {
    // Test Cases
    vector<pair<string, string>> testCases = {
            {"cbaebabacd", "abc"},  // Example 1
            {"abab", "ab"},          // Example 2
            {"baa","aa"}
    };

    // Expected Outputs
    vector<vector<int>> expectedOutputs = {{0, 6}, {0, 1, 2},{1}}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        Solution solution;  // Create a new Solution object for each test case
        vector<int> actual = solution.findAnagrams(testCases[i].first, testCases[i].second);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Input: s = \"" << testCases[i].first << "\", p = \"" << testCases[i].second << "\", "
             << "Expected: [";
        for (size_t j = 0; j < expectedOutputs[i].size(); ++j) {
            cout << expectedOutputs[i][j];
            if (j < expectedOutputs[i].size() - 1) cout << ", ";
        }
        cout << "], Actual: [";
        for (size_t j = 0; j < actual.size(); ++j) {
            cout << actual[j];
            if (j < actual.size() - 1) cout << ", ";
        }
        cout << "], Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
