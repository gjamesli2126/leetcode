#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution{
private:
    unordered_map<char,int> smap,tmap;
    int have=0;
public:
    string minWindow(const string& s,const string& t){
        int sLen=int(s.length());
        int minSubStrlen=sLen+1;
        pair<int,int> minSubptrs;
        int fp=0,bp;
        for(const char& c:t) tmap[c]++;
        const int need=int(tmap.size());
        for(bp=0;bp<sLen;++bp){
            if(tmap.contains(s[bp])){
                smap[s[bp]]++;
                if(tmap[s[bp]]==smap[s[bp]]) ++have;
            }
            while(have==need){
                if(bp-fp+1 < minSubStrlen){
                    minSubStrlen=bp-fp+1;
                    minSubptrs={fp,bp};
                }
                if(smap.contains(s[fp])){
                    smap[s[fp]]--;
                    if(smap[s[fp]]<tmap[s[fp]]) --have;
                }
                ++fp;
            }

        }
        if(minSubStrlen==sLen+1) return "";
        return s.substr(minSubptrs.first,minSubStrlen);
    }
};

int mainTest() {
    auto test = [](const string& obtained, const string& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "[Pass] ";
        } else {
            cout << RED << "[Fail] ";
        }
        cout << RESET << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
    };

    struct TestCase {
        string s;
        string t;
        string expected;
    };

    vector<TestCase> testCases = {
            {"ADOBECODEBANC", "ABC", "BANC"},  // Test case 1
            {"a", "a", "a"},                   // Test case 2
            {"a", "aa", ""},                   // Test case 3
            {"aa","aa","aa"},
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        Solution solution;
        string result = solution.minWindow(testCases[i].s, testCases[i].t);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
