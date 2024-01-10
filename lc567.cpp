#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<char,int> mp1,mp2;
    //O(26n) for time complex
public:
    bool checkInclusion(const string& s1, const string s2) {
        if(s1.size()>s2.size()) return false;
        //create map for s1
        for(const char c:s1) mp1[c]++;
        const int winLen=int(s1.size());
        //create dynamic map for s2
        int l=0,r;
        for(int i=l;i<=winLen-1;++i) mp2[s2[i]]++;

        for(r=winLen-1;r<s2.length();){
            bool found=false,match=true;
            for(const auto [k,v]:mp2){//comparing 2 hashmap fully
                if(mp1.contains(k)){
                    found=true;
                    if(mp1[k]!=v) match=false;
                }
                else match=false;
            }
            if(match&&found) return true;
            if(found){
                mp2[s2[l]]--;
                if(mp2[s2[l]]==0) mp2.erase(s2[l]);
                ++l;
                ++r;
                mp2[s2[r]]++;
            }
            else{
                mp2.clear();
                r+=winLen;
                l+=winLen;
                if(r>=s2.size()) return false;
                for(int i=l;i<=r;++i) mp2[s2[i]]++;
            }
        }
        return false;
    }
};

int mainTest() {
    auto test = [](bool obtained, bool expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "[Pass] ";
        } else {
            cout << RED << "[Fail] ";
        }
        cout << RESET << testName << " - Expected: " << (expected ? "True" : "False") << ", Obtained: " << (obtained ? "True" : "False") << RESET << endl;
    };

    struct TestCase {
        string s1;
        string s2;
        bool expected;
    };

    vector<TestCase> testCases = {
            {"ab", "eidbaooo", true},  // Test case 1
            {"ab", "eidboaoo", false}, // Test case 2
            {"rokx","otrxvfszxroxrzdsltg",false},
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        Solution solution;
        bool result = solution.checkInclusion(testCases[i].s1, testCases[i].s2);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
